//
//  main.c
//  L7_1
//
//  Created by Михаил Ковалевский on 24.10.2019.
//  Copyright © 2019 Mikhail Kavaleuski. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define HOME_DIRECTORY "/Users/ixasthur/Desktop/Dev^_^/C/PL/L7/FILES/"
#define INPUT_LENGTH 256

struct item {
    char name[INPUT_LENGTH];
    int price;
};

struct list_s {
    struct item data;
    struct list_s *next;
};

const unsigned long fileSignature = 3164124715;

FILE* openFile(FILE *F, const char *name, const char *mode){
    const unsigned long pathLength = strlen(HOME_DIRECTORY) + strlen(name);
    
    char *path;
    path = calloc(pathLength, sizeof(char));
    strcpy(path, HOME_DIRECTORY);
    path = strcat(path, name);
    
    F = fopen(path, mode);
    if (F != NULL) {
        return F; // TRUE
    } else {
        return NULL; // FALSE
    }
}

struct list_s* initHead(struct list_s *head){
    head = (struct list_s*)malloc(sizeof(struct list_s));
    strcpy(head->data.name, "");
    head->data.price = 0;
    head->next = NULL;
    return head;
}

void outputList(struct list_s *head){
    struct list_s *element = head->next;
    int i = 1;
    printf("\nLIST:\n");
    while (element != NULL) {
        printf("%d: %s (%d$)\n",i,element->data.name,element->data.price);
        element = element->next;
        i++;
    }
}

void addItem(struct list_s *head, struct item item){
    struct list_s *element = head;
    while (element->next != NULL) {
        element = element->next;
    }
    element->next = (struct list_s*)malloc(sizeof(struct list_s));
    element = element->next;
    
    element->data = item;
    element->next = NULL;
}

struct item inputItem(){
    struct item buff;
    char input[INPUT_LENGTH];
    
    printf("Name: ");
    scanf("%s",input);
    strcpy(buff.name, input);
    
    printf("Price: ");
    scanf("%s",input);
    buff.price = atoi(input);
    
    return buff;
}

int getItemCount(struct list_s *head){
    struct list_s *element = head->next;
    int i = 0;
    while (element != NULL) {
        i++;
        element = element->next;
    }
    
    return i;
}

void editItemByNumber(struct list_s *head, struct item item, int pos){
    struct list_s *element = head;
    int i = 0;
    while (i < pos) {
        i++;
        element = element->next;
    }
    element->data = item;
}

void removeItemByNumber(struct list_s *head, int pos){
    struct list_s *element = head;
    int i = 0;
    while (i < pos - 1) {
        i++;
        element = element->next;
    }
    struct list_s *buff;
    buff = element->next->next;
    free(element->next);
    element->next = buff;
}

void clearList(struct list_s *head){
    while (head->next != NULL) {
        removeItemByNumber(head, 1);
    }
}

void fillListWithSampleData(struct list_s *head){
    const struct item buff[] = {{"Ethereum",1000},{"IOTA",1},{"EOS",20},{"Cardano",2},{"Bitcoin",20000}};
    long unsigned count = sizeof(buff)/sizeof(struct item);
    long unsigned i = 0;
    while (i<count) {
        addItem(head, buff[i]);
        i++;
    }
}

void saveToFile(FILE *F,struct list_s *head){
    struct list_s *element = head->next;
    fwrite(&fileSignature, sizeof(unsigned long), 1, F);
    int count = getItemCount(head);
    fwrite(&count, sizeof(int), 1, F);
    while (element != NULL) {
        struct item buff = element->data;
        fwrite(&buff, sizeof(struct item), 1, F);
        element = element->next;
    }
}

void readFromFile(FILE *F,struct list_s *head){
    int i = 0;
    unsigned long buffSignature;
    fread(&buffSignature, sizeof(unsigned long), 1, F);
    if (buffSignature == fileSignature) {
    int count;
    fread(&count, sizeof(int), 1, F);
    
    while (i<count) {
        struct item buff;
        fread(&buff, sizeof(struct item), 1, F);
        addItem(head, buff);
        i++;
    }
    } else {
        printf("\nFILE IS CORRUPTED!\nUNABLE TO READ!\n");
    }
}

void editMenu(FILE *F, const char *fileName){
    int rdyToExit = 0;
    int shouldShowMenu = 1;
    const char menuStringFirst[] = "\nEDIT MENU(FILE:";
    const char menuStringSeccond[] = ")\n1.Output data\n2.Add item\n3.Edit item\n4.Remove item\n9.Fill with sample data\n0.Save and go back\n";
    
    struct list_s *head = NULL;
    head = initHead(head);
    
    openFile(F, fileName, "r");
    readFromFile(F, head);
    fclose(F);
    
    while (!rdyToExit) {
        if (shouldShowMenu) {
            printf("%s",menuStringFirst);
            printf(HOME_DIRECTORY);
            printf("%s", fileName);
            printf("%s",menuStringSeccond);
            shouldShowMenu = 0;
        }
        printf("-> ");
        char input[INPUT_LENGTH];
        scanf("%s",input);
        int menuItem;
        if (input[0]>='0' && input[0]<='9') {
            menuItem = atoi(input);
        } else {
            menuItem = -1;
        }
        
        switch (menuItem) {
            case 1: {
                outputList(head);
                shouldShowMenu = 1;
                break;
            }
            case 2: {
                struct item buff = inputItem();
                addItem(head, buff);
                shouldShowMenu = 1;
                break;
            }
            case 3: {
                int n = 0;
                printf("Number of item to edit: ");
                scanf("%d",&n);
                if (n > 0 && n <= getItemCount(head)) {
                    struct item buff = inputItem();
                    editItemByNumber(head, buff,n);
                    shouldShowMenu = 1;
                    printf("\nSuccessfully edited %d item!\n",n);
                } else {
                    printf("Item does not exist!\n");
                }
                break;
            }
            case 4: {
                int n = 0;
                printf("Number of item to remove: ");
                scanf("%d",&n);
                if (n > 0 && n <= getItemCount(head)) {
                    removeItemByNumber(head, n);
                    shouldShowMenu = 1;
                    printf("\nSuccessfully removed %d item!\n",n);
                } else {
                    printf("Item does not exist!\n");
                }
                break;
            }
            case 9: {
                clearList(head);
                fillListWithSampleData(head);
                printf("\nSuccessfully filled list!\n");
                shouldShowMenu = 1;
                break;
            }
            case 0: {
                openFile(F, fileName, "w");
                saveToFile(F, head);
                fclose(F);
                rdyToExit = 1;
                break;
            }
            default: {
                printf("Invalid input!\n");
            }
        }
    }
}

int main() {
    FILE *F = NULL;
    char fileName[INPUT_LENGTH];
    strcpy(fileName, "");
    strcpy(fileName, "buff.txt");
    
    int rdyToExit = 0;
    int shouldShowMenu = 1;
    const char menuStringFirst[] = "\nMAIN MENU(FILE:";
    const char menuStringSeccond[] = ")\n1.Create file\n2.Open file\n3.Select file\n0.Exit\n";
    
    while (!rdyToExit) {
        if (shouldShowMenu) {
            printf("%s",menuStringFirst);
            if (strcmp(fileName, "") != 0) {
                printf(HOME_DIRECTORY);
                printf("%s", fileName);
            } else {
                printf(" NULL");
            }
            printf("%s",menuStringSeccond);
            shouldShowMenu = 0;
        }
        printf("-> ");
        char input[INPUT_LENGTH];
        scanf("%s",input);
        int menuItem;
        if (input[0]>='0' && input[0]<='9') {
            menuItem = atoi(input);
        } else {
            menuItem = -1;
        }
        
        switch (menuItem) {
            case 1:
                if (strcmp(fileName, "") != 0) {
                    // Open file
                    F = openFile(F, fileName, "w");
                    int count = 0;
                    fwrite(&fileSignature, sizeof(unsigned long), 1, F);
                    fwrite(&count, sizeof(int), 1, F);
                    fclose(F);
                    if (F != NULL) {
                        editMenu(F, fileName);
                        shouldShowMenu = 1;
                    } else {
                        printf("Error creating file!\n");
                    }
                } else {
                    printf("File isn't open!\n");
                }
                break;
            case 2:
                if (strcmp(fileName, "") != 0) {
                    // Open file
                    F = openFile(F, fileName, "r") ;
                    fclose(F);
                    if (F != NULL) {
                        editMenu(F, fileName);
                        shouldShowMenu = 1;
                    } else {
                        printf("File does not exist!\n");
                    }
                } else {
                    printf("File isn't open!\n");
                }
                break;
            case 3:
                printf("Please input file name: ");
                scanf("%s",fileName);
                shouldShowMenu = 1;
                break;
            case 0:
                rdyToExit = 1;
                break;
            default:
                printf("Invalid input!\n");
        }
    }
    
    return 0;
}
