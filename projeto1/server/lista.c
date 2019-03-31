#include <stdio.h> 
#include <stdlib.h>
#include <string.h> 
#include "lista.h"
#define MAX 8000
  
void push(Perfil** head_ref, char *email, char *nome, char *sobrenome, char *foto, 
        char *residencia, char *formacaoAcademica, char *habilidades, char *experiencia) { 
    /* Aloca o no */
    Perfil* new_node = (Perfil*) malloc(sizeof(Perfil)); 
  
    /* coloca as informacoes de perfil  */
    strcpy(new_node->email, email); 
    strcpy(new_node->nome, nome); 
    strcpy(new_node->sobrenome, sobrenome); 
    strcpy(new_node->foto, foto); 
    strcpy(new_node->residencia, residencia); 
    strcpy(new_node->formacaoAcademica, formacaoAcademica); 
    strcpy(new_node->habilidades, habilidades); 
    strcpy(new_node->experiencia, experiencia); 
  
    /* coloca o novo no da lista */
    new_node->next = (*head_ref); 
  
    /* Move o no cabeca para o comeco da lista */
    (*head_ref) = new_node; 
} 

Perfil* search(Perfil* head, char *email) { 
    Perfil* current = head;
    while (current != NULL) { 
        if (strcmp(current->email,  email) == 0) 
            return current; 
        current = current->next; 
    } 
    return NULL; 
}  


void printList(Perfil *node) { 
    while (node != NULL) { 
        printPerfil(node);
        node = node->next; 
    }
    printf("\n");
}

void printPerfil(Perfil *node){
    printf("Email: %s\n", node->email);
    printf("Nome: %s\n", node->nome);
    printf("Sobrenome: %s\n", node->sobrenome);
    printf("Foto: %s\n", node->foto);
    printf("Residencia: %s\n", node->residencia);
    printf("Formacao Academica: %s\n", node->formacaoAcademica);
    printf("Habilidades: %s\n", node->habilidades);
    printf("Experiencia: %s\n", node->experiencia);
}

char *concatenaPerfil(Perfil *node){
    char *t = malloc(sizeof(char)*MAX);
    strcat(t, "Email: ");
    strcat(t, node->email);
    strcat(t, "\n");
    strcat(t, "Nome: ");
    strcat(t, node->nome);
    strcat(t, " ");
    strcat(t, "Sobrenome: ");
    strcat(t, node->sobrenome);
    strcat(t, "\n");
    strcat(t, "Foto: ");
    strcat(t, node->foto);
    strcat(t, "\n");
    strcat(t, "Residencia: ");
    strcat(t, node->residencia);
    strcat(t, "\n");
    strcat(t, "Formacao Academica: ");
    strcat(t, node->formacaoAcademica);
    strcat(t, "\n");
    strcat(t, "Hebilidades: ");
    strcat(t, node->habilidades);
    strcat(t, "\n");
    strcat(t, "Experiencia: ");
    strcat(t, node->experiencia);
    strcat(t, "\n");

    return t;
}

/* 1 - retorna todas as pessoas de um determinado curso */
Perfil* getPeopleByCourse(Perfil * head, char *formacaoAcademica){
    Perfil* new_head = NULL;
    Perfil* cur = head;
    while (cur != NULL) { 
        if (strcmp(cur->formacaoAcademica,  formacaoAcademica) == 0) 
            push(&new_head, cur->email, cur->nome, cur->sobrenome, cur->foto, cur->residencia, cur->formacaoAcademica, cur->habilidades, cur->experiencia); 
        cur = cur->next; 
    } 
    return new_head; 
}

/* 2 - retorna todas as pessoas de uma determinada Cidade*/
Perfil* getPeopleByCity(Perfil * head, char *residencia){
    Perfil* new_head = NULL;
    Perfil* cur = head;
    while (cur != NULL) { 
        if (strcmp(cur->residencia,  residencia) == 0) 
            push(&new_head, cur->email, cur->nome, cur->sobrenome, cur->foto, cur->residencia, cur->formacaoAcademica, cur->habilidades, cur->experiencia); 
        cur = cur->next; 
    } 
    return new_head; 
}

/* 3 - Adicina experiencia a um determinado perfil*/
void addPersonExp(Perfil *person, char *experiencia){
    strcat(person->experiencia, ", ");
    strcat(person->experiencia, experiencia);
}

/* 4 - Retorna as informacoes de experiencia do usuario */
char *getPersonExp(Perfil *head, char *email){
    Perfil *t;
    char *r = malloc(sizeof(char)*MAX);
    t = search(head, email);
    if (t == NULL)
        return NULL;
    strcpy(r, "Experiencia: ");
    strcat(r, t->experiencia);
    strcat(r, "\n");
    return r;
}   

/* 5 - listar todas as informações de todos os perfis*/
char *listPeople(Perfil *head){
    char *t = malloc(sizeof(char)*MAX);
    Perfil * node = head;
    while(node){
        strcat(t, concatenaPerfil(node));
        strcat(t, "---------\n");
        node = node->next;
    }
    return t;
}
/* 6 -  Retorna as informacoes completa do perfil do usuario*/
char *getPerson(Perfil *head, char *email){
    Perfil *t;
    char *r = malloc(sizeof(char)*MAX);
    t = search(head, email);
    if (t == NULL)
        return NULL;
    r = concatenaPerfil(t);
    return r;
}