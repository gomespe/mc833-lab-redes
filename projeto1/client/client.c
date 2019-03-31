
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <stdio.h>

#define MAX 8000
#define PORT 8001
#define SA struct sockaddr

void func(int sockfd)
{
    char buff[MAX];
    while(1){
        bzero(buff, sizeof(buff));
        read(sockfd, buff, sizeof(buff));
        printf("\n------------------\nFrom Server : \n%s\n", buff);
        
        fgets(buff, MAX , stdin);
        buff[strlen(buff)-1]= '\0';
        
        // verifica se o cliente quer sair
        if ((strcmp(buff, "0")) == 0){
            printf("Client Exit...\n");
            break;
        }
        write(sockfd, buff, strlen(buff));
        bzero(buff, sizeof(buff));
    }
}

int main()
{
    int sockfd, connfd;
    struct sockaddr_in servaddr, cli;

    // Criacao do socket e verificacao 
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1)
    {
        printf("socket creation failed...\n");
        exit(0);
    }
    else
        printf("Socket successfully created..\n");
    bzero(&servaddr, sizeof(servaddr));

    // atribuicao de IP e Porta 
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    servaddr.sin_port = htons(PORT);

    // connect the client socket to server socket
    if (connect(sockfd, (SA *)&servaddr, sizeof(servaddr)) != 0){
        printf("connection with the server failed...\n");
        exit(0);
    }
    else
        printf("connected to the server..\n");

    // funcao de conversa
    func(sockfd);

    // fecha socket
    close(sockfd);
}
