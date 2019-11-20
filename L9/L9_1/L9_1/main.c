//
//  main.c
//  L9_1
//
//  Created by Михаил Ковалевский on 20.11.2019.
//  Copyright © 2019 Mikhail Kavaleuski. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct TreeElement {
    int key;
    struct TreeElement *left;
    struct TreeElement *right;
};

struct TreeElement* createHead(struct TreeElement *head){
    head = (struct TreeElement*)malloc(sizeof(struct TreeElement));
    head->key = 0;
    head->left = NULL;
    head->right = NULL;
    return head;
}

struct TreeElement* createElement(struct TreeElement *element, int key){
    element = (struct TreeElement*)malloc(sizeof(struct TreeElement));
    element->key = key;
    element->left = NULL;
    element->right = NULL;
    return element;
}

void insertElement(struct TreeElement *head, struct TreeElement *element){
    if (head != NULL) {
        if (head->key > element->key) {
            if (head->left != NULL) {
                insertElement(head->left, element);
            } else {
                head->left = element;
            }
        } else
            if (head->key < element->key) {
                if (head->right != NULL) {
                    insertElement(head->right, element);
                } else {
                    head->right = element;
                }
            }
    }
}

void clearTreeREC(struct TreeElement *head, struct TreeElement *parent){
    if (head != NULL) {
        if (parent != NULL && head->left == NULL && head->right == NULL) {
            printf("Removing element with key = %d\n", head->key);
            if (parent != NULL) {
                if (parent->left == head) {
                    parent->left = NULL;
                } else {
                    parent->right = NULL;
                }
            }
            free(head);
        } else {
            while (head->left != NULL) {
                clearTreeREC(head->left, head);
            }
            while (head->right != NULL) {
                clearTreeREC(head->right, head);
            }
        }
    }
}

void clearTree(struct TreeElement *head){
    if (head != NULL) {
        clearTreeREC(head, NULL);
        printf("Removing element with key = %d\n", head->key);
        free(head);
    }
}

void getTreeDepth(struct TreeElement *head, int depth, int *maxDepth){
    if (head != NULL) {
        if (*maxDepth < depth) {
            *maxDepth = depth;
        }
        if (head->left != NULL) {
            getTreeDepth(head->left, depth+1, maxDepth);
        }
        if (head->right != NULL) {
            getTreeDepth(head->right, depth+1, maxDepth);
        }
    }
}

int getIntLength(int v){
    int ret = 0;
    while (v != 0) {
        v = v / 10;
        ret++;
    }
    return ret;
}

void removeElementFromTreeREC(struct TreeElement *head, int *stop, int value){
    if (head != NULL) {
        if (!(*stop) && head->left != NULL) {
            if (head->left->key == value) {
                clearTree(head->left);
                head->left = NULL;
                *stop = 1;
            } else {
                removeElementFromTreeREC(head->left, stop, value);
            }
        }
        if (!(*stop) && head->right != NULL) {
            if (head->right->key == value) {
                clearTree(head->right);
                head->right = NULL;
                *stop = 1;
            } else {
                removeElementFromTreeREC(head->right, stop, value);
            }
        }
    }
}

void removeElementFromTree(struct TreeElement **head, int value){
    if ((*head) != NULL) {
        if ((*head)->key == value) {
            clearTree(*head);
            *head = NULL;
        } else {
            int stop = 0;
            removeElementFromTreeREC(*head, &stop, value);
        }
    }
}

void outoutTreeHZ(struct TreeElement *head, int xOffest){
    int numLength = getIntLength(head->key);
    char buffStr[xOffest+numLength];
    strcpy(buffStr, "");
    for (int i = 0; i<xOffest; i++) {
        strcat(buffStr, " ");
    }
    
    char numStr[numLength];
    snprintf(numStr, sizeof(head->key), "%d", head->key);
    strcat(buffStr, numStr);
    
    printf("%s\n",buffStr);
    
    if (head->left != NULL) {
        outoutTreeHZ(head->left, xOffest+numLength*2);
    }
    if (head->right != NULL) {
        outoutTreeHZ(head->right, xOffest+numLength*2);
    }
}

void outputTree(struct TreeElement *head){
    if (head != NULL) {
        int depth = 0;
        getTreeDepth(head, 0, &depth);
        printf("Tree depth: %d\n", depth);
        
        outoutTreeHZ(head, 0);
    } else {
        printf("Tree is empty!");
    }
}

int main() {
    
    const int arr[9] = {8,3,10,1,6,4,7,14,13};
    struct TreeElement *head = NULL;
    head = createElement(head, arr[0]);
    
    for (int i = 1; i<(sizeof(arr)/sizeof(arr[0])); i++) {
        struct TreeElement *element = NULL;
        element = createElement(element, arr[i]);
//        printf("Adding element with key = %d\n", element->key);
        insertElement(head, element);
    }
    
    outputTree(head);
    printf("\n");
    
    removeElementFromTree(&head, 10);
    printf("\n");
    
    outputTree(head);
    printf("\n");
    
    printf("Clearing memory...\n");
    clearTree(head);
    printf("\n");
    
    return 0;
}
