//
//  main.c
//  L8_1
//
//  Created by Михаил Ковалевский on 01.11.2019.
//  Copyright © 2019 Mikhail Kavaleuski. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define INPUT_LENGTH 256

struct stack_t {
    int v;
    struct stack_t *next;
};

struct stack_t* initHead(struct stack_t *head) {
    head = (struct stack_t*)malloc(sizeof(struct stack_t));
    head->v = 0;
    head->next = NULL;
    return head;
}

void push(struct stack_t *head, int value) {
    struct stack_t *next = head->next;
    struct stack_t *buff = (struct stack_t*)malloc(sizeof(struct stack_t));
    buff->v = value;
    buff->next = next;
    head->next = buff;
}

int pop(struct stack_t *head) {
    struct stack_t *next = head->next;
    int ret = -1;
    if (next != NULL) {
        ret = next->v;
        next = next->next;
    }
    free(head->next);
    head->next = next;
    return ret;
}

void outputStack(struct stack_t *head) {
    struct stack_t *element = head->next;
    while (element!=NULL) {
        printf("%d ",element->v);
        element = element->next;
    }
    printf("\n");
}

int getStackSize(struct stack_t *head) {
    struct stack_t *element = head->next;
    int i = 0;
    while (element!=NULL) {
        i++;
        element = element->next;
    }
    return i;
}

int main(int argc, const char * argv[]) {
    struct stack_t *stack_head_1 = NULL;
    stack_head_1 = initHead(stack_head_1);
    
    struct stack_t *stack_head_2 = NULL;
    stack_head_2 = initHead(stack_head_2);
    
    struct stack_t *stack_head_3 = NULL;
    stack_head_3 = initHead(stack_head_3);
    
    push(stack_head_1, 5);
    push(stack_head_1, 4);
    push(stack_head_1, 3);
    push(stack_head_1, 2);
    push(stack_head_1, 1);
    printf("STACK 1: ");
    outputStack(stack_head_1);
    
    push(stack_head_2, 12);
    push(stack_head_2, 11);
    push(stack_head_2, 10);
    push(stack_head_2, 9);
    push(stack_head_2, 8);
    push(stack_head_2, 7);
    push(stack_head_2, 6);
    printf("STACK 2: ");
    outputStack(stack_head_2);
    
    int count = getStackSize(stack_head_1) + getStackSize(stack_head_2);
    int arr[count];
    int i = 0;
    int v = 1;
    while (v != -1) {
        v = pop(stack_head_1);
        if (v != -1) {
            arr[i] = v;
            i++;
        }
    }
    v = 1;
    while (v != -1) {
        v = pop(stack_head_2);
        if (v != -1) {
            arr[i] = v;
            i++;
        }
    }
    
    for (i = count-1; i>=0; i--) {
        push(stack_head_3, arr[i]);
    }
    
    printf("STACK 3: ");
    outputStack(stack_head_3);
    
    return 0;
}
