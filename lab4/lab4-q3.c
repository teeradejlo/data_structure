#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int isprime(int n) {
    int i;
    for (i = 2; i<= n/2; i++) {
        if (n % i == 0) {
            return 0;
        }
    }
    return 1;
}

int main(int argc, char *argv[]) {

	FILE *fin, *fout;
	int n, answer = 0;

	fin = fopen(argv[1], "r");
	fout = fopen(argv[2], "w");

	fscanf(fin, "%d", &n);
	/* Your code here */
	answer = 2 * n;
    while (!isprime(answer)) {
        answer++;
    }

	/* Output format */
	fprintf(fout, "%d\n", answer);

	fclose(fin);
	fclose(fout);

	return 0;
}
