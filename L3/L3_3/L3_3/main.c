//
//  main.c
//  L3_3
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
    
    int i = 0, q = 0;
    if (l >= 1) {
        int symbols[50][2], symbolCount = 1;
        symbols[0][0] = s[0];
        symbols[0][1] = 1;
        for (i = 1; i<=(l-1); i++) {
            if (s[i] != '_') {
                int foundSymbol = 0;
                for (q = 0; q<=(symbolCount-1); q++) {
                    if (symbols[q][0] == s[i]) {
                        symbols[q][1] += 1;
                        foundSymbol = 1;
                    }
                }
                
                if (!foundSymbol) {
                    symbols[symbolCount][0] = s[i];
                    symbols[symbolCount][1] = 1;
                    symbolCount += 1;
                }
            }
        }
        
        for (i = 0; i<=(symbolCount - 1); i++) {
            printf("%c%d",symbols[i][0],symbols[i][1]);
        }
        
        printf("\n");
    }
    
}
