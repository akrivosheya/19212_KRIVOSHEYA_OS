#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 100

typedef struct list_t{
        char* line;
        struct list_t* next;
} list;

int putLine(list** last, char* line){
        size_t size = strlen(line);
        char* newLine = (char*)malloc((size + 1) * sizeof(char));
        if(!newLine){
                return 0;
        }
        if(!(*last)){
                *last = (list*)malloc(sizeof(list));
        }
        else{
                (*last)->next = (list*)malloc(sizeof(list));
                *last = (*last)->next;
        }
        if(!(*last)){
                free(newLine);
                return 0;
        }
        (*last)->next = NULL;
        strcpy(newLine, line);
        (*last)->line = newLine;
        return 1;
}

void printList(list* root){
        list* next = root;
        while(next){
                printf("%s", next->line);
                next = next->next;
        }
}

int main(){
        char line[MAX];
        list* root = NULL;
        list* last = NULL;
        while(fgets(line, MAX, stdin)){
                if(line[0] == '.'){
                        break;
                }
                if(!putLine(&last, line)){
                        break;
                }
                if(!root){
                        root = last;
                }
        }
        printList(root);
        return 0;
}
