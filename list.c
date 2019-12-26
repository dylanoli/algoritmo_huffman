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

typedef struct tNode
{
    Dado dado;
    struct tNode * right;
    struct tNode * left;
}Node;

typedef struct tNodeList
{
    Node node;
    struct tNodeList * listProx;
    struct tNodeList * listAnte;
}NodeList;

//------------List---------------------------
List * startList();
void adicionarInicio(List * list, Dado dado);
void adicionarFim(List * list, Dado dado);
void addEndChar(List * list, char word);
void removeEnd(List * list);
void removeStart(List * list);
void remover(List * list, int id);
void quickSort(List * list, int began, int end);
void delay(int number_of_seconds) ;
void showList(List list);
List * searchByID(List * list, int id);
List * searchByWord(List * list, char word);
List * searchFirst(List * list);
//------------Node---------------------------
Node * startNode();
Node * startNodeWithElements(Node nodeRight, Node nodeLeft);
Node * transformNode(Dado dado);
void showNodes(Node * node);
//------------Table---------------------------
void buildTable(char ** table, int lenght ,Node * node);
void findCode(char code, Node * node, char ** table, int * index);
char getCodeByChar(char Char);
void showTable(char ** table, int lenght);
//------------NodeList-------------------------
NodeList * startNodeList();
void addNodeStart(NodeList * list, Node node);
//------------List---------------------------
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
void removeEnd(List * list)
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
void removeStart(List * list)
{
    List * element = list->listProx;
    if(element != NULL)
    {
        list->listProx = element->listProx;
        if (element->listProx == NULL)
        {
            list->listAnte = NULL;
        }
        else
        {
            element->listProx->listAnte = list;
        }
        element->listProx=NULL;
        element->listAnte=NULL;
        free(element);
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
	while(i < j)
	{
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
		if(i <= j )
		{
            if (searchByID(list,(i))->dado.qtd != searchByID(list,(j))->dado.qtd)
            {
                Dado aux =  searchByID(list,(i))->dado;
                searchByID(list,(i))->dado = searchByID(list,(j))->dado;
                searchByID(list,(j))->dado = aux;
            }
			i++;
			j--;
		}
	}
	if(j > began)
	{
        quicksort(list, began, j);
    }	
    
	if(i < end)
    {
		quicksort(list, i, end);
    }
}
void delay(int number_of_seconds) 
{ 
    // Converting time into milli_seconds 
    int milli_seconds = 1000 * number_of_seconds; 
  
    // Stroing start time 
    clock_t start_time = clock(); 
  
    // looping till required time is not acheived 
    while (clock() < start_time + milli_seconds); 
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

List * searchFirst(List * list)
{
    List * element = list->listProx;
    return element;
}

void showList(List list)
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
//------------Node---------------------------
Node * startNode()
{
    Node * node = (Node*)calloc(1,sizeof(Node));
    node->right = NULL;
    node->left = NULL;
    return node;
}
Node * startNodeWithElements(Node nodeRight, Node nodeLeft)
{
    Node * node = (Node*)calloc(1,sizeof(Node));
    Node * right = (Node*)calloc(1,sizeof(Node));
    Node * left = (Node*)calloc(1,sizeof(Node));
    *right = nodeRight;
    *left = nodeLeft;
    node->dado.word = ' ';
    node->dado.qtd = nodeRight.dado.qtd + nodeLeft.dado.qtd;
    node->right = right;
    node->left = left;
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
int lengthNodes(Node * node)
{
    int count = 0;
    if (node->right==NULL && node->left==NULL)
    {
        count++;
    }
    if (node->right!=NULL)
    {
        count += lengthNodes(node->right);
    }
    
    if (node->left!=NULL)
    {
        count += lengthNodes(node->left);
    }
    
    return count;
}
void showNodes(Node * node)
{
    printf("\nNode: %d\n", node);
    printf("Palavra: %c\n", node->dado.word);
    printf("Quantidade: %d\n", node->dado.qtd);
    printf("Direita: %d\n",node->right);
    printf("Esquerda: %d\n",node->left);
    if (node->right!=NULL)
    {
        showNodes(node->right);
    }
    if (node->left!=NULL)
    {
        showNodes(node->left);
    }
}
//------------Table---------------------------
void buildTable(char ** table, int lenght, Node * node)
{
    char code = 1;
    int index = 0;
    findCode(code, node, table, &index);
}
void findCode(char code, Node * node, char ** table, int * index)
{
    if (node->right==NULL && node->left==NULL)
    {
        table[*index][0] = node->dado.word;
        table[*index][1] = code;
        (*index)++;
    }
    if (node->left!=NULL)
    {
        code = code<<1;
        findCode(code, node->left, table, index);
    }
    if (node->right!=NULL)
    {
        if (node->left!=NULL)
        {
            code = code>>1;
        }
        code = code<<1;
        code = code|1;
        findCode(code, node->right, table, index);
    }
    
}
void showTable(char ** table, int lenght)
{
    int i;
    for ( i = 0; i < lenght; i++)
    {
        printf("\n\nTable[%d]:",i);
        int j;
        for (j = 0; j < 2; j++)
        {
            if (j==0)
            {
                printf("\nChar: %c",table[i][j]);
            }
            else
            {
                printf("\nCode: %d",table[i][j]);
            }
        }
    }
}

//------------NodeList-------------------------
NodeList * startNodeList()
{
    NodeList * list  = (NodeList*)calloc(1,sizeof(NodeList));
    list->listProx = NULL;
    list->listAnte = NULL;
    return list;
}
void addNodeStart(NodeList * list, Node node)
{
    NodeList * novoElemento = (NodeList*)calloc(1,sizeof(NodeList));
    Node * nodeNovo = (Node*)calloc(1,sizeof(Node));
    *nodeNovo = node;
    
    novoElemento->node = *nodeNovo;

    novoElemento->listProx = list->listProx;
    novoElemento->listAnte = list;
    
    
    if (list->listProx == NULL)
    {
        list->listAnte=novoElemento;
    }
    else
    {
        list->listProx->listAnte = novoElemento;
    }
    list->listProx = novoElemento;
}
void removeNodeStart(NodeList *nodeList)
{
    NodeList * element = nodeList->listProx;
    if(element != NULL)
    {
        nodeList->listProx = element->listProx;
        if (element->listProx == NULL)
        {
            nodeList->listAnte = NULL;
        }
        else
        {
            element->listProx->listAnte = nodeList;
        }
        element->listProx=NULL;
        element->listAnte=NULL;
        free(element);
    }
}
void removeNodeLast(NodeList *nodeList)
{
    NodeList * element = nodeList->listAnte;
    if(element != NULL)
    {
        NodeList * elementoAnte = element->listAnte;
        NodeList * elementoProx = element->listProx;

        elementoAnte->listProx = element->listProx;
        if (nodeList->listAnte == element)
        {
            nodeList->listAnte = elementoAnte;
        }
        else
        {
            elementoProx->listAnte = element->listAnte;
        }
        element->listProx=NULL;
        element->listAnte=NULL;
    }
}
void showNodeList(NodeList nodeList)
{
    NodeList * listRef = nodeList.listProx;
    if (listRef == NULL)
    {
        printf("\nLista vazia");
    }
    
    while (listRef != NULL)
    {
        printf("\n");
		printf("Elemento: %d \n", listRef);
        printf("Palavra: %c\n", listRef->node.dado.word);
        printf("Quantidade: %d\n", listRef->node.dado.qtd);
        printf("Proximo: %d\n", listRef->listProx);
        printf("Anterior: %d\n", listRef->listAnte);
        printf("\n");
        listRef = listRef->listProx;
    }
}