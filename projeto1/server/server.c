
#include <netdb.h> 
#include <netinet/in.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 
#include <sys/types.h> 
#include <stdio.h>
#include "lista.h"

#define MAX 8000 
#define PORT 8080
#define SA struct sockaddr 

char comandoInvalido[] = "Comando invalido. Por favor tente novamente\n\n";
Perfil *listaPerfil;
char buff[MAX];
FILE *image;

void listarTodos() {
    char *resposta;
    bzero(buff, MAX);
    resposta = listPeople(listaPerfil);
    strcpy(buff, resposta);
}

// Funcao lista perfil especifico dado um email
void listarPerfil(int sockfd) {
    char *resposta;
    
    
    char msg2[] = "Voce gostaria de:\n[1] - Perfil completo\n[2] - Somente experiencia\n";
    write(sockfd, msg2, sizeof(msg2));
    
    char comando[2] = "\0\0";
    read(sockfd, comando, sizeof(comando));
    
    char msg1[] = "Por favor digite email\n";
    write(sockfd, msg1, sizeof(msg1));

    
    bzero(buff, MAX);
    read(sockfd, buff, sizeof(buff));

    if(strncmp("1", comando, 2) == 0) {
        Perfil *node;
        resposta = getPerson(listaPerfil, buff);
        node = search(listaPerfil, buff);
        printf("vou abrir em %s\n", node->foto);
        image = fopen(node->foto, "r");
    } else if(strncmp("2", comando, 2) == 0) {
        resposta = getPersonExp(listaPerfil, buff);
    } else {
        bzero(buff, MAX);
        strcat(buff, comandoInvalido);
        return;
    }

    // caso email nao tenha sido encontrado
    if(!resposta) {
        strcpy(buff, "Email nao encontrado\n\n");
    } else {
        strcpy(buff, resposta);
    }
}

void addExperiencia(int sockfd) {
    Perfil *pessoa;
    
    char msg1[] = "Por favor digite email\n";
    write(sockfd, msg1, sizeof(msg1));

    bzero(buff, MAX);
    read(sockfd, buff, sizeof(buff));

    pessoa = search(listaPerfil, buff);

    if(!pessoa) {
        strcpy(buff, "Email nao encontrado\n\n");
        return;
    }

    char msg2[] = "Por favor digite experiencia a ser adicionada\n";
    write(sockfd, msg2, sizeof(msg2));

    bzero(buff, MAX);
    read(sockfd, buff, sizeof(buff));

    addPersonExp(pessoa, buff);

    bzero(buff, MAX);
    strcat(buff, "Atualizacao efetuado com sucesso\n");
}

void listarPeloCurso(int sockfd) {
    Perfil *resposta;
    
    char msg1[] = "Por favor digite curso\n";
    write(sockfd, msg1, sizeof(msg1));

    bzero(buff, MAX);
    read(sockfd, buff, sizeof(buff));

    resposta = getPeopleByCourse(listaPerfil, buff);

    if(!resposta) {
        bzero(buff, MAX);
        strcat(buff, "Nenhum perfil com este curso foi encontrado\n");
    } else {
        bzero(buff, MAX);
        strcat(buff, "Perfis encontrados:\n");
        while(resposta){
            strcat(buff, concatenaPerfil(resposta));
            strcat(buff, "---------\n");
            resposta = resposta->next;
        }
    }
}

void listarPelaCidade(int sockfd) {
    Perfil *resposta;
    
    char msg1[] = "Por favor digite cidade\n";
    write(sockfd, msg1, sizeof(msg1));

    bzero(buff, MAX);
    read(sockfd, buff, sizeof(buff));

    resposta = getPeopleByCity(listaPerfil, buff);

    if(!resposta) {
        bzero(buff, MAX);
        strcat(buff, "Nenhum perfil com esta cidade foi encontrado\n");
    } else {
        bzero(buff, MAX);
        strcat(buff, "Perfis encontrados:\n");
        while(resposta){
            strcat(buff, concatenaPerfil(resposta));
            strcat(buff, "---------\n");
            resposta = resposta->next;
        }
    }
}

// Funcao de conversa entra Cliente e Servidor 
void conversaComCliente(int sockfd) { 
    int n; 
    char mensagemComandos[] = "O que gostaria de fazer?\n[1] - Listar todos os perfis\n[2] - Listar perfil especifico\n[3] - Acrescentar nova experiencia\n[4] - Listar perfils pelo curso\n[5] - Listar perfils por cidade\n[0] - Sair";
    write(sockfd, mensagemComandos, sizeof(mensagemComandos)); 
    // loop infinito de conversa 
    while(1) { 
        bzero(buff, MAX);

        // recebe mensagem do cliente e coloca no buff 
        read(sockfd, buff, sizeof(buff)); 
        
        // realiza funcao desejada pelo cliente
        if (strncmp("1", buff, 2) == 0) {
            listarTodos();
        } else if (strncmp("2", buff, 2) == 0) {
            listarPerfil(sockfd);
        } else if (strncmp("3", buff, 2) == 0) {
            addExperiencia(sockfd);
        } else if (strncmp("4", buff, 2) == 0) {
            listarPeloCurso(sockfd);
        } else if (strncmp("5", buff, 2) == 0) {
            listarPelaCidade(sockfd);
        } else if (strncmp("0", buff, 2) == 0) {
            printf("Client Exited...\n");
            break;
        } else {
            bzero(buff, MAX);
            strcat(buff, comandoInvalido);
        }

        // envia mensagem para o cliente
        strcat(buff, mensagemComandos);
        write(sockfd, buff, sizeof(buff));
        if (image){
            int nb = fread(buff, 1, sizeof(buff), image);
            while(!feof(image)){
                write(sockfd, buff, nb);
                nb = fread(buff, 1, sizeof(buff), image);
            }
            bzero(buff, MAX);
            write(sockfd, buff, sizeof(buff));
            fclose(image);
            image = NULL;
        }
    } 
} 

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

// coloca o banco de dados em cache
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

int main() { 
    int sockfd, connfd, len; 
    struct sockaddr_in servaddr, cli;
  
    // coloca o banco de dados em cache
    loadDBInCache();

    // Criacao do socket e verificacao 
    bzero(&sockfd, sizeof(sockfd)); 
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
  

    while(1){
        // Aceita o pacote de dados do cliente e verificacao 
        connfd = accept(sockfd, (SA*)&cli, &len); 
        if (connfd < 0) { 
            printf("server acccept failed...\n"); 
            continue; 
        } 
        else
            printf("server acccept the client...\n"); 
        

        // funcao de conversa entre cliente e servidor 
        if(!fork()){
            close(sockfd); 
            conversaComCliente(connfd);
            close(connfd);
            exit(0); 
        }
        // apos a conversa, fechar o socket pq o pai nao precisa disso
        close(connfd); 

    }
}