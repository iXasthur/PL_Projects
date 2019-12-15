//
//  main.c
//  L11_1
//
//  Created by Михаил Ковалевский on 27.11.2019.
//  Copyright © 2019 Михаил Ковалевский. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct leaf{
    char sym;
    struct leaf *right;
    struct leaf *left;
};

char pr[4] = {'+','-','*','/'};

struct leaf * addnode(char c, struct leaf *tree) {
    if (tree == NULL) {
        tree =(struct leaf *)calloc(1, sizeof(struct leaf));
        tree->sym = c;
        tree->left =  NULL;
        tree->right = NULL;
    }
    return tree;
}

void treePrintInf(struct leaf *tree) {
    if (tree!=NULL) {
        treePrintInf(tree->left);
        printf("%c",tree->sym);
        treePrintInf(tree->right);
    }
}


void treePrintPost(struct leaf *tree) {
    if (tree!=NULL) {
        treePrintPost(tree->left);
        treePrintPost(tree->right);
        printf("%c",tree->sym);
    }
}

void treePrintPref(struct leaf *tree) {
    if (tree!=NULL) {
        printf("%c",tree->sym);
        treePrintPref(tree->left);
        treePrintPref(tree->right);
    }
}

void printTree (struct leaf *tree, int n)
{
    if (tree == NULL)
        return;
    n+=5;
    
    printTree(tree->right, n);
    printf("\n");
    for (int i = 5; i<n; i++)
        printf(" ");
    printf("%c\n", tree->sym);
    printTree(tree->left, n);
}

struct leaf *turnExpressionToTree(char *expression, struct leaf *tree){
    int flg = 0;
    if (strlen(expression) == 1){
        tree  = addnode(expression[0], tree);
    } else
    for (int j = 0; j<4; j++) {
        int i = 0;
        while ((i<strlen(expression))&&!flg) {
            if (expression[i] == pr[j]) {
                flg = 1;
                tree = addnode(expression[i], tree);
                char boof[20];
                int z = 0;
                int q = 0;
                for (z = 0; z < i; z++)
                    boof[q++] = expression[z];
                boof[q] = '\0';
                tree->left = turnExpressionToTree(boof, tree->left);
                z++;
                q = 0;
                for (; z<strlen(expression); z++)
                    boof[q++] = expression[z];
                boof[q] = '\0';
                tree->right = turnExpressionToTree(boof, tree->right);
            }
            i++;
        }
    }
    return tree;
}

int main(int argc, const char * argv[]) {
    char expression[100];
    printf("Введите выражение в инфиксной форме\n");
    scanf("%s",expression);
    struct leaf *tree  = NULL;
    tree = turnExpressionToTree(expression, tree);
    printTree(tree, 0);
    printf("Инфиксная форма записи\n");
    treePrintInf(tree);
    printf("\n");
    printf("Обратная польская форма записи\n");
    treePrintPost(tree);
    printf("\n");
    printf("Польская форма записи\n");
    treePrintPref(tree);
    printf("\n");
    return 0;
}

