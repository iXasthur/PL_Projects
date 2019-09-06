//
//  main.c
//  L1
//
//  Created by Михаил Ковалевский on 05/09/2019.
//  Copyright © 2019 Mikhail Kavaleuski. All rights reserved.
//

#include <stdio.h>

void task18(){
    int i, n = 0;
    double sum = 0;
    
    printf("\nPerforming task 18\nInput n:\n-> ");
    scanf("%d", &n);
    for (i = 1; i<=n; i++) {
        sum = sum + 1.0/i;
    }
    
    printf("Sum: %lf\n\n", sum);
}

void task26(){
    int i, n = 0;
    
    printf("\nPerforming task 26\nInput n:\n-> ");
    scanf("%d", &n);
    
    if (n > 0) {
        printf("Natural dividers: 1");
        for (i = 2; i<=n/2; i++) {
            if (n % i == 0) {
                printf(" %d", i);
            }
        }
        printf(" %d", n);
    } else {
        printf("n is not a natural number");
    }
    
    printf("\n\n");
}

int main() {
    int x, rdyToExit = 0, infoIsShown = 0;
    
    while (rdyToExit != 1) {
        if (infoIsShown == 0) {
            printf("Choose task:\n1. 18\n2. 26\n3. Exit\n");
            infoIsShown = 1;
        }
        
        printf("-> ");
        scanf("%d", &x);
        
        switch (x) {
            case 1:
                task18();
                infoIsShown = 0;
                break;
            case 2:
                task26();
                infoIsShown = 0;
                break;
            case 3:
                rdyToExit = 1;
                break;
            default:
                printf("Invalid input\n");
                break;
        }
    }
    
    return 0;
}
