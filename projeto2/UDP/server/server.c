
#include <stdio.h> 
#include <string.h> 
#include <sys/types.h> 
#include <arpa/inet.h> 
#include <sys/socket.h> 
#include <netinet/in.h>
#include <stdlib.h>
#include <netdb.h>
#include <sys/time.h> 
#include "lista.h"

#define PORT 5000 
#define MAXLINE 1000 

struct timeval start, end;
Perfil *listaPerfil;
FILE *image;


void createList(char *source) {
    char buff[500];
    int i=0;
    char s[2] = ";";
    char *token;
    token = strtok(source, s);
    listaPerfil = NULL;
    do {
        char email[80];
        char nome[80];
        char sobrenome[80];
        char foto[80];
        char residencia[80];
        char formacaoAcademica[80];
        char habilidades[800];
        char experiencia[800];
        strcpy(email, token);
        token = strtok(NULL, s);
        strcpy(nome, token);
        token = strtok(NULL, s);
        strcpy(sobrenome, token);
        token = strtok(NULL, s);
        strcpy(foto, token);
        token = strtok(NULL, s);
        strcpy(residencia, token);
        token = strtok(NULL, s);
        strcpy(formacaoAcademica, token);
        token = strtok(NULL, s);
        strcpy(habilidades, token);
        token = strtok(NULL, s);
        strcpy(experiencia, token);
        token = strtok(NULL, s);
        push(&listaPerfil, (char *)email, (char *)nome, (char *)sobrenome, (char *)foto, (char *)residencia, 
                (char *)formacaoAcademica, (char *)habilidades, (char *)experiencia);
    } while(token != NULL);
}

void loadDBInCache() {
    char *source = NULL;
    FILE *fp = fopen("../cadastros/banco.txt", "r+");
    if (fp != NULL) {
        /* vai para o final do arquivo */
        if (fseek(fp, 0L, SEEK_END) == 0) {
            /* calcula tamanho do arquivo */
            long bufsize = ftell(fp);
            if (bufsize == -1) { printf("-----------------");}

            /* aloca o buffer com o tamanho */
            source = malloc(sizeof(char) * (bufsize + 1));

            /* reseta para o comeco do arquivo */
            if (fseek(fp, 0L, SEEK_SET) != 0) {  printf("-----------------"); }

            /* le o arquivo no buffer */
            size_t newLen = fread(source, sizeof(char), bufsize, fp);
            if ( ferror( fp ) != 0 ) {
                fputs("Error reading file", stderr);
            } else {
                source[newLen++] = '\0'; /* Just to be safe. */
            }
        }
        fclose(fp);
    }
    createList(source);
    free(source);
}

int main(){    
    char buffer[5000]; 
    int listenfd, len; 
    struct sockaddr_in servaddr, cliaddr; 
    bzero(&servaddr, sizeof(servaddr)); 

    // coloca o banco de dados em cache
    loadDBInCache();

    // Cria UDP Socket 
    listenfd = socket(AF_INET, SOCK_DGRAM, 0);         
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY); 
    servaddr.sin_port = htons(PORT); 
    servaddr.sin_family = AF_INET;  
   
    // faz o bind 
    bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr)); 

    len = sizeof(cliaddr); 
    
    //recebe datagram 
    bzero(&buffer, sizeof(buffer));
    int n = recvfrom(listenfd, buffer, sizeof(buffer), 
            0, (struct sockaddr*)&cliaddr,&len); //receive message from server 
       
    // envia mensagem 
    char *message1 = "Por favor insira email"; 
    sendto(listenfd, message1, MAXLINE, 0, 
          (struct sockaddr*)&cliaddr, sizeof(cliaddr)); 

    //recebe datagram
    char email[80];
    n = recvfrom(listenfd, email, sizeof(email), 
            0, (struct sockaddr*)&cliaddr,&len); //receive message from server 
    email[n] = '\0'; 
    puts(email);

    char *resposta;
    Perfil *node;
    resposta = getFullName(listaPerfil, email);
    node = search(listaPerfil, email);
    if (node){
        printf("vou abrir a foto em %s\n", node->foto);
        image = fopen(node->foto, "r");
    }

    // caso email nao tenha sido encontrado
    if(!resposta) {
        strcpy(resposta, "Email nao encontrado\n\n");
    }

    // envia mensagem 
    sendto(listenfd, resposta, MAXLINE, 0, 
          (struct sockaddr*)&cliaddr, sizeof(cliaddr));
    
    //envia imagem
    if(image) {
        bzero(&buffer, sizeof(buffer));
        int nb = fread(buffer, 1, sizeof(buffer), image);
        
        puts(nb);
        while(!feof(image)){
            sendto(listenfd, buffer, MAXLINE, 0, 
                (struct sockaddr*)&cliaddr, sizeof(cliaddr));
            nb = fread(buffer, 1, sizeof(buffer), image);
        }
        bzero(buffer, 5000);
        sendto(listenfd, buffer, MAXLINE, 0, 
            (struct sockaddr*)&cliaddr, sizeof(cliaddr));

    } else {
        puts("imagem nao encontrada");
    }
    fclose(image);
    
    
} 
