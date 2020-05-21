#include <stdio.h>
#include <errno.h>   // for errno
#include <stdlib.h>  // for strtol
#include <limits.h>


int Convertion(char* arg) {
	char* p;
	long convert = 0;
	errno = 0;

	convert = strtol(arg, &p, 10);
	if (errno != 0 || *p != '\0' || convert > INT_MAX || convert < INT_MIN || convert < 0) return -1;
	else return convert;
}

int main(int argc, char** argv) {
	int N = 0;
	int D = 0;
	int result = 0;

	if (argc != 3) {
		printf("Wrong number of arguments");
		return 0;
	}
	N = Convertion(argv[1]);
	if (N < 0) {
		printf("Incorrect arguments");
		return 0;
	}
	D = Convertion(argv[2]);
	if (D < 0) {
		printf("Incorrect arguments");
		return 0;
	}

	if (N % 2 == 0) result = (N + 1)*(N / 2)*D;
	else result = (N*((N - 1) / 2) + N)*D;

	printf("%d\n", result);
	return result;
}