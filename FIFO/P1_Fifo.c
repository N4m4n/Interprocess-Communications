#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <sys/un.h>
#include <unistd.h>
#include <errno.h>
#define BUFFER_SIZE 128
void getString(char arr[50][5]){
    char toRet[5];
    for(int i = 0;i<50;i++){
        for(int j =0 ;j<5;j++){
            arr[i][j] = (rand() % (122 - 97 + 1)) + 97;
        }
    }

}


int main(){

    int a = mkfifo("namanFifo", 0777);
    if(a==-1){
        if(errno!=EEXIST){
            printf("File creation error\n");
            return 1;
        }
    }

    char arr[50][5];
    getString(arr);

    int k = 0;
    char buffer[BUFFER_SIZE];
    int flag = 0;
    int fd;
    while(k<50){
        
        if(flag){
            memset(buffer, 0, BUFFER_SIZE);
            fd = open("namanFifo", O_RDONLY);
            int r = read(fd, buffer, BUFFER_SIZE);
            if (r == -1) {
                perror("read");
                exit(EXIT_FAILURE);
            }

            buffer[BUFFER_SIZE - 1] = 0;
            k = atoi(buffer);
            printf("Recieved ID = %d\n", k);
            k+=1;
            close(fd);
        }
        flag = 1;

        char temp[32] = "";

        sprintf(temp,"%d",k);
        strncat(temp, "\n", 2);
        strncat(temp, arr[k], 5);
        strncat(temp, "\n", 2);
        strncat(temp, arr[k+1], 5);
        strncat(temp, "\n", 2);
        strncat(temp, arr[k+2], 5);
        strncat(temp, "\n", 2);
        strncat(temp, arr[k+3], 5);
        strncat(temp, "\n", 2);
        strncat(temp, arr[k+4], 5);
        strncat(temp, "\n", 2);
        fd = open("namanFifo", O_WRONLY);
        int w = write(fd, temp, sizeof(temp));
        close(fd);

    }

    return 0;
}