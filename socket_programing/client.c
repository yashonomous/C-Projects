#include <unistd.h>
#include <stdio.h>
#ifdef __WIN32__
#include <winsock2.h>
#else
#include <sys/socket.h>
#endif
#include <ws2tcpip.h>
#include <stdlib.h>
#include <string.h>

#define PORT 8080

int inet_pton(int af, const char *src, void *dst)
{
  struct sockaddr_storage ss;
  int size = sizeof(ss);
  char src_copy[INET6_ADDRSTRLEN+1];

  ZeroMemory(&ss, sizeof(ss));
  /* stupid non-const API */
  strncpy (src_copy, src, INET6_ADDRSTRLEN+1);
  src_copy[INET6_ADDRSTRLEN] = 0;

  if (WSAStringToAddress(src_copy, af, NULL, (struct sockaddr *)&ss, &size) == 0) {
    switch(af) {
      case AF_INET:
    *(struct in_addr *)dst = ((struct sockaddr_in *)&ss)->sin_addr;
    return 1;
      case AF_INET6:
    *(struct in6_addr *)dst = ((struct sockaddr_in6 *)&ss)->sin6_addr;
    return 1;
    }
  }
  return 0;
} 

int main(int argc, char const *argv[])
{
    /* code */
    int socket_fd, valread;
    struct sockaddr_in address;
    char *hello = "Hello from client.\n";
    char buffer[1024] = {0};

    if((socket_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        perror("Socket creation failed.\n");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_port = htons(PORT);

    if(inet_pton(AF_INET, "127.0.0.1", &address.sin_addr) <= 0){
        perror("Invalid address / Address not supported.");
        exit(EXIT_FAILURE);
    }

    if(connect(socket_fd, (struct sockaddr*)&address, sizeof(address))){
        perror("Connection failed.\n");
        exit(EXIT_FAILURE);
    }

    send(socket_fd, hello, strlen(hello), 0);
    fprintf(stdout, "%s\n", "Hello message sent.");
    valread = read(socket_fd, buffer, 1024);
    fprintf(stdout, "%s\n", buffer);

    return 0;
}
