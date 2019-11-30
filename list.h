#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include <time.h> 
typedef struct tDado
{
    char word;
    char qtd;
}Dado;

typedef struct tList
{
    int id;
    Dado dado;
    struct tList * listProx;
    struct tList * listAnte;
}List;

List * startList();
void adicionarInicio(List * list, Dado dado);
void adicionarFim(List * list, Dado dado);
void addEndChar(List * list, char word);
void removerFim(List * list);
void remover(List * list, int id);
void quickSort(List * list, int began, int end);
void delay(int number_of_seconds) ;
void exibir(List list);
List * searchByID(List * list, int id);
List * searchByWord(List * list, char word);


