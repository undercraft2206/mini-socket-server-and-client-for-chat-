#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define IPV4 AF_INET
#define TCP SOCK_STREAM
#define ANY_INTERFACE INADDR_ANY

#define PORT 53

int main(void){
    system("clear");

    char msg[1023];

    int server_fd, new_socket;
    ssize_t valread;
    struct sockaddr_in address;
    socklen_t addrlen = sizeof(address);
    int opt = 1;
    char buffer[1024] = { 0 };

    if((server_fd = socket(IPV4, TCP, 0)) < 0){
        perror("ERRORE: socket not initie");
        exit(EXIT_FAILURE);
    }

    if(setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))){
        perror("ERRORE: Failed to initie setsockopt");
        exit(EXIT_FAILURE);
    }

    address.sin_family = IPV4;
    address.sin_addr.s_addr = ANY_INTERFACE;
    address.sin_port = htons(PORT);

    if(bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0){
        perror("ERRORE: Failed to init bind");
        exit(EXIT_FAILURE);
    }

    if(listen(server_fd, 3) < 0){
        perror("ERRORE: Failed to init listen");
        exit(EXIT_FAILURE);
    }

    if((new_socket = accept(server_fd, (struct sockaddr*)&address, &addrlen)) < 0){
        perror("ERROR: Failed to accept new socket");
        exit(EXIT_FAILURE);
    }

    printf("client connected, starting chating ! client starting talking\n\n");

    while(strcmp(msg, "exit") != 0){
        valread = read(new_socket, buffer, 1024 - 1);
        printf("client: %s", buffer);
        memset(buffer, 0, 1024);

        printf("\n> ");
        scanf("%s", msg);

        send(new_socket, msg, strlen(msg), 0);
    }

    close(new_socket);
    close(server_fd);
}
