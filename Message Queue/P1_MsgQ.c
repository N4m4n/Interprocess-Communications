#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <sys/un.h>
#include <unistd.h>
#include <string.h>

#define BUFFER_SIZE 128
void getString(char arr[50][5]){
    char toRet[5];
    for(int i = 0;i<50;i++){
        for(int j =0 ;j<5;j++){
            arr[i][j] = (rand() % (122 - 97 + 1)) + 97;
        }
    }

}

struct mesg_buffer {
    long mesg_type;
    char mesg_text[100];
};
  
int main()
{
    struct mesg_buffer message;
    struct mesg_buffer message2;
    char arr[50][5];
    getString(arr);
    key_t key;
    key_t key2;
    int msgid;
    int msgid2;

    key = 1010;
    key2 = 1010101010;

    msgid = msgget(key, 0666 | IPC_CREAT);
    msgid2 = msgget(key2, 0666 | IPC_CREAT);
    message.mesg_type = 1;
  

    int flag = 0;  
    int k = 0;
    char buffer[BUFFER_SIZE];
    while(k<50){
        if(flag){ 
           
            memset(buffer, 0, BUFFER_SIZE);
     
            int ret = msgrcv(msgid2, &message, sizeof(message), 1, 0);
            printf("here\n");
            strncpy(buffer, message.mesg_text,sizeof(buffer));
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
        memset(message.mesg_text, 0, BUFFER_SIZE);
        strncpy(message.mesg_text, temp, BUFFER_SIZE);
        
        msgsnd(msgid, &message, sizeof(message), 0);
        
        // sleep(1);
        

    }
  
    return 0;
}