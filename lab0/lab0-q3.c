#include<stdio.h>

int main(int argc, char* argv[]) {
    FILE *fin = fopen(argv[1], "r");
    FILE *fout = fopen(argv[2], "w");

    int original;
    fscanf(fin, "%d", &original);
    int dummy;

    if (original == 0) {
        fprintf(fout, "0\n");
        fclose(fin);
        fclose(fout);
        return 0;
    }

    while (original % 10 == 0) {
        original /= 10;
    }
    while (original > 0) {
        dummy = original % 10;
        fprintf(fout, "%d", dummy);
        original /= 10;
    }
    fprintf(fout, "\n");

    fclose(fin);
    fclose(fout);

    return 0;
}
