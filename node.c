#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include"dado.h"

typedef struct tNode
{
    Dado dado;
    struct tNode * right;
    struct tNode * left;
}Node;

Node * startNode();
Node * transformNode(Node * node, Dado dado);
void addNode(Node * nodefather, Node * nodeRight, Node * nodeLeft);
// void removerFim(List * list);
// void remover(List * list, int id);
// void quickSort(List * list, int began, int end);
// void delay(int number_of_seconds) ;
// void exibir(List list);
// List * searchByID(List * list, int id);
// List * searchByWord(List * list, char word);

Node * startNode()
{
    Node * node  = (Node*)calloc(1,sizeof(Node));
    node->right = NULL;
    node->left = NULL;
    return node;
}

Node * transformNode(Dado dado)
{
    Node * node  = (Node*)calloc(1,sizeof(Node));
    node->dado.word = dado.word;
    node->dado.qtd = dado.qtd;
    node->right = NULL;
    node->left = NULL;
    return node;
}
// void addRight(Node * node, Dado dado)
// {
//     Node * newNode  = (Node*)calloc(1,sizeof(Node));
//     newNode->dado.word = dado.word;
//     newNode->dado.qtd = dado.qtd;

//     newNode->right = NULL;
//     newNode->left = NULL;
//     list->listProx = novoElemento;
    
    
//     if (list->id==1)
//     {
//         list->listAnte=novoElemento;
//     }
//     else
//     {
//         novoElemento->listProx->listAnte = list->listProx;
//     }
    
//     list->id++;

// }
// void addLeft(Node * node, Dado dado)
// {
//     List * novoElemento = (List*)calloc(1,sizeof(List));
//     novoElemento->id = list->id;
    
//     novoElemento->dado.word = dado.word;
//     novoElemento->dado.qtd = dado.qtd;
//     novoElemento->listProx = NULL;

//     List * ultimoElem = list->listAnte;
//     if (ultimoElem==NULL)
//     {
//         list->listAnte = ultimoElem;
//         list->listProx = novoElemento;
//     }
//     else
//     {
//         ultimoElem->listProx = novoElemento;
//         novoElemento->listAnte = ultimoElem;
//     }
//     list->listAnte = novoElemento;
//     list->id++;
// }

// void addEndChar(List * list, char word)
// {
//     List * novoElemento = (List*)calloc(1,sizeof(List));
//     novoElemento->id = list->id;
    
//     novoElemento->dado.word = word;
//     novoElemento->dado.qtd = 1;
//     novoElemento->listProx = NULL;

//     List * ultimoElem = list->listAnte;
//     if (ultimoElem==NULL)
//     {
//         list->listAnte = ultimoElem;
//         list->listProx = novoElemento;
//     }
//     else
//     {
//         ultimoElem->listProx = novoElemento;
//         novoElemento->listAnte = ultimoElem;
//     }
//     list->listAnte = novoElemento;
//     list->id++;
// }
// void removerFim(List * list)
// {
//     List * elemento = list->listAnte;
//     if(elemento != NULL)
//     {
//         List * elementoAnte = elemento->listAnte;
//         List * elementoProx = elemento->listProx;

//         elementoAnte->listProx = elemento->listProx;
//         if (list->listAnte == elemento)
//         {
//             list->listAnte = elementoAnte;
//         }
//         else
//         {
//             elementoProx->listAnte = elemento->listAnte;
//         }
//         elemento->listProx=NULL;
//         elemento->listAnte=NULL;
//         free(elemento);
//     }
// }
// void remover(List * list, int id)
// {
//     List * elemento = searchByID(list, id);
//     if(elemento != NULL)
//     {
//         List * elementoAnte = elemento->listAnte;
//         List * elementoProx = elemento->listProx;

//         elementoAnte->listProx = elemento->listProx;
//         if (list->listAnte == elemento)
//         {
//             list->listAnte = elementoAnte;
//         }
//         else
//         {
//             elementoProx->listAnte = elemento->listAnte;
//         }
//         elemento->listProx=NULL;
//         elemento->listAnte=NULL;
//         free(elemento);
//     }
// }

// void quicksort(List * list, int began, int end)
// {
// 	int i, j, pivo;
// 	i = began;
// 	j = end;
// 	pivo = searchByID(list,((began + end) / 2))->dado.qtd;
// 	while(i < j)
// 	{
//         List * listRef = searchByID(list,(i));
// 		while( listRef->dado.qtd < pivo && i < end)
// 		{
//             i++;
// 			listRef = listRef->listProx;
// 		}
//         listRef = searchByID(list,(j));
// 		while(listRef->dado.qtd > pivo && j > began)
// 		{
//             j--;
// 			listRef = listRef->listAnte;
// 		}
// 		if(i <= j )
// 		{
//             if (searchByID(list,(i))->dado.qtd != searchByID(list,(j))->dado.qtd)
//             {
//                 Dado aux =  searchByID(list,(i))->dado;
//                 searchByID(list,(i))->dado = searchByID(list,(j))->dado;
//                 searchByID(list,(j))->dado = aux;
//             }
// 			i++;
// 			j--;
// 		}
// 	}
// 	if(j > began)
// 	{
//         quicksort(list, began, j);
//     }	
    
// 	if(i < end)
//     {
// 		quicksort(list, i, end);
//     }
// }
// void delay(int number_of_seconds) 
// { 
//     // Converting time into milli_seconds 
//     int milli_seconds = 1000 * number_of_seconds; 
  
//     // Stroing start time 
//     clock_t start_time = clock(); 
  
//     // looping till required time is not acheived 
//     while (clock() < start_time + milli_seconds); 
// }
// List * searchByID(List * list, int id)
// {
//     if(list->listProx != NULL)
//     {
//         List * listRef = list->listProx;
//         while (listRef != NULL && listRef->id != id)
//         {
//             listRef = listRef->listProx;
//         }
//         if (listRef == NULL)
//         {
//             return NULL;
//         }
//         else
//         {
//             return listRef;
//         }
//     }
//     else
//     {
//         return NULL;
//     }
    
// }

// List * searchByWord(List * list, char word)
// {
//     if(list->listProx != NULL)
//     {
//         List * listRef = list->listProx;
//         while (listRef != NULL && listRef->dado.word != word)
//         {
//             listRef = listRef->listProx;
//         }
//         if (listRef == NULL)
//         {
//             return NULL;
//         }
//         else
//         {
//             return listRef;
//         }
//     }
//     else
//     {
//         return NULL;
//     }
    
// }
// void exibir(List list)
// {
//     List * listRef = list.listProx;
//     if (listRef == NULL)
//     {
//         printf("\nLista vazia");
//     }
    
//     while (listRef != NULL)
//     {
//         printf("\n");
// 		printf("Elemento: %d \n", listRef->id);
//         printf("Palavra: %c\n", listRef->dado.word);
//         printf("Quantidade: %d\n", listRef->dado.qtd);
//         printf("\n");
//         listRef = listRef->listProx;
//     }
    
// }