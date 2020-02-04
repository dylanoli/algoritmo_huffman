#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include <time.h>
#define MASKCODE1111 4294967295
#define MASKWORD0001 1
#define LENCODE sizeof(int)*8
#define LENWORD sizeof(char)*8
#define TRUE 1
#define FALSE 0

typedef struct tDado
{
    char word;
    unsigned int qtd;
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

typedef struct tTable
{
    char word;
    unsigned int code;
    unsigned char lenght;
}Table;
//------------List---------------------------
List * startList();
void addEndChar(List * list, char word);
void delay(int number_of_seconds) ;
void showList(List list);
//------------Node---------------------------
Node * startNode();
Node * startNodeWithElements(Node nodeRight, Node nodeLeft);
void showNodes(Node * node);
int lengthNodes(Node * node);
//------------Table---------------------------
Table getCodeByChar(Table * table,char Char);
List * buildCharTable(Table * table, List * str, Table * rest,unsigned char * charResult, char * len,int *lenghtCount);
unsigned char searchTable(unsigned char charBase, int len, Table * table, int sizeTable, int * ref, int * findBase, Table * rest, int flagFim);
void buildTable(Table * table, Node * node, int lenghtTable);
void findCode(unsigned int code, Node * node, Table * table, int * index,unsigned char lenght);
void bubblesortTable(Table * table, unsigned char lenght);
void showTable(Table * table, int lenght);
//------------NodeList-------------------------
NodeList * startNodeList();
NodeList * searchByWord(NodeList * list, char word);
void addNodeEndChar(NodeList * list, char word);
void addNodeEndDado(NodeList * list, Dado dado);
void addNodeEnd(NodeList * list, Node node);
void removeNodeLast(NodeList *nodeList);
void bubblesortNodeList(NodeList * nodeList);
void showNodeList(NodeList nodeList);
//------------List---------------------------
List * startList()
{
    List * list  = (List*)calloc(1,sizeof(List));
    list->id = 1;
    list->listProx = NULL;
    list->listAnte = NULL;
    return list;
}

void addNodeEndChar(NodeList * list, char word)
{
    NodeList * novoElemento = (NodeList*)calloc(1,sizeof(NodeList));
    
    novoElemento->node.dado.word = word;
    novoElemento->node.dado.qtd = 1;
    novoElemento->listProx = NULL;

    NodeList * ultimoElem = list->listAnte;
    if (ultimoElem==NULL)
    {
        list->listAnte = novoElemento;
        list->listProx = novoElemento;
    }
    else
    {
        ultimoElem->listProx = novoElemento;
        novoElemento->listAnte = ultimoElem;
    }
    list->listAnte = novoElemento;
}


void addNodeEndDado(NodeList * list, Dado dado)
{
    NodeList * novoElemento = (NodeList*)calloc(1,sizeof(NodeList));
    
    novoElemento->node.dado.word = dado.word;
    novoElemento->node.dado.qtd = dado.qtd;
    novoElemento->listProx = NULL;

    NodeList * ultimoElem = list->listAnte;
    if (ultimoElem==NULL)
    {
        list->listAnte = novoElemento;
        list->listProx = novoElemento;
    }
    else
    {
        ultimoElem->listProx = novoElemento;
        novoElemento->listAnte = ultimoElem;
    }
    list->listAnte = novoElemento;
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
void bubblesortNodeList(NodeList * nodeList)
{
    NodeList * listI = nodeList->listProx;
    while (listI != NULL && listI->listProx != NULL)
    {
        NodeList * listJ = nodeList->listProx;
        while (listJ != NULL && listJ->listProx != NULL)
        {
            if (listJ->node.dado.qtd < listJ->listProx->node.dado.qtd)
            {
                Node aux = listJ->node;
                listJ->node = listJ->listProx->node;
                listJ->listProx->node = aux;
            }
            listJ = listJ->listProx;
        }
        listI = listI->listProx;
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

NodeList * searchByWord(NodeList * list, char word)
{
    if(list->listProx != NULL)
    {
        NodeList * listRef = list->listProx;
        while (listRef != NULL && listRef->node.dado.word != word)
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
		printf("Elemento: %i \n", listRef->id);
		printf("Endereco: %i \n", listRef);
        printf("Palavra: %c\n", listRef->dado.word);
        printf("Quantidade: %i\n", listRef->dado.qtd);
		printf("Anterior: %i \n", listRef->listAnte);
		printf("Proximo: %i \n", listRef->listProx);
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
    printf("\nNode: %i\n", node);
    printf("Palavra: %c\n", node->dado.word);
    printf("Quantidade: %i\n", node->dado.qtd);
    printf("Direita: %i\n",node->right);
    printf("Esquerda: %i\n",node->left);
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
void buildTable(Table * table, Node * node, int lenghtTable)
{
    unsigned int code = 0;
    unsigned char lenght = 0;
    int index = 0;
    findCode(code, node, table, &index, lenght);
    bubblesortTable(table, lenghtTable);
}
void findCode(unsigned int code, Node * node, Table * table, int * index,unsigned char lenght)
{
    if (node->right==NULL && node->left==NULL)
    {
        table[*index].word = node->dado.word;
        table[*index].code = code;
        table[*index].lenght = lenght;
        (*index)++;
        
    }
    if (node->right!=NULL)
    {
        lenght++;
        code = code<<1;
        findCode(code, node->right, table, index,lenght);
    }
    if (node->left!=NULL)
    {
        lenght++;
        if (node->right!=NULL)
        {
            lenght--;
            code = code>>1;
        }
        code = code<<1;
        code = code|1;
        findCode(code, node->left, table, index,lenght);
    }
}
void bubblesortTable(Table * table, unsigned char lenght)
{
    int i, j;
    Table aux;
    for(i = 0; i<lenght; i++){
        for(int j = 0; j<lenght-1; j++){
            if(table[j].lenght > table[j + 1].lenght){
                aux = table[j];
                table[j] = table[j+1];
                table[j+1] = aux;
            }
        }
    }
}

Table getCodeByChar(Table * table, char Char)
{
    Table result;
    int i = -1;
    do
    {
        i++;
    } while (table[i].word != Char);
    result = table[i];
    return result;
}
List * buildCharTable(Table * table, List * str, Table * rest, unsigned char * charResult, char * len, int *lenghtCount)
{
    unsigned char Base = 0;
    unsigned int count = 0;
    if (rest->lenght > 0)
    {
        if (rest->lenght <= LENWORD)
        {
            Base = Base|(rest->code);
            count += (rest->lenght);
            rest->code = 0;
            rest->lenght = 0;
        }
        else
        {
            rest->lenght = rest->lenght-LENWORD;
            Base = Base|((rest->code>>rest->lenght));
            count += LENWORD;
            rest->code = rest->code&(~(MASKCODE1111<<rest->lenght));
        } 
    }
    if (str != NULL)
    {
        str = str->listProx;
    }
    while (str != NULL && count < LENWORD)
    {
        Table newChar;
        int restAux = 0;
        newChar = getCodeByChar(table,str->dado.word);
        if ((count + newChar.lenght) > LENWORD)
        {
            restAux = (count + newChar.lenght)-LENWORD;
            rest->code = newChar.code&(~(MASKCODE1111<<restAux));
            rest->lenght = restAux;
            newChar.code = newChar.code>>restAux;
        }
        Base = Base<<(newChar.lenght-restAux);
        Base = Base|newChar.code;
        count += newChar.lenght;
        str = str->listProx;
        (*lenghtCount)++;
    }
    *charResult = Base;
    *len = count;
    if (str == NULL) 
    {
        return NULL;
    }
    else
    {
        if (rest->lenght==0)
        {
            (*charResult) = (*charResult)<<(LENWORD-count);            
        }
        return str->listAnte;
    }
    
}
unsigned char searchNode(unsigned char charBase, int leghtLast, Node * node, int ref, int flagFim)
{
    int pivo = 1;
    Node * auxNode = node;
    while (auxNode->right != NULL && auxNode->left != NULL)
    {
        char aux = (charBase>>LENWORD-pivo)&MASKWORD0001;
        if (aux == 1)
        {
            auxNode = auxNode->right;
        }
        else
        {
            auxNode = auxNode->left;
        }
        pivo++;
    }
    
    
}
unsigned char searchTable(unsigned char charBase, int len, Table * table, int sizeTable, int * ref, int * findBase, Table * rest, int flagFim)
{
    int find = 0;
    unsigned char result;
    int index = (LENCODE-1) - (*ref) -rest->lenght;
    int endWord = LENCODE;
    unsigned int codeBase = 0;
    Table aux;
    if (flagFim == 1)
    {
        endWord=len;
    }
    if (!flagFim)
    {
        codeBase = ((unsigned int)(charBase))<<((LENCODE+(*ref))-(LENWORD+rest->lenght));
    }
    else
    {
        codeBase = ((unsigned int)(charBase))<<((LENCODE+(*ref))-(endWord+rest->lenght));
    }
    codeBase = codeBase|((rest->code)<<((LENCODE+(*ref))-rest->lenght));
    while (find == 0 && index>=(LENCODE-LENWORD-rest->lenght) && (*ref)<endWord)
    {
        aux.code = codeBase;
        aux.code = aux.code>>index+(*ref);
        aux.lenght = LENCODE-((*ref)+index);
        int i;
        for (i = 0; i < sizeTable; i++)
        {
            if (aux.code == table[i].code && aux.lenght == table[i].lenght)
            {
                result = table[i].word;
                find = 1;
            }
        }
        index--;
    }
    
    if (find == FALSE)
    {
        *rest = aux;
        *ref = LENWORD;
    }
    else
    {
        *ref = (LENCODE-(index+1+rest->lenght)); 
        rest->code = 0;
        rest->lenght = 0;  
    }
    *findBase = find;
    return result;
}
void showTable(Table * table, int lenght)
{
    int i;
    for ( i = 0; i < lenght; i++)
    {
        printf("\n\nTable[%i]:",i);
        printf("\nChar: %c",table[i].word);
        printf("\nCode: %i",table[i].code);
        printf("\nLenght: %i",table[i].lenght);
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

void addNodeEnd(NodeList * list, Node node)
{
    NodeList * novoElemento = (NodeList*)calloc(1,sizeof(NodeList));
    Node * nodeNovo = (Node*)calloc(1,sizeof(Node));
    *nodeNovo = node;
    novoElemento->node = *nodeNovo;

    novoElemento->listProx = NULL;

    NodeList * ultimoElem = list->listAnte;
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

        if (elementoAnte != NULL)
        {
            elementoAnte->listProx = element->listProx;
        }
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
    NodeList * listRef = &nodeList;
    if (listRef == NULL)
    {
        printf("\nLista vazia");
    }
    
    while (listRef != NULL)
    {
        printf("\n");
		printf("Elemento: %i \n", listRef);
        printf("Palavra: %c\n", listRef->node.dado.word);
        printf("Quantidade: %i\n", listRef->node.dado.qtd);
        printf("Proximo: %i\n", listRef->listProx);
        printf("Anterior: %i\n", listRef->listAnte);
        printf("\n");
        listRef = listRef->listProx;
    }
}