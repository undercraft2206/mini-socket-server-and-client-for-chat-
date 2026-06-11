#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define IPV4 AF_INET
#define TCP SOCK_STREAM
#define ANY_INTERFACE INADDR_ANY

#define PORT 53

void chat(char msg[1023]){
   
}

int main(void){
    system("clear");

    char msg[1023];
    char ip[20];

    int client_fd, status, valread;
    struct sockaddr_in serv_addr;
    char buffer[1024] = { 0 }; 

    if((client_fd = socket(IPV4, TCP, 0)) < 0){
        perror("ERRORE: Failed to init socket");
        exit(EXIT_FAILURE);
    }

    serv_addr.sin_family = IPV4;
    serv_addr.sin_port = htons(PORT);

    if(inet_pton(IPV4, ip, &serv_addr.sin_addr) <= 0){
        perror("ERROR: Failed to init intet_pton");
        exit(EXIT_FAILURE);
    }

    if((status = connect(client_fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr))) < 0){
        perror("ERRORE: Failed to init connect");
        exit(EXIT_FAILURE);
    }

    printf("server connected !\nYou start to talk !\n\n");

    while(strcmp(msg, "exit") != 0){

        printf("\n> ");
        scanf("%s", msg);
        
        send(client_fd, msg, strlen(msg), 0);

        valread = read(client_fd, buffer, 1024 - 1);
        printf("server: %s", buffer);

        memset(buffer, 0, 1024);
    }

//    send(client_fd, msg, strlen(msg), 0);
//    printf("\nMSG send !\n");
//    valread = read(client_fd, buffer, 1024 - 1);
//    printf("%s", buffer);

    close(client_fd);    
    return 0;
}