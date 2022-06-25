#include<stdio.h>
#include<math.h>

int main(int argc, char* argv[]) {
    FILE *fin = fopen(argv[1], "r");
    FILE *fout = fopen(argv[2], "w");

    int P, R, T, M;
    double compoundMultiplier = 0;
    double compoundInterest = 0;

    fscanf(fin, "%d%d%d%d", &P, &R, &T, &M);

    //T/12
    //12/M
    /*
    int i;
    compoundMultiplier = 1 + (R/100.0) / (12.0/M);
    for (i = 0; i < (T/12.0) * (12.0/M) - 1; i++) {
        compoundMultiplier *= 1 + (R/100.0) / (12.0/M);
    }
    */
    compoundMultiplier = pow(1 + (R/100.0) / (12.0/M), (T/12.0) * (12.0/M));
    compoundInterest = P * (compoundMultiplier - 1);
    fprintf(fout, "%.2f\n", compoundInterest);

    fclose(fin);
    fclose(fout);

    return 0;
}
