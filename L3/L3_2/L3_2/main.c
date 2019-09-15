//
//  main.c
//  L3_2
//
//  Created by Михаил Ковалевский on 13/09/2019.
//  Copyright © 2019 Mikhail Kavaleuski. All rights reserved.
//

#include <stdio.h>

int main(int argc, const char * argv[]) {
    char s[256];
    printf("Input string:\n");
    scanf("%s",s);
    int l = 0;
    while (s[l] != '\0') {
        l += 1;
    }
    printf("Length: %d\n", l);
    
    char buff;
    for (int i = 0; i<=((l-1) - l%2); i+=2) {
        buff = s[i];
        s[i] = s[i+1];
        s[i+1] = buff;
    }
    
    printf("New string:\n%s\n",s);
    return 0;
}
