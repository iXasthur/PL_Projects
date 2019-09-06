//
//  main.c
//  L2_3
//
//  Created by Михаил Ковалевский on 06/09/2019.
//  Copyright © 2019 Mikhail Kavaleuski. All rights reserved.
//

#include <stdio.h>
#include "stdlib.h"
#include "time.h"

void swapElements(int *a, int *b){
    int buff = *a;
    *a = *b;
    *b = buff;
}

int main() {
    srand(time(NULL));
    int n = 5, k = 10, i, j, rowIsSorted = 0;
    int a[n][k];
    
    printf("Initial array:\n");
    for (i=0; i<=n-1; i++) {
        for (j=0; j<=k-1; j++) {
            a[i][j] = rand()%90 + 10;
            printf("%.2d  ", a[i][j]);
        }
        printf("\n");
    }
    
    for (i=0; i<=n-1; i++) {
        rowIsSorted = 0;
        
        while (rowIsSorted==0) {
            rowIsSorted = 1;
            
            for (j=0; j<=k-2; j++) {
                if (a[i][j]<a[i][j+1]) {
                    swapElements(&a[i][j], &a[i][j+1]);
                    rowIsSorted = 0;
                }
            }
        }
    }
    
    printf("\nOld row sums:\n");
    int rowSum[n];
    for (i=0; i<=n-1; i++) {
        rowSum[i] = a[i][0];
        for (j=1; j<=k-1; j++) {
            rowSum[i] += a[i][j];
        }
        printf("%d row: %d\n", i, rowSum[i]);
    }
    
    rowIsSorted = 0;
    while (rowIsSorted == 0) {
        rowIsSorted = 1;
        
        for (i=0; i<=n-2; i++) {
            if (rowSum[i] >= rowSum[i+1]) {
                rowIsSorted = 0;
                
                swapElements(&rowSum[i], &rowSum[i+1]);
                for (j=0; j<=k-1; j++) {
                    swapElements(&a[i][j], &a[i+1][j]);
                }
            }
        }
    }
    
    printf("\nEdited array:\n");
    for (i=0; i<=n-1; i++) {
        for (j=0; j<=k-1; j++) {
            printf("%.2d  ", a[i][j]);
        }
        printf("\n");
    }
    
    printf("\nNew row sums:\n");
    for (i=0; i<=n-1; i++) {
        int sum = a[i][0];
        for (j=1; j<=k-1; j++) {
            sum += a[i][j];
        }
        printf("%d row: %d\n", i, sum);
    }
    
    return 0;
}
