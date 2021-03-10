#include <sys/types.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define YEARFORREF 1900

int main(){
        if(putenv("TZ=America/Los_Angeles") < 0){
                perror("Can't change TZ");
                return 0;
        }
        time_t now;
        struct tm *califTime;
        if(time(&now) < 0){
                perror("Can't get time");
                return 0;
        }
        califTime = localtime(&now);
        printf("California time: %02d/%02d/%d, %02d:%02d:%02d\n",
                califTime->tm_mday,
                califTime->tm_mon + 1,
                califTime->tm_year + YEARFORREF,
                califTime->tm_hour,
                califTime->tm_min,
                califTime->tm_sec);
        if(putenv("TZ=") < 0){
                perror("Can't change TZ");
                return 0;
        }
        return 0;
}
