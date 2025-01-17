
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
    int client_socket=socket(AF_INET,SOCK_STREAM,0);

    Socket_add server_address;//giving information abouit server
    server_address.sin_family=AF_INET;
    server_address.sin_port=htons(9002);
    server_address.sin_addr.s_addr=INADDR_ANY;

    int stat=connect(client_socket,(struct sockaddr*)&server_address,sizeof(server_address));

    char server_response[256];
    char client_message[256];

    recv(client_socket,(void*)server_response,sizeof(server_response),0);
    printf("Server: %s\n",server_response);
    
    while (server_response!="Q")

    {
        printf("client: ");
        fgets(client_message,sizeof(client_message),stdin);
        string_format(client_message);
        send(client_socket,(void*)client_message,sizeof(client_message),0);
        recv(client_socket,(void*)server_response,sizeof(server_response),0);
        string_format(server_response);
        printf("Server: %s\n",server_response);
        
    }
    

    
    close(client_socket);
    return 0;
}