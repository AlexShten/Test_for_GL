#include <stdio.h>
#include <errno.h>   // for errno
#include <stdlib.h>  // for strtol
#include <limits.h>
#include <string.h>


int Convertion(char* arg) {
	char* p;
	long convert = 0;
	errno = 0;

	convert = strtol(arg, &p, 10);
	if (errno != 0 || *p != '\0' || convert > INT_MAX || convert < INT_MIN || convert < 0) return -1;
	else return convert;
}

double main(int argc, char** argv) {
	int N = 0;
	int D = 0;
	double dD=0;
	double result = 0;
	int notint=0;
	char *ptr;

	if (argc != 3) {
		printf("Wrong number of arguments");
		return 0;
	}
	N = Convertion(argv[1]);
	if (N < 0) {
		printf("Incorrect arguments");
		return 0;
	}

	for (int i=0; i<strlen(argv[2]); i++) {
		if (argv[2][i]==46){
			notint=1;
			break;
		}
	}	
	if (notint==0){
		D = Convertion(argv[2]);
		if (D < 0) {
			printf("Incorrect arguments");
			return 0;
		}

		if (N % 2 == 0) result = (N + 1)*(N / 2)*D;
		else result = (N*((N - 1) / 2) + N)*D;
		printf("%5.0f\n", result);
	}
	else {
		dD=strtod(argv[2], &ptr);
		if (errno==ERANGE || dD<0) {
			printf("value out of range\n");
			return 0;

		}
		if (N % 2 == 0) result = (N + 1)*(N / 2)*dD;
		else result = (N*((N - 1) / 2) + N)*dD;
		printf("%5.2f\n", result);
	}
	
	return result;
}