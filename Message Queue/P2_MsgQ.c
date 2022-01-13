#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BUFFER_SIZE 128 
struct mesg_buffer {
    long mesg_type;
    char mesg_text[100];
}; 
  
int main()
{
    key_t key;
    key_t key2;
    int msgid;
    int msgid2;
    struct mesg_buffer message;
    struct mesg_buffer message2;
    key = 1010;
    key2 = 1010101010;
    msgid = msgget(key, 0666 | IPC_CREAT);
    msgid2 = msgget(key2, 0666 | IPC_CREAT);
    message.mesg_type = 1;
    message2.mesg_type = 1;
    char buffer[BUFFER_SIZE];

    for(int i =0;i<11;i++){
        memset(buffer, 0, BUFFER_SIZE); 
        msgrcv(msgid, &message, sizeof(message), 1, 0);
        strncpy(buffer, message.mesg_text,sizeof(buffer));
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
        // printf("reads1\n");
        memset(message.mesg_text, 0, BUFFER_SIZE);
        // printf("reads2\n");
        strncpy(message.mesg_text, buffer, BUFFER_SIZE);
        // printf("reads3\n");
        msgsnd(msgid2, &message, sizeof(message), 0);
        // printf("reads4\n");

    }
    msgctl(msgid, IPC_RMID, NULL);
    msgctl(msgid2, IPC_RMID, NULL);
    return 0;
}