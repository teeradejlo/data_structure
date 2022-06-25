#include<stdio.h>
#include"lab0-q4.h"

int isprime(int input, int *result) {
	if (input < 0) {
        //neg number
        return -1;
	}
	if (input <= 1) {
        //not neg, exception
        *result = 0;
        return 0;
	}
	int i;
    for (i = 2; i <= input/2; i++) {
        if (input % i == 0) {
            *result = 0;
            return 0;
        }
    }

    *result = 1;
    return 0;
}
