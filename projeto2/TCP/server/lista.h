/* Estrutura de dados*/
struct Node { 
    char email[80], nome[80], sobrenome[80], foto[80], residencia[80], formacaoAcademica[80],
        habilidades[800], experiencia[800];   
  
    struct Node *next; 
}; 
typedef struct Node Perfil;

/* Adiciona um no ao inicio da lista*/
void push(Perfil** head_ref, char *email, char *nome, char *sobrenome, char *foto, 
        char *residencia, char *formacaoAcademica, char *habilidades, char *experiencia);

/* Retorna o perfil se achado, NULL caso nao*/
Perfil* search(Perfil* head, char key[80]);

/* Imprime todos os perfils da lista*/
void printList(Perfil *node);

/* Imprime um unico perfil*/
void printPerfil(Perfil *node);

/* Rettorna uma unica string com todos os dados concatenados*/
char* concatenaPerfil(Perfil *node);

/* 1 - retorna todas as pessoas de um determinado curso */
Perfil* getPeopleByCourse(Perfil * head, char *formacaoAcademica);

/* 2 - retorna todas as pessoas de uma determinada Cidade*/
Perfil* getPeopleByCity(Perfil * head, char *residencia);

/* 3 - Adicina experiencia a um determinado perfil*/
void addPersonExp(Perfil *person, char *experiencia);

/* 4 - Retorna as informacoes de experiencia do usuario */
char* getPersonExp(Perfil *head, char *email);

/* 5 - listar todas as informações de todos os perfis, retorna numa string pronta para impressao*/
char* listPeople(Perfil *head);

/* 6 -  Retorna as informacoes completa do perfil do usuario*/
char* getPerson(Perfil *head, char *email);