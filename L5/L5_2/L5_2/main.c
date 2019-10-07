//
//  main.c
//  L5_2
//
//  Created by Михаил Ковалевский on 04/10/2019.
//  Copyright © 2019 Mikhail Kavaleuski. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define EMPLOYEE_COUNT 5
#define STRLENGTH 100
#define CURRENTYEAR 2019

struct employee {
    char fullName[STRLENGTH];
    double avgMark;
    int income;
};

const char fullNames[EMPLOYEE_COUNT][STRLENGTH] = {"VEKO VLADISLAV VASILIEVICH","KAVALEUSKI MIKHAIL YURIEVICH","ZABENKO TAMARA IROREVNA","BARYKO ILYA YURIEVICH","RUSINOVICH ANGELINA ALEXANDROVNA"};

int main() {
    srand(time(NULL));
    
    struct employee workers[EMPLOYEE_COUNT];
    int i;
    for (i = 0; i<EMPLOYEE_COUNT; i++) {
        strcpy(workers[i].fullName, fullNames[i]);
        workers[i].avgMark = (double)(rand() % 10) + 1/(double)(rand() % 101);
        workers[i].income = rand() % 50000;
    }
    
    printf("Initial array:\n");
    printf("--------------------\n");
    for (i = 0; i<EMPLOYEE_COUNT; i++) {
        printf("%s\n",workers[i].fullName);
        printf("%.2lf\n",workers[i].avgMark);
        printf("%d$\n",workers[i].income);
        printf("--------------------\n");
    }
    printf("\n\n");
    
    int sorted = 0;
    while (!sorted) {
        sorted = 1;
        for (i = 0; i<EMPLOYEE_COUNT-1; i++) {
            if (workers[i].income < workers[i+1].income) {
                struct employee buffWorker;
                buffWorker = workers[i];
                workers[i] = workers[i+1];
                workers[i+1] = buffWorker;
                sorted = 0;
            }
        }
    }
    
    printf("Sorted array:\n");
    printf("--------------------\n");
    for (i = 0; i<EMPLOYEE_COUNT; i++) {
        printf("%s\n",workers[i].fullName);
        printf("%.2lf\n",workers[i].avgMark);
        printf("%d$\n",workers[i].income);
        printf("--------------------\n");
    }
    printf("\n\n");
    
    return 0;
}
