#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

typedef struct sockaddr_in Socket_add;

void string_format(char buffer[]){
    for (int i = 0; i < sizeof(buffer); i++)
    {
        if(buffer[i]=='\n'){
            return;
        }
        else{
            buffer[i]=buffer[i];
        }
    }
    
}

int main(){
    //create the server socket
    char server_message[256]="Hello this is the server!!";
    char client_message[256];

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

    while (client_message!="Q" || server_message!="Q")//develop the code to await until the client sends a reply. i guess
    {
        recv(client_socket,(void*)&client_message,sizeof(client_message),0);
        string_format(client_message);
        printf("Client: %s\n",client_message);
        printf("Server: ");
        fgets(server_message,sizeof(server_message),stdin);
        string_format(server_message);
        send(client_socket,(void*)server_message,sizeof(server_message),0);
    }
    

    
    close(server_socket);
    return 0;

}