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
int main(){
    
    char buffer[BUFFER_SIZE];
    int fd;
    for(int i = 0;i<11;i++) {
        fd = open("namanFifo", O_RDONLY);
        memset(buffer, 0, BUFFER_SIZE);
        printf("Waiting for string packet from P1\n");
        int r = read(fd, buffer, BUFFER_SIZE);
        close(fd);
        
        char tempBuff[BUFFER_SIZE];
            strncpy(tempBuff, buffer, 2);
            int index = atoi(tempBuff);
            int ptr;
            if(index<10){
                ptr = 2;
            }else{
                ptr = 3;
            }
            char first[7];
            first[0] = buffer[ptr];
            first[1] = buffer[ptr+1];
            first[2] = buffer[ptr+2];
            first[3] = buffer[ptr+3];
            first[4] = buffer[ptr+4];

            char second[7];
            second[0] = buffer[ptr+6];
            second[1] = buffer[ptr+7];
            second[2] = buffer[ptr+8];
            second[3] = buffer[ptr+9];
            second[4] = buffer[ptr+10];

            char third[7];
            third[0] = buffer[ptr+12];
            third[1] = buffer[ptr+13];
            third[2] = buffer[ptr+14];
            third[3] = buffer[ptr+15];
            third[4] = buffer[ptr+16];


            char fourth[7];
            fourth[0] = buffer[ptr+18];
            fourth[1] = buffer[ptr+19];
            fourth[2] = buffer[ptr+20];
            fourth[3] = buffer[ptr+21];
            fourth[4] = buffer[ptr+22];


            char fifth[7];
            fifth[0] = buffer[ptr+24];
            fifth[1] = buffer[ptr+25];
            fifth[2] = buffer[ptr+26];
            fifth[3] = buffer[ptr+27];
            fifth[4] = buffer[ptr+28];
            int toSend = 49;
            if(index<50){
                printf("ID:%d :%s \n", index, first);
                toSend = index;
            }
            if(index+1<50){
                printf("ID:%d :%s \n", index+1, second);
                toSend = index+1;
            }
            if(index+2<50){
                printf("ID:%d :%s \n", index+2, third);
                toSend = index+2;
            }
            if(index+3<50){
                printf("ID:%d :%s \n", index+3, fourth);
                toSend = index+3;
            }
            if(index+5<50){
                printf("ID:%d :%s \n", index+4, fifth);
                toSend = index+4;
            }

            memset(buffer, 0, BUFFER_SIZE);
            sprintf(buffer, "%d", toSend);

            printf("Sending back the highest ID: %d\n", toSend);
            sleep(1);
            fd = open("namanFifo", O_WRONLY);
            int w = write(fd, buffer, BUFFER_SIZE);
            if (fd == -1) {
                printf("Could not write\n");
                exit(EXIT_FAILURE);
            }
            close(fd);
            if((index+4)>=49){
                break;
            }

    }

    


}