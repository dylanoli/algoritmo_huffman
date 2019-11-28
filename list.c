#include<stdlib.h>
#include<stdio.h>
#include<string.h>

typedef struct tDado
{
    char word;
    char qtd;
}Dado;

typedef struct tLista
{
    int id;
    Dado dado;
    struct tLista * listaProx;
    struct tLista * listaAnte;
}Lista;

Lista inicializarLista();
void adicionarInicio(Lista * lista, Dado dado);
void adicionarFim(Lista * lista, Dado dado);
void removerFim(Lista * lista);
void remover(Lista * lista, int id);
void exibir(Lista lista);
Lista * buscar(Lista * lista, int id);
Lista * searchWord(Lista * lista, char word);


Lista inicializarLista()
{
    Lista lista;
    lista.id = 1;
    lista.listaProx = NULL;
    lista.listaAnte = NULL;
    return lista;
}
void adicionarInicio(Lista * lista, Dado dado)
{
    Lista * novoElemento = (Lista*)calloc(1,sizeof(Lista));
    novoElemento->id = lista->id;
    novoElemento->dado.word = dado.word;
    novoElemento->dado.qtd = dado.qtd;

    novoElemento->listaProx = lista->listaProx;
    novoElemento->listaAnte = lista;
    lista->listaProx = novoElemento;
    
    
    if (lista->id==1)
    {
        lista->listaAnte=novoElemento;
    }
    else
    {
        novoElemento->listaProx->listaAnte = lista->listaProx;
    }
    
    lista->id++;

}
void adicionarFim(Lista * lista, Dado dado)
{
    Lista * novoElemento = (Lista*)calloc(1,sizeof(Lista));
    novoElemento->id = lista->id;
    
    novoElemento->dado.word = dado.word;
    novoElemento->dado.qtd = dado.qtd;
    novoElemento->listaProx = NULL;

    Lista * ultimoElem = lista->listaAnte;
    if (ultimoElem==NULL)
    {
        lista->listaAnte = ultimoElem;
        lista->listaProx = novoElemento;
    }
    else
    {
        ultimoElem->listaProx = novoElemento;
        novoElemento->listaAnte = ultimoElem;
    }
    lista->listaAnte = novoElemento;
    lista->id++;
}
void removerFim(Lista * lista)
{
    Lista * elemento = lista->listaAnte;
    if(elemento != NULL)
    {
        Lista * elementoAnte = elemento->listaAnte;
        Lista * elementoProx = elemento->listaProx;

        elementoAnte->listaProx = elemento->listaProx;
        if (lista->listaAnte == elemento)
        {
            lista->listaAnte = elementoAnte;
        }
        else
        {
            elementoProx->listaAnte = elemento->listaAnte;
        }
        elemento->listaProx=NULL;
        elemento->listaAnte=NULL;
        free(elemento);
    }
}
void remover(Lista * lista, int id)
{
    Lista * elemento = buscar(lista, id);
    if(elemento != NULL)
    {
        Lista * elementoAnte = elemento->listaAnte;
        Lista * elementoProx = elemento->listaProx;

        elementoAnte->listaProx = elemento->listaProx;
        if (lista->listaAnte == elemento)
        {
            lista->listaAnte = elementoAnte;
        }
        else
        {
            elementoProx->listaAnte = elemento->listaAnte;
        }
        elemento->listaProx=NULL;
        elemento->listaAnte=NULL;
        free(elemento);
    }
}

Lista * buscar(Lista * lista, int id)
{
    if(lista->listaProx != NULL)
    {
        Lista * listaRef = lista->listaProx;
        while (listaRef != NULL && listaRef->id != id)
        {
            listaRef = listaRef->listaProx;
        }
        if (listaRef == NULL)
        {
            return NULL;
        }
        else
        {
            return listaRef;
        }
    }
    else
    {
        return NULL;
    }
    
}

Lista * searchWord(Lista * lista, char word)
{
    if(lista->listaProx != NULL)
    {
        Lista * listaRef = lista->listaProx;
        while (listaRef != NULL && listaRef->dado.word != word)
        {
            listaRef = listaRef->listaProx;
        }
        if (listaRef == NULL)
        {
            return NULL;
        }
        else
        {
            return listaRef;
        }
    }
    else
    {
        return NULL;
    }
    
}
void exibir(Lista lista)
{
    Lista * listaRef = lista.listaProx;
    if (listaRef == NULL)
    {
        printf("\nLista vazia");
    }
    
    while (listaRef != NULL)
    {
        printf("\n");
		printf("Elemento: %d \n", listaRef);
        printf("ID: %d\n", listaRef->id);
        printf("Palavra: %c\n", listaRef->dado.word);
        printf("Quantidade: %c\n", listaRef->dado.qtd);
        printf("Proximo: %d\n", listaRef->listaProx);
        printf("Anterior: %d\n", listaRef->listaAnte);
        printf("\n");
        listaRef = listaRef->listaProx;
    }
    
}