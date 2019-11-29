#include"list.h"
List * startList()
{
    List * list  = (List*)calloc(1,sizeof(List));
    list->id = 1;
    list->listProx = NULL;
    list->listAnte = NULL;
    return list;
}
void adicionarInicio(List * list, Dado dado)
{
    List * novoElemento = (List*)calloc(1,sizeof(List));
    novoElemento->id = list->id;
    novoElemento->dado.word = dado.word;
    novoElemento->dado.qtd = dado.qtd;

    novoElemento->listProx = list->listProx;
    novoElemento->listAnte = list;
    list->listProx = novoElemento;
    
    
    if (list->id==1)
    {
        list->listAnte=novoElemento;
    }
    else
    {
        novoElemento->listProx->listAnte = list->listProx;
    }
    
    list->id++;

}
void adicionarFim(List * list, Dado dado)
{
    List * novoElemento = (List*)calloc(1,sizeof(List));
    novoElemento->id = list->id;
    
    novoElemento->dado.word = dado.word;
    novoElemento->dado.qtd = dado.qtd;
    novoElemento->listProx = NULL;

    List * ultimoElem = list->listAnte;
    if (ultimoElem==NULL)
    {
        list->listAnte = ultimoElem;
        list->listProx = novoElemento;
    }
    else
    {
        ultimoElem->listProx = novoElemento;
        novoElemento->listAnte = ultimoElem;
    }
    list->listAnte = novoElemento;
    list->id++;
}

void addEndChar(List * list, char word)
{
    List * novoElemento = (List*)calloc(1,sizeof(List));
    novoElemento->id = list->id;
    
    novoElemento->dado.word = word;
    novoElemento->dado.qtd = 1;
    novoElemento->listProx = NULL;

    List * ultimoElem = list->listAnte;
    if (ultimoElem==NULL)
    {
        list->listAnte = ultimoElem;
        list->listProx = novoElemento;
    }
    else
    {
        ultimoElem->listProx = novoElemento;
        novoElemento->listAnte = ultimoElem;
    }
    list->listAnte = novoElemento;
    list->id++;
}
void removerFim(List * list)
{
    List * elemento = list->listAnte;
    if(elemento != NULL)
    {
        List * elementoAnte = elemento->listAnte;
        List * elementoProx = elemento->listProx;

        elementoAnte->listProx = elemento->listProx;
        if (list->listAnte == elemento)
        {
            list->listAnte = elementoAnte;
        }
        else
        {
            elementoProx->listAnte = elemento->listAnte;
        }
        elemento->listProx=NULL;
        elemento->listAnte=NULL;
        free(elemento);
    }
}
void remover(List * list, int id)
{
    List * elemento = searchByID(list, id);
    if(elemento != NULL)
    {
        List * elementoAnte = elemento->listAnte;
        List * elementoProx = elemento->listProx;

        elementoAnte->listProx = elemento->listProx;
        if (list->listAnte == elemento)
        {
            list->listAnte = elementoAnte;
        }
        else
        {
            elementoProx->listAnte = elemento->listAnte;
        }
        elemento->listProx=NULL;
        elemento->listAnte=NULL;
        free(elemento);
    }
}

void quicksort(List * list, int began, int end)
{
	int i, j, pivo;
	i = began;
	j = end;
	pivo = searchByID(list,((began + end) / 2))->dado.qtd;
    printf("\nI = %d - J = %d", i,j);
    printf("\nAqui1");
	while(i < j)
	{
        printf("\nAqui2");
        List * listRef = searchByID(list,(i));
		while( listRef->dado.qtd < pivo && i < end)
		{
            i++;
			listRef = listRef->listProx;
		}
        listRef = searchByID(list,(j));
		while(listRef->dado.qtd > pivo && j > began)
		{
            j--;
			listRef = listRef->listAnte;
		}
		if(i < j)
		{
			Dado aux =  searchByID(list,(i))->dado;
			searchByID(list,(i))->dado = searchByID(list,(j))->dado;
			searchByID(list,(j))->dado = aux;
			i++;
			j--;
		}
	}
    
    printf("\nAqui3");
	if(j > began)
	{
        quicksort(list, began, j);
    }	
	if(i < end)
    {
		quicksort(list, i, end);
    }
}

List * searchByID(List * list, int id)
{
    if(list->listProx != NULL)
    {
        List * listRef = list->listProx;
        while (listRef != NULL && listRef->id != id)
        {
            listRef = listRef->listProx;
        }
        if (listRef == NULL)
        {
            return NULL;
        }
        else
        {
            return listRef;
        }
    }
    else
    {
        return NULL;
    }
    
}

List * searchByWord(List * list, char word)
{
    if(list->listProx != NULL)
    {
        List * listRef = list->listProx;
        while (listRef != NULL && listRef->dado.word != word)
        {
            listRef = listRef->listProx;
        }
        if (listRef == NULL)
        {
            return NULL;
        }
        else
        {
            return listRef;
        }
    }
    else
    {
        return NULL;
    }
    
}
void exibir(List list)
{
    List * listRef = list.listProx;
    if (listRef == NULL)
    {
        printf("\nLista vazia");
    }
    
    while (listRef != NULL)
    {
        printf("\n");
		printf("Elemento: %d \n", listRef->id);
        printf("Palavra: %c\n", listRef->dado.word);
        printf("Quantidade: %d\n", listRef->dado.qtd);
        printf("\n");
        listRef = listRef->listProx;
    }
    
}