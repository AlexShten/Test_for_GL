#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
 
#define ERROR_FILE_OPEN -3
#define SEEK_SET 0

void main(int argc, char** argv) {
	FILE *FS_image = NULL;
	FILE *inner_file = NULL;
	int **fentry_table = NULL;
	struct stat st={0};
	unsigned char dir[100];
	unsigned char subdir[100];
	unsigned char fnpath[100];
	unsigned char somedir[100];
	unsigned char read_byte;
	char read;
	int entnum = 0;
	int fsize = 0;
	int foffset = 0;
	int file_name_size;
	long last_position;

	//Creating a folder with an .img file name
	//
	for (int i = 0; i < strlen(argv[1]); i++) {
		if (argv[1][i] == 46) {
			memset(dir, 0, 100);
			strncpy(dir, argv[1], i);
			break;
		}			
	}
	strcpy(somedir, argv[2]);
	strcat(somedir, "/");
	strcat(somedir, dir);
	if(stat(somedir, &st) == -1) mkdir(somedir, 0777);
	//---------------------------------------------------------
	
	//Open .img file as binary file for read
	//
	FS_image = fopen(argv[1], "rb");
	if (FS_image == NULL) {
		printf("Error opening file");
		exit(ERROR_FILE_OPEN);
	}
	//---------------------------------------------------------

	//Obtaining information about the number of files in the image
	//
	fseek(FS_image, 3L, SEEK_SET);
	fread(&read_byte, sizeof(unsigned char), 1, FS_image);
	entnum = read_byte * 256;
	fseek(FS_image, 2L, SEEK_SET);
	fread(&read_byte, sizeof(unsigned char), 1, FS_image);
	entnum = entnum + read_byte;
	//---------------------------------------------------------

	//Creating a dynamic two-dimensional array for file size and offset
	//
	fentry_table = (int**)malloc(entnum * sizeof(int*));
	for (int i = 0; i < entnum; i++) {
		fentry_table[i] = (int*)malloc(2 * sizeof(int));
	}
	//---------------------------------------------------------

	//Getting file size and offset information (for fentry table)
	//
	for (int i = 0; i < entnum; i++) {
		fseek(FS_image, (6L + i * 7L), SEEK_SET);
		fread(&read_byte, sizeof(unsigned char), 1, FS_image);
		fsize = read_byte * 65536;
		fseek(FS_image, (5L + i * 7L), SEEK_SET);
		fread(&read_byte, sizeof(unsigned char), 1, FS_image);
		fsize = fsize + read_byte * 256;
		fseek(FS_image, (4L + i * 7L), SEEK_SET);
		fread(&read_byte, sizeof(unsigned char), 1, FS_image);
		fsize = fsize + read_byte;
		fentry_table[i][0] = fsize;

		fseek(FS_image, (10L + i * 7L), SEEK_SET);
		fread(&read_byte, sizeof(unsigned char), 1, FS_image);
		foffset = read_byte * 16777216;
		fseek(FS_image, (9L + i * 7L), SEEK_SET);
		fread(&read_byte, sizeof(unsigned char), 1, FS_image);
		foffset = foffset + read_byte * 65536;
		fseek(FS_image, (8L + i * 7L), SEEK_SET);
		fread(&read_byte, sizeof(unsigned char), 1, FS_image);
		foffset = foffset + read_byte * 256;
		fseek(FS_image, (7L + i * 7L), SEEK_SET);
		fread(&read_byte, sizeof(unsigned char), 1, FS_image);
		foffset = foffset + read_byte;
		fentry_table[i][1] = foffset;
	}
	//-------------------------------------------------------------
	
	//The main part of the program that extracts information from the image
	//
	for (int i = 0; i < entnum; i++) {
		if (i != entnum - 1) {	//Runs for non-recent files in an image
			
			file_name_size = fentry_table[i + 1][1] - fentry_table[i][1] - fentry_table[i][0] - 1 - 1;
			
			memset(fnpath, 0, 100);
			fseek(FS_image, (fentry_table[i][1] + fentry_table[i][0]), SEEK_SET);
			for (int j = 0; j <= file_name_size; j++) {	//Extract file name from image
				fread(&read_byte, sizeof(unsigned char), 1, FS_image);
				fnpath[j] = read_byte;
			}
			for (int j = strlen(fnpath)-1; j >=0 ; j--) {
				if (fnpath[j] == 47) {	//Search "/" as a sign of subfolders
					memset(subdir, 0, 100);
					strncpy(subdir, fnpath, j);
					strcpy(somedir, argv[2]);
					strcat(somedir, "/");
					strcat(somedir, dir);
					strcat(somedir, "/");
					strcat(somedir, subdir);
					if(stat(somedir, &st) == -1) mkdir(somedir, 0777); //Creating subfolder
				}			
			}

			strcpy(somedir, argv[2]);
			strcat(somedir, "/");
			strcat(somedir, dir);
			strcat(somedir, "/");
			strcat(somedir, fnpath);
			inner_file = fopen(somedir, "wb");	//Preparing a new file for copying
			if (inner_file == NULL) {
				printf("Error opening file");
				exit(ERROR_FILE_OPEN);
			}

			fseek(FS_image, (fentry_table[i][1]), SEEK_SET);
			for (int j = 0; j < fentry_table[i][0]; j++) {	//Copying information from an image to a new file
				fread(&read, sizeof(char), 1, FS_image);
				fwrite(&read, sizeof(char), 1, inner_file);
			}
			fclose(inner_file);
		}
		else {	//runs for the last file in the image
			fseek(FS_image, (fentry_table[i][1] + fentry_table[i][0]), SEEK_SET);
			while (getc(FS_image) != EOF) {}
			last_position = ftell(FS_image);
			file_name_size = last_position - fentry_table[i][1] - fentry_table[i][0] - 1 - 1;

			memset(fnpath, 0, 100);
			fseek(FS_image, (fentry_table[i][1] + fentry_table[i][0]), SEEK_SET);
			for (int j = 0; j <= file_name_size; j++) {
				fread(&read_byte, sizeof(unsigned char), 1, FS_image);
				fnpath[j] = read_byte;
			}
			

			for (int j = strlen(fnpath)-1; j>=0 ; j--) {
				if (fnpath[j] == 47) {	//Search "/" as a sign of subfolders
					memset(subdir, 0, 100);
					strncpy(subdir, fnpath, j);
					strcpy(somedir, argv[2]);
					strcat(somedir, "/");
					strcat(somedir, dir);
					strcat(somedir, "/");
					strcat(somedir, subdir);
					if(stat(somedir, &st) == -1) mkdir(somedir, 0777);//Creating subfolder
				}			
			}
			strcpy(somedir, argv[2]);
			strcat(somedir, "/");
			strcat(somedir, dir);
			strcat(somedir, "/");
			strcat(somedir, fnpath);
			inner_file = fopen(somedir, "wb");	//Preparing a new file for copying
			if (inner_file == NULL) {
				printf("Error opening file");
				exit(ERROR_FILE_OPEN);
			}

			fseek(FS_image, (fentry_table[i][1]), SEEK_SET);
			for (int j = 0; j < fentry_table[i][0]; j++) {	//Copying information from an image to a new file
				fread(&read, sizeof(char), 1, FS_image);
				fwrite(&read, sizeof(char), 1, inner_file);
			}
			fclose(inner_file);
		}
	}
	fclose(FS_image);
}
