//
//  main.c
//  L6_2
//
//  Created by Михаил Ковалевский on 11.10.2019.
//  Copyright © 2019 Mikhail Kavaleuski. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#define EMPLOYEE_COUNT 5
#define STRLENGTH 100

const char fullNames[EMPLOYEE_COUNT][STRLENGTH] = {"CVEKO VLADISLAV VASILIEVICH","BKAVALEUSKI MIKHAIL YURIEVICH","EZABENKO TAMARA IROREVNA","DBARYKO ILYA YURIEVICH","ARUSINOVICH ANGELINA ALEXANDROVNA"};

int main(int argc, const char * argv[]) {
    FILE *F;
    F = fopen("/Users/ixasthur/Desktop/Dev^_^/C/PL/L6/LIST_1.txt", "w+");
    int i;
    for (i = 0; i<EMPLOYEE_COUNT-2; i++) {
        fwrite(&fullNames[i], sizeof(char), STRLENGTH, F);
    }
    fclose(F);
    
    F = fopen("/Users/ixasthur/Desktop/Dev^_^/C/PL/L6/LIST_2.txt", "w+");
    for (; i<EMPLOYEE_COUNT; i++) {
        fwrite(&fullNames[i], sizeof(char), STRLENGTH, F);
    }
    fclose(F);
    
    
    
    char list[EMPLOYEE_COUNT][STRLENGTH];
    char element[STRLENGTH];
    i = 0;
    
    F = fopen("/Users/ixasthur/Desktop/Dev^_^/C/PL/L6/LIST_1.txt", "r+");
    while (fread(&element, sizeof(char), STRLENGTH, F)) {
        strcpy(list[i], element);
        i++;
    }
    fclose(F);
    
    F = fopen("/Users/ixasthur/Desktop/Dev^_^/C/PL/L6/LIST_2.txt", "r+");
    while (fread(&element, sizeof(char), STRLENGTH, F)) {
        strcpy(list[i], element);
        i++;
    }
    fclose(F);
    
    int sorted = 0;
    while (!sorted) {
        sorted = 1;
        for (i=0; i<EMPLOYEE_COUNT-1; i++) {
            if(strcmp(list[i], list[i+1])>0){
                sorted = 0;
                
                char buff[STRLENGTH];
                strcpy(buff, list[i]);
                strcpy(list[i], list[i+1]);
                strcpy(list[i+1], buff);
            }
        }
    }
    
    F = fopen("/Users/ixasthur/Desktop/Dev^_^/C/PL/L6/LIST_FULL.txt", "w+");
    for (i=0; i<EMPLOYEE_COUNT; i++) {
        int q = 0;
        while (list[i][q] != '\0') {
            fwrite(&list[i][q], sizeof(char), 1, F);
            q++;
        }
        char newLine = '\n';
        fwrite(&newLine, sizeof(char), 1, F);
    }
    fclose(F);
    
    return 0;
}
