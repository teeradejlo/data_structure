#include<stdio.h>

int main(int argc, char* argv[]) {
    FILE *fin = fopen(argv[1], "r");
    FILE *fout = fopen(argv[2], "w");

    fprintf(fout, "Hello World!\n");

    fclose(fin);
    fclose(fout);

    return 0;
}
