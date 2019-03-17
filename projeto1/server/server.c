
#include <netdb.h> 
#include <netinet/in.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 
#include <sys/types.h> 
#include <stdio.h>

#define MAX 8000 
#define PORT 8080 
#define SA struct sockaddr 

char comandoInvalido[] = "Comando invalido. Por favor tente novamente\n\n";
listaDosPerfils -> array de struct tipo perfil 

char *listarPerfil() {
    char *resposta;
    char msg2[] = "Voce gostaria de:\n [1] - Perfil completo\n[2] - Somente experiencia\n"
    write(sockfd, msg2, sizeof(msg2));
    
    char buff[MAX];
    read(sockfd, buff, sizeof(buff));

    while(1) {
        char msg1[] = "Por favor digite email\n";
        write(sockfd, msg1, sizeof(msg1));

        bzero(buff, MAX);
        read(sockfd, buff, sizeof(buff));

        if(strncmp("1", buff, 2) == 0) {
            resposta = getPerson(listaDosPerfils, buff);
        } else if(strncmp("2", buff, 2) == 0) {
            resposta = getPersonExp(listDosPerfils, buff);
        } else {
            bzero(buff, MAX);
            strcat(buff, comandoInvalido);
            continue;
        }

        // caso email nao tenha sido encontrado
        if(!resposta) {
            strcat(resposta, "Email nao encontrado, digite novamente:\n");
        } else {
            return resposta;
        }
    }

    return NULL;
}


// Funcao de conversa entra Cliente e Servidor 
void conversaComCliente(int sockfd) { 
    char buff[MAX]; 
    int n; 
    char mensagemComandos[] = "O que gostaria de fazer?\n[1] - Listar todos os perfis\n[2] - Listar perfil especifico\n[3] - Acrescentar nova experiencia\n[4] - Listar perfils pelo curso\n[5] - Listar perfils por cidade\n";
    write(sockfd, mensagemComandos, sizeof(mensagemComandos)); 
    
    // loop infinito de conversa 
    while(1) { 
        bzero(buff, MAX);

        // recebe mensagem do cliente e coloca no buff 
        read(sockfd, buff, sizeof(buff)); 

        // realiza funcao desejada pelo cliente
        if (strncmp("1", buff, 2) == 0) {
            listarTodos(&buff);
        } else if (strncmp("2", buff, 2) == 0) {
            listarPerfil(&buff);
        } else if (strncmp("3", buff, 2) == 0) {
            
        } else if (strncmp("4", buff, 2) == 0) {
            
        } else if (strncmp("5", buff, 2) == 0) {
        
        } else {
            bzero(buff, MAX);
            strcat(buff, comandoInvalido);
        }

        // envia mensagem para o cliente
        strcat(buff, mensagemComandos);
        write(sockfd, mensagemComandos, sizeof(mensagemComandos));
    } 
} 
  
int main() { 
    int sockfd, connfd, len; 
    struct sockaddr_in servaddr, cli; 
  
    // Criacao do socket e verificacao 
    sockfd = socket(AF_INET, SOCK_STREAM, 0); 
    if (sockfd == -1) { 
        printf("socket creation failed...\n"); 
        exit(0); 
    } 
    else
        printf("Socket successfully created..\n"); 
    bzero(&servaddr, sizeof(servaddr)); 
  
    // atribuicao de IP e Porta 
    servaddr.sin_family = AF_INET; 
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY); 
    servaddr.sin_port = htons(PORT); 
  
    // Faz o bind do socket com o IP e verificacao 
    if ((bind(sockfd, (SA*)&servaddr, sizeof(servaddr))) != 0) { 
        printf("socket bind failed...\n"); 
        exit(0); 
    } 
    else
        printf("Socket successfully binded..\n"); 
  
    // Servidor pronto para ouvir e verificacao 
    if ((listen(sockfd, 5)) != 0) { 
        printf("Listen failed...\n"); 
        exit(0); 
    } 
    else
        printf("Server listening..\n"); 
    len = sizeof(cli); 
  
    // Aceita o pacote de dados do cliente e verificacao 
    connfd = accept(sockfd, (SA*)&cli, &len); 
    if (connfd < 0) { 
        printf("server acccept failed...\n"); 
        exit(0); 
    } 
    else
        printf("server acccept the client...\n"); 
  
    // funcao de conversa entre cliente e servidor 
    conversaComCliente(connfd); 
  
    // apos a conversa, fechar o socket 
    close(sockfd); 
}