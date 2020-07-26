// gcc server.c -lws2_32

#include <unistd.h>
#include <stdio.h>
#ifdef __WIN32__
# include <winsock2.h>
#else
# include <sys/socket.h>
#endif
#include <ws2tcpip.h>
#include <stdlib.h>
#include <string.h>

#define PORT 8080
//typedef int* socklen_t;

int main(int argc, char const *argv[])
{
    /* code */
    int server_fd, new_socket, valread;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};
    char *hello = "Hello from server";

    //creating socket fd
    if((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0){
        perror("Socket creation failed.\n");
        exit(EXIT_FAILURE);
    }

    //forcefully attaching socket to the port 8080
    if(setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_BROADCAST, (char*)&opt, sizeof(opt))){
        perror("setsocketopt failure.\n;");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.S_un.S_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if(bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0){
        perror("bind failed.\n");
        exit(EXIT_FAILURE);
    }

    if(listen(server_fd, 3) < 0){
        perror("listen failure.\n");
        exit(EXIT_FAILURE);
    }

    if((new_socket = accept(server_fd, (struct sockaddr*)&address, &addrlen))){
        perror("accept failure.\n");
        exit(EXIT_FAILURE);
    }

    valread = read(new_socket, buffer, 1024);
    fprintf(stdout, "%s\n", buffer);
    send(new_socket, hello, strlen(hello), 0);
    fprintf(stdout, "Hello message sent.\n");

    return 0;
}
