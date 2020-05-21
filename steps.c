#include <stdio.h>
#include <errno.h>   // for errno
#include <limits.h>  // for INT_MAX, INT_MIN
#include <stdlib.h>  // for strtol

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
	int K = 0;
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
	K = Convertion(argv[2]);
	if (K < 0) {
		printf("Incorrect arguments");
		return 0;
	}

	result = N / (K + 1);
	if (N % (K + 1) != 0) result += 1;

	printf("%d\n", result);
	return result;
}