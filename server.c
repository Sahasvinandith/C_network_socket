#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

typedef struct sockaddr_in Socket_add;

int main(){
    //create the server socket
    char server_message[256]="Hello this is the server!!";

    int server_socket=socket(AF_INET,SOCK_STREAM,0);

    Socket_add server_address;

    server_address.sin_family=AF_INET;
    server_address.sin_addr.s_addr=INADDR_ANY;
    server_address.sin_port=htons(9002);

    bind(server_socket,(struct sockaddr*)&server_address,sizeof(server_address));

    printf("Server listening\n");

    listen(server_socket,5);

    int client_socket=accept(server_socket,NULL,NULL);

    send(client_socket,(void*)server_message,sizeof(server_message),0);
    close(server_socket);
    return 0;

}