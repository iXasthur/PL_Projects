//
//  main.c
//  PL_L12
//
//  Created by Михаил Ковалевский on 04.12.2019.
//  Copyright © 2019 Михаил Ковалевский. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

enum SYMBOL_TYPE {
    DOLLAR = 1,
    ZERO = 2,
    X = 3,
    DIGIT = 4,
    NOT_DIGIT = 5
};

enum SYMBOL_TYPE getSymbolType(char s, int state){
    if (state == 1 || state == 2) {
        if (s == '0') {
            return ZERO;
        } else
            if (s == 'x') {
                return X;
            } else
                if (s == '$') {
                    return DOLLAR;
                }
    } else
        if ((s>='a' && s<='f') ||
            (s>='A' && s<='F') ||
            (s>='0' && s<='9')) {
            return DIGIT;
        }
    return NOT_DIGIT;
};



int main(int argc, const char * argv[]) {
    // "ABCDE 0xABC 0xGA $ABC $GA 0x0"
    char text[] = "ABCDE 0xABC GA $ABC GA 0x0 0x $5 $0-0x5";
    unsigned long length = strlen(text) + 1;
    printf("Text(%lu): %s\n", length, text);
    int machine[7][6] = {
        {0, 0, 0, 0, 0, 0},
        {0, 3, 2, 0, 0, 0},
        {0, 0, 0, 3, 0, 0},
        {0, 0, 0, 0, 4, 0},
        {0, 0, 0, 0, 5, 6},
        {0, 0, 0, 0, 5, 6},
        {0, 0, 0, 0, 0, 0}
    };
    int machineFinalStates[7] = {-1, 0, 0, 0, 0, 0, 1};
    int currentState = 1;
    char buffStr[length];
    strcpy(buffStr, "");
    
    int i = 0;
    for (i = 0; i<length; i++) {
        char *buffSymbol;
        buffSymbol = (char*)malloc(sizeof(char)*2);
        buffSymbol[0] = text[i];
        buffSymbol[1] = '\0';
        strcat(buffStr, buffSymbol);
        currentState = machine[currentState][getSymbolType(text[i],currentState)];
        switch (machineFinalStates[currentState]) {
            case -1: {
                strcpy(buffStr, "");
                currentState = 1;
                break;
            }
            case 1: {
                unsigned long buffLength = strlen(buffStr) + 1;
                if (getSymbolType(buffStr[buffLength - 2], -1) == NOT_DIGIT) {
                    buffStr[buffLength - 2] = '\0';
                }
                printf("%s\n", buffStr);
                strcpy(buffStr, "");
                currentState = 1;
                break;
            }
            default:
                break;
        }
    }
    
    return 0;
}
