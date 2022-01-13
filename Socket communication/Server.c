#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <string.h>

void getString(char arr[50][5]){
    char toRet[5];
    for(int i = 0;i<50;i++){
        for(int j =0 ;j<5;j++){
            arr[i][j] = (rand() % (122 - 97 + 1)) + 97;
        }
    }

}

#define SOCKET_NAME "naman"
#define BUFFER_SIZE 128

int main(){

    struct sockaddr_un socket_add;
    int ret;
    int fd;
    char buffer[BUFFER_SIZE];
    fd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (fd == -1) {
        perror("socket not created");
        exit(1);
    }

    memset(&socket_add, 0, sizeof(struct sockaddr_un));
    socket_add.sun_family = AF_UNIX;
    strncpy(socket_add.sun_path, SOCKET_NAME, sizeof(socket_add.sun_path) - 1);

    char arr[50][5];
    getString(arr);
    ret = connect (fd, (const struct sockaddr *) &socket_add, sizeof(struct sockaddr_un));
    if (ret == -1) { 
        printf("P2 has not started yet.");
        exit(EXIT_FAILURE);
    }

    
    int flag = 0;  
    // int k = (rand() % (50 - 0 + 1)) + 0;
    int k = 0;
    while (k < 50) { 
       if(flag){   
        memset(buffer, 0, BUFFER_SIZE);  
        ret = read(fd, buffer, BUFFER_SIZE);
        if (ret == -1) {
            printf("could not read");
            exit(EXIT_FAILURE);
        }

        buffer[BUFFER_SIZE - 1] = 0;
        k = atoi(buffer);
        printf("Recieved ID = %d\n", k);
        k+=1;
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
        ret = write(fd, temp, sizeof(temp));
        if (ret == -1) {
            perror("write");
            break;
        }
        sleep(1);


    }
    close(fd);
    exit(EXIT_SUCCESS);
}