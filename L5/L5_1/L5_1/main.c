//
//  main.c
//  L5_1
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

struct dateOfBirth {
    int day;
    int month;
    int year;
};

struct employee {
    char fullName[STRLENGTH];
    int departmentNumber;
    struct dateOfBirth date;
};

const char fullNames[EMPLOYEE_COUNT][STRLENGTH] = {"VEKO VLADISLAV VASILIEVICH","KAVALEUSKI MIKHAIL YURIEVICH","ZABENKO TAMARA IROREVNA","BARYKO ILYA YURIEVICH","RUSINOVICH ANGELINA ALEXANDROVNA"};

int main() {
    srand(time(NULL));
    
    struct employee workers[EMPLOYEE_COUNT];
    int i;
    for (i = 0; i<EMPLOYEE_COUNT; i++) {
        strcpy(workers[i].fullName, fullNames[i]);
        workers[i].departmentNumber = rand() % 2 + 1000;
        struct dateOfBirth buffDate;
        buffDate.day = rand() % 30 + 1;
        buffDate.month = rand() % 12 + 1;
        buffDate.year = rand() % 50 + 1950;
        workers[i].date = buffDate;
    }
    
    printf("Initial array:\n");
    printf("--------------------\n");
    for (i = 0; i<EMPLOYEE_COUNT; i++) {
        printf("%s\n",workers[i].fullName);
        printf("%d\n",workers[i].departmentNumber);
        printf("%d/",workers[i].date.day);
        printf("%d/",workers[i].date.month);
        printf("%d\n",workers[i].date.year);
        printf("--------------------\n");
    }
    printf("\n\n");
    
    int currentDepartment;
    
    do {
        currentDepartment = 0;
        i = 0;
        while (currentDepartment == 0 && i<EMPLOYEE_COUNT){
            currentDepartment = workers[i].departmentNumber;
            i++;
        }
        if (currentDepartment != 0) {
            int overallAge = 0;
            int count = 0;
            for (i = 0; i<EMPLOYEE_COUNT; i++) {
                if (workers[i].departmentNumber == currentDepartment){
                    workers[i].departmentNumber = 0;
                    overallAge = overallAge + (CURRENTYEAR - workers[i].date.year);
                    count++;
                }
            }
            overallAge /= count;
            printf("Department: %d\n",currentDepartment);
            printf("Avg. age: %d\n\n",overallAge);
        }
    } while (currentDepartment != 0);
    
    return 0;
}
