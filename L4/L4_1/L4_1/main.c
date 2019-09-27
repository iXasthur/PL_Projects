//
//  main.c
//  L4_1
//
//  Created by Михаил Ковалевский on 26/09/2019.
//  Copyright © 2019 Mikhail Kavaleuski. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define WORDLENGTH 20


struct translation {
    char initial[WORDLENGTH];
    char result[WORDLENGTH];
};

int main(int argc, const char * argv[]) {
    const int dictionaryLength = 5;
    const struct translation dictionary[dictionaryLength] = {{"this","это"},{"table","стол"},{"is",""},{"a",""},{"very","очень"}};
    char str[256];
    char resultStr[256];
    scanf("%s",str);
    
    char words[50][WORDLENGTH];
    int i = 0;
    int wordCount = 0;
    
    while (str[i] != '\0') {
        int wordPos = 0;
        char w[WORDLENGTH] = "";
        
        while (str[i] != '_' && str[i] != '\0'){
            w[wordPos] = str[i];
            wordPos++;
            i++;
        }
        
        if (strcmp(w, "") != 0) {
            strcpy(words[wordCount], w);
            wordCount++;
        }
        i++;
    }
    
//    for (i = 0; i<wordCount; i++) {
//        printf("%s\n", words[i]);
//    }
    
    int j = 0;
    int foundTranslation = 0;
    for (i = 0; i<wordCount; i++) {
        foundTranslation = 0;
        j = 0;

        while (!foundTranslation && j<dictionaryLength) {
            if (strcmp(words[i], dictionary[j].initial) == 0){
                foundTranslation = 1;
                
                if (strcmp(resultStr, "") == 0 && strcmp(dictionary[j].result, "") != 0) {
                    strcat(resultStr, dictionary[j].result);
                } else if (strcmp(dictionary[j].result, "") != 0){
                    
                    strcat(resultStr, "_");
                    strcat(resultStr, dictionary[j].result);
                }
            }
            j++;
        }
        
        if (!foundTranslation) {
            if (strcmp(resultStr, "") == 0 && strcmp(words[i], "") != 0) {
                strcat(resultStr, words[i]);
            } else if (strcmp(words[i], "") != 0){
                strcat(resultStr, "_");
                strcat(resultStr, words[i]);
            }
        }
    }
    
    printf("%s\n",resultStr);
    
    return 0;
}
