//
//  main.c
//  L2_2
//
//  Created by Михаил Ковалевский on 06/09/2019.
//  Copyright © 2019 Mikhail Kavaleuski. All rights reserved.
//

#include <stdio.h>
#include "time.h"
#include "stdlib.h"

int main(int argc, const char * argv[]) {
    srand(time(NULL));
    int n = 5, i, j;
    double a[n][n];
    
    if (n>0) {
    printf("Initial array:\n");
    for (i=0; i<=n-1; i++) {
        for (j=0; j<=n-1; j++) {
            a[i][j] = (double)(rand()%100) + (double)(rand()%100)/100;
            printf("%5.2lf  ", a[i][j]);
        }
        printf("\n");
    }
    
    
    double maxDiag = a[0][0];
    int savedI = 0, savedJ = 0;
    for (i=1, j=1; i<=n-1; i++, j++) {
        if (a[i][j] > maxDiag) {
            maxDiag = a[i][j];
            savedI = i;
            savedJ = j;
        }
    }
    
    for (i=n-1, j=0; i>=0; i--, j++) {
        if (a[i][j] > maxDiag) {
            maxDiag = a[i][j];
            savedI = i;
            savedJ = j;
        }
    }
    
    printf("\nMax diagonal element: %5.2lf  (i: %d, j: %d)\n", maxDiag, savedI, savedJ);
    
    if (n % 2 == 0) {
        printf("\nThere is no element in the center!\n");
    } else {
        double buff = a[(n-1)/2][(n-1)/2];
        printf("Central element: %5.2lf\n",buff);
        
        a[(n-1)/2][(n-1)/2] = a[savedI][savedJ];
        a[savedI][savedJ] = buff;
    }
    
    printf("\nEdited array:\n");
    for (i=0; i<=n-1; i++) {
        for (j=0; j<=n-1; j++) {
            printf("%5.2lf  ", a[i][j]);
        }
        printf("\n");
    }
    } else {
        printf("Array is too small!\n");
    }
    
    return 0;
}
