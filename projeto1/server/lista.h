/* Estrutura de dados*/
struct Node { 
    char email[80], nome[80], sobrenome[80], foto[80], residencia[80], formacaoAcademica[80],
        habilidades[80], experiencia[80];   
  
    struct Node *next; 
}; 
typedef struct Node Perfil;

/* Adiciona um no ao inicio da lista*/
void push(Perfil** head_ref, char *email, char *nome, char *sobrenome, char *foto, 
        char *residencia, char *formacaoAcademica, char *habilidades, char *experiencia);

/* Retorna as informacoes completa do perfil do usuario*/
char *getPerson(Perfil *head, char *email);

/* Retorna as informacoes de experiencia do usuario*/
char *getPersonExp(Perfil *head, char *email);

/* Retorna o perfil se achado, NULL caso nao*/
Perfil* search(Perfil* head, char key[80]);

/* Imprime todos os perfils da lista*/
void printList(Perfil *node);

/* Imprime um unico perfil*/
void printPerfil(Perfil *node);

/* Rettorna uma unica string com todos os dados concatenados*/
char* concatenaPerfil(Perfil *node);