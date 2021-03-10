#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main(int argc, char* argv[]) {
        if(argc < 0) {
                printf("There are not options\n");
        }
        char options[] = "ispuU:cC:dvV:";
        int c;
        while((c = getopt(argc, argv, options)) != EOF) {
                switch(c) {
                case '?':
                        printf("invalid option is %c\n", optopt);
                        break;
                case 'i':
                        printf("actual id: %d\neffective id: %d\n", getuid(), geteuid());
                        break;
                case 's':
                        if(setpgrp()) {
                                perror("Can't create new group");
                                break;
                        }
                case '
        }
        return 0;
}
