//
//  main.c
//  L6_1
//
//  Created by Михаил Ковалевский on 10.10.2019.
//  Copyright © 2019 Mikhail Kavaleuski. All rights reserved.
//

#include <stdio.h>
#define ELEMENT_COUNT 10

int main(int argc, const char * argv[]) {
    FILE *F1, *F2;
    F1 = fopen("/Users/ixasthur/Desktop/Dev^_^/C/PL/L6/F1.txt", "w+");
    F2 = fopen("/Users/ixasthur/Desktop/Dev^_^/C/PL/L6/F2.txt", "w+");
    for (int i = ELEMENT_COUNT; i>0; i--) {
        int j = i*2;
        fwrite(&i, sizeof(int), 1, F1);
        fwrite(&j, sizeof(int), 1, F2);
    }
    fclose(F1);
    fclose(F2);
    
    F1 = fopen("/Users/ixasthur/Desktop/Dev^_^/C/PL/L6/F1.txt", "r+");
    F2 = fopen("/Users/ixasthur/Desktop/Dev^_^/C/PL/L6/F2.txt", "r+");
    int arrF1[ELEMENT_COUNT], arrF2[ELEMENT_COUNT];
    for (int i=0; i<ELEMENT_COUNT; i++) {
        fread(&arrF1[i], sizeof(int), 1, F1);
        fread(&arrF2[i], sizeof(int), 1, F2);
    }
    fclose(F1);
    fclose(F2);
    
    int arrF3[ELEMENT_COUNT*2];
    printf("F1:\n");
    for (int i=0; i<ELEMENT_COUNT; i++) {
        arrF3[i] = arrF1[i];
        printf("%d ",arrF1[i]);
    }
    printf("\nF2:\n");
    for (int i=0; i<ELEMENT_COUNT; i++) {
        arrF3[ELEMENT_COUNT+i] = arrF2[i];
        printf("%d ",arrF2[i]);
    }
    printf("\n");
    
    int sorted = 0;
    while (!sorted) {
        sorted = 1;
        for (int i = 0; i<(ELEMENT_COUNT*2)-1; i++) {
            if (arrF3[i] > arrF3[i+1]) {
                sorted = 0;
                int buff = arrF3[i];
                arrF3[i] = arrF3[i+1];
                arrF3[i+1] = buff;
            }
        }
    }
    
    F1 = fopen("/Users/ixasthur/Desktop/Dev^_^/C/PL/L6/F3.txt", "w+");
    for (int i=0; i<ELEMENT_COUNT*2; i++) {
        fwrite(&arrF3[i], sizeof(int), 1, F1);
    }
    fclose(F1);
    
    printf("F3:\n");
    F1 = fopen("/Users/ixasthur/Desktop/Dev^_^/C/PL/L6/F3.txt", "r+");
    for (int i=0; i<ELEMENT_COUNT*2; i++) {
        int buff;
        fread(&buff, sizeof(int), 1, F1);
        printf("%d ", buff);
    }
    fclose(F1);
    printf("\n");
    
    
    return 0;
}
