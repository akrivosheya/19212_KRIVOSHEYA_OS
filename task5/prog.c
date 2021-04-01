#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

#define DEFAULTSIZE 1
#define MAXLENGTH 100
#define BADROW -1

typedef struct line_t{
        size_t length;
        off_t offset;
} line;

void clear(line** tab, size_t size){
        for(int i = 0; i < size; ++i){
                free(tab[i]);
        }
}

int resize(line*** tab, size_t *size){
        line** newTab;
        if(!(newTab = (line**)realloc(*tab, *size * 2 * sizeof(line*)))){
                return 0;
        }
        *tab = newTab;
        *size *= 2;
        return 1;
}

int createLine(line** newLine, size_t length, off_t offset){
        *newLine = (line*)malloc(sizeof(line));
        if(!(*newLine)){
                return 0;
        }
        (*newLine)->length = length;
        (*newLine)->offset = offset - length;
        return 1;
}

int createTab(int fd, line*** tab, size_t *size){
        size_t length = 0;
        off_t offset = 0;
        char symb;
        size_t count;
        int i = 0;
        while((count = read(fd, &symb, sizeof(char))) > 0){
                ++length;
                ++offset;
                if(symb == '\n'){
                        if(i == *size){
                                if(!resize(tab, size)){
                                        clear(*tab, *size);
                                        return 0;
                                }
                        }
                        if(!createLine(&((*tab)[i]), length, offset)){
                                clear(*tab, *size);
                                return 0;
                        }
                        length = 0;
                        ++i;
                }
        }
        if(count < 0){
                perror("Can't read file");
                clear(*tab, *size);
                return 0;
        }
        *size = i;
        return 1;
}

void printTab(line** tab, int size){
        for(int i = 0; i < size && tab[i]; ++i){
                printf("length - %d; offset -  %d\n", tab[i]->length, tab[i]->offset);
        }
}

void getRow(int* row){
        int count;
        if(!(scanf("%d", row) > 0)){
                *row = BADROW;
        }
}

int printLine(char* string, int length){
        for(int i = 0; i < length; ++i){
                if(putchar(string[i]) == EOF){
                        return 0;
                }
        }
        return 1;
}

int readRows(int fd, line** tab, int size){
        int row;
        char string[MAXLENGTH];
        getRow(&row);
        while(row != 0){
                if(row == BADROW){
                        printf("Bad row\n");
                        return 1;
                }
                else if(row > size){
                        printf("Too big number of row\n");
                }
                else{
                        if(lseek(fd, tab[row - 1]->offset, SEEK_SET) < 0){
                                return 0;
                        }
                        if(read(fd, string, tab[row - 1]->length) < 0){
                                return 0;
                        }
                        if(!printLine(string, tab[row - 1]->length)){
                                return 0;
                        }
                }
                getRow(&row);
        }
        return 1;
}

int main(int argc, char* argv[]){
        if(argc < 2){
                printf("Needs argument\n");
                return 0;
        }
        int fd = open(argv[1], O_RDONLY);
        if(fd < 0){
                perror("Can't open file");
                return 0;
        }
        line** tab = (line**)calloc(DEFAULTSIZE, sizeof(line*));
        if(!tab){
                printf("Can't get memory\n");
                close(fd);
                return 0;
        }
        size_t size = DEFAULTSIZE;
        if(!createTab(fd, &tab, &size)){
                free(tab);
                printf("Can't create tab\n");
                close(fd);
                return 0;
        }
        //printTab(tab, size);
        printf("File has %d rows\nEnter index of row:\n", size);
        if(!readRows(fd, tab, size)){
                printf("Can't read file\n");
        }
        clear(tab, size);
        free(tab);
        close(fd);
        return 0;
}
