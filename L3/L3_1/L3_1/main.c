//
//  main.c
//  L3
//
//  Created by Михаил Ковалевский on 13/09/2019.
//  Copyright © 2019 Mikhail Kavaleuski. All rights reserved.
//

#include <stdio.h>

int main() {
    char s[256];
    printf("Input string:\n");
    scanf("%s", s);
    int l = -1, foundEnding = 0;
    while (!foundEnding) {
        l += 1;
        if (s[l] == '\0') {
            foundEnding = 1;
        }
    }
    
    printf("Length: %d\n", l);
    if ((l-1)%2 == 0) {
        int midPos = (l-1)/2;
        printf("Middle symbol: %c\n", s[midPos]);
        
        for (int i = midPos; i<=(l-1); i++) {
            s[i] = s[i+1];
        }
        
        printf("New string:\n%s\n", s);
    } else {
        printf("There is no middle symbol\n");
    }
    
    return 0;
}
