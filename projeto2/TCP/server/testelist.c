#include<stdio.h> 
#include<stdlib.h>
#include<string.h>
#include"lista.h"

#define MAX 800000

int main(){
    /* Start with the empty list */
    Perfil* head = NULL;
    FILE * fp;
    FILE * saida;
    char image[MAX];
    char buff;
     
    //char *r;

    //push(&head, "a", "aa", "aaa", "aaaa", "aaaaa", "aaaaaa", "aaaaaaa", "aaaaaaaa"); 
    //push(&head, "b", "bb", "bbb", "bbbb", "bbbbb", "bbbbbb", "bbbbbbb", "bbbbbbbb"); 
    //push(&head, "c", "cc", "ccc", "cccc", "ccccc", "cccccc", "ccccccc", "cccccccc"); 
    //push(&head, "d", "dd", "ddd", "dddd", "ddddd", "dddddd", "ddddddd", "dddddddd"); 
    push(&head, "e", "ee", "eee", "../cadastros/imagem3.ppm", "eeeee", "eeeeee", "eeeeeee", "eeeeeeee"); 
    fp = fopen (head->foto, "r");
    if (fp)
        printf("abriu\n");
    //printList(head);
    //addPersonExp(head, "c", "asd");
    //r = getPersonExp(head, "c");
    //r = listPeople(head);
    //if (r){
    //    printf("%s", r);
    //}
    int i = 0;
    fscanf(fp, "%c", &buff);
    while(buff != EOF){
        image[i] = buff;
        i++;
        fscanf(fp, "%c", &buff);
    }
    printf("leu\n");

    saida = fopen("saida.ppm", "w");
    printf("abriu2\n");
    
    fprintf(saida, "%s", image);   
    printf("escreveu\n"); 
    fclose(fp);
    fclose(saida);
    return 0;
}