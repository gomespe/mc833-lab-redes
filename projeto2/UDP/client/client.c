
#include <stdio.h> 
#include <string.h> 
#include <sys/types.h> 
#include <arpa/inet.h> 
#include <sys/socket.h> 
#include<netinet/in.h> 
#include<unistd.h> 
#include<stdlib.h> 
  
#define PORT 5000 
#define MAXLINE 1000
#define MAX 8000

int main() {    
    char buffer[MAX]; 
    int sockfd, n; 
    struct sockaddr_in servaddr; 
      
    bzero(&servaddr, sizeof(servaddr)); 
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1"); 
    servaddr.sin_port = htons(PORT); 
    servaddr.sin_family = AF_INET; 
      
    // cria datagram socket 
    sockfd = socket(AF_INET, SOCK_DGRAM, 0); 
      
    // conecta ao server 
    if(connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0){ 
        printf("\n Error : Connect Failed \n"); 
        exit(0); 
    } 
    // envia datagram 
    sendto(sockfd, "", MAXLINE, 0, (struct sockaddr*)NULL, sizeof(servaddr)); 

    // espera resposta 
    bzero(&buffer, sizeof(buffer));
    recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr*)NULL, NULL); 
    puts(buffer); 
  
    // envia datagram 
    char *email = "pedro_gomes@gmail.com";
    sendto(sockfd, email, MAXLINE, 0, (struct sockaddr*)NULL, sizeof(servaddr)); 
      
    // espera resposta 
    bzero(&buffer, sizeof(buffer));
    recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr*)NULL, NULL); 
    puts(buffer);

    // char *nome = "imagemRecebida";
    // strcat(nome, ".png");
    // printf("imagem salva como %s\n", nome);
    // FILE *image = fopen(nome, "w");
    // int nb = recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr*)NULL, NULL);
    // while(strlen(buffer) > 0){
    //     fwrite(buffer, 1, nb, image);
    //     nb = recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr*)NULL, NULL);
    // }
    // fclose(image);
    // fecha descriptor 
    close(sockfd); 
}