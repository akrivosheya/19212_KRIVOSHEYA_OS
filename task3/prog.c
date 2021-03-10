#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main() {
        FILE* file;
        if(!(file = fopen("file", "r"))) {
                perror("Can't open file");
        }
        else {
                fclose(file);
        }
        uid_t euid = geteuid();
        if(setuid(euid)){
                perror("Can't change ID");
        }
        if(!(file = fopen("file", "r"))) {
                perror("Can't open file");
        }
        else {
                fclose(file);
        }
        printf("%d\n", getuid());
        return 0;
}
