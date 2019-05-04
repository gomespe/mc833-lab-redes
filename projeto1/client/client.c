#include <sys/time.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <stdio.h>

#define MAX 8000
#define PORT 8080
#define SA struct sockaddr

int contador = 0;
struct timeval start, end;

void startClock () {
    gettimeofday(&start, NULL);
}

void stopClock () {
    gettimeofday(&end, NULL);
    printf("[%d] Tempo de total: %ld\n", contador, ((end.tv_sec * 1000000 + end.tv_usec) - (start.tv_sec * 1000000 + start.tv_usec)));
    contador++;
}
char *extraiNome(char *buff){
    char *token;
    char s[2] = " ";
    token = strtok(buff, s);
    token = strtok(NULL, s);
    token = strtok(NULL, s);

    return token;
}
void func(int sockfd){
    int flag = 0;
    int tempo=0;
    char buff[MAX];
    char *nome;
    while(1){

        bzero(buff, sizeof(buff));
        read(sockfd, buff, sizeof(buff));
        if(tempo) {
            stopClock();
            tempo--;
        }
        printf("\n------------------\nFrom Server : \n%s\n", buff);
        if (flag == 3){
            nome = extraiNome(buff);
            strcat(nome, ".png");
            printf("imagem salva como %s\n", nome);
            FILE *image = fopen(nome, "w");
            int nb = read(sockfd, buff, MAX);
            while(strlen(buff) > 0){
                fwrite(buff, 1, nb, image);
                nb = read(sockfd, buff, MAX);
            }
            fclose(image);
            flag = 0;
        }
        if (flag)
            flag++;
        fgets(buff, MAX , stdin);
        buff[strlen(buff)-1]= '\0';
        
        // verifica se o cliente quer sair
        if ((strcmp(buff, "0")) == 0){
            printf("Client Exit...\n");
            break;
        }
        else if ((strcmp(buff, "2")) == 0){
            flag = 1;
        }

        startClock();
        tempo++;
        
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
    if (sockfd == -1){
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
