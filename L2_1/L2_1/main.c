//
//  main.c
//  L2_1
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
    int a[5][5], i, j, rowIsSorted = 0;
    
    printf("Initial array:\n");
    for (i=0; i<=4; i++) {
        for (j=0; j<=4; j++) {
            a[i][j] = rand() % 90 + 10;
            printf("%2d ", a[i][j]);
        }
        printf("\n");
    }
    
    for (i=0; i<=4; i++) {
        rowIsSorted = 0;
        
        while (rowIsSorted==0) {
            rowIsSorted = 1;
            
            for (j=0; j<=3; j++) {
                if ((i % 2 == 1) && (a[i][j]>a[i][j+1])) {
                    swapElements(&a[i][j], &a[i][j+1]);
                    rowIsSorted = 0;
                } else
                    if ((i % 2 == 0) && (a[i][j]<a[i][j+1])) {
                        swapElements(&a[i][j], &a[i][j+1]);
                        rowIsSorted = 0;
                    }
            }
        }
    }
    
    printf("\nEdited array:\n");
    for (i=0; i<=4; i++) {
        for (j=0; j<=4; j++) {
            printf("%2d ", a[i][j]);
        }
        printf("\n");
    }
    
    return 0;
}
