#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include <time.h>
#define MASKCODE1111 4294967295
#define LENCODE sizeof(int)*8
#define LENWORD sizeof(char)*8

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
NodeList * searchByWord(NodeList * list, char word);
List * searchFirst(List * list);
//------------Node---------------------------
Node * startNode();
Node * startNodeWithElements(Node nodeRight, Node nodeLeft);
Node * transformNode(Dado dado);
void showNodes(Node * node);
int lengthNodes(Node * node);
//------------Table---------------------------
void buildTable(Table * table, Node * node, int lenghtTable);
void findCode(unsigned int code, Node * node, Table * table, int * index,unsigned char lenght);
void bubblesortTable(Table * table, unsigned char lenght);
Table getCodeByChar(Table * table,char Char);
List * buildCharTable(Table * table, List * str, Table * rest,unsigned char * charResult, int * len);
unsigned char searchTable(unsigned char charBase, int len, Table * table, int sizeTable, int * ref, int * findBase, Table * rest, int flagFim);
void showTable(Table * table, int lenght);
//------------NodeList-------------------------
NodeList * startNodeList();
void addNodeEndChar(NodeList * list, char word);
void addNodeStart(NodeList * list, Node node);
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
		printf("Endereco: %d \n", listRef);
        printf("Palavra: %c\n", listRef->dado.word);
        printf("Quantidade: %d\n", listRef->dado.qtd);
		printf("Anterior: %d \n", listRef->listAnte);
		printf("Proximo: %d \n", listRef->listProx);
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
List * buildCharTable(Table * table, List * str, Table * rest, unsigned char * charResult, int * len)
{
    unsigned char Base = 0;
    unsigned int count = 0;
    if (rest->lenght > 0)
    {
        // Base = Base<<(rest->lenght);
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
        // printf(" [%d-%d] ", newChar.code,newChar.lenght);
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
        // if (str->dado.word == 'p')
        // {
            // printf("\nnewCharCODE: %d",newChar.code);
            // printf("\nnewCharLEN: %d",newChar.lenght);
            // printf("\nCharResult: %d",(*charResult));
            // printf("\nBASE: %d",Base);
            // printf("\nLEN: %d",count);
        // }
        str = str->listProx;
    }
    // printf("\n0BASE0: %d",Base);
    *charResult = Base;
    *len = count;
    // printf("\n0CharResult0: %d",*charResult);
    if (str == NULL) 
    {
        
        // printf("\nWORD: %c",str->listAnte->dado.word);
        // printf("\nCharResult: %d",*charResult);
        return NULL;
    }
    else
    {
        if (rest->lenght==0)
        {
            (*charResult) = (*charResult)<<(LENWORD-count);            
        }
        // printf("\nWORD: %c",str->listAnte->dado.word);
        // printf("\nCharResult: %d",*charResult);
        return str->listAnte;
    }
    
}
unsigned char searchTable(unsigned char charBase, int len, Table * table, int sizeTable, int * ref, int * findBase, Table * rest, int flagFim)
{
    int find = 0;
    unsigned char result;
    int index = (LENCODE-1) - (*ref);
    int endWord = LENCODE;
    Table aux;
    if (flagFim == 1)
    {
        endWord=len;
    }
    while (find == 0 && index>=(LENCODE-LENWORD) && (*ref)<endWord)
    {
        if (!flagFim)
        {
            aux.code = ((unsigned int)(charBase))<<(LENCODE-LENWORD);
        }
        else
        {
            aux.code = ((unsigned int)(charBase))<<(LENCODE-endWord);
        }
        aux.code = aux.code&(MASKCODE1111<<index);
        aux.code = aux.code&(MASKCODE1111>>(*ref));
        aux.code = aux.code>>index;
        aux.lenght = LENCODE-((*ref)+index);
        // if (flagFim)
        // {
        //     showTable(&aux,1);
        //     printf("\nCharBase: ");
        //     printf("%d",charBase);
        // }
        
        // showTable(&aux,1);
        if (rest->lenght>0)
        {
            aux.code = aux.code|((rest->code)<<aux.lenght);
            aux.lenght += rest->lenght;
        }
        int i;
        for (i = 0; i < sizeTable; i++)
        {
            if (aux.code == table[i].code && aux.lenght == table[i].lenght)
            {
                result = table[i].word;
                find = 1;
                // if (table[i].word == 'p')
                // {
                //     printf("\nTABLE:");
                //     showTable(&aux,1);
                //     printf("\nCharBase: ");
                //     printf("%d",charBase);
                // }
                
                // printf("\nFIND.....");
            }
        }
        index--;
    }
    rest->code = 0;
    rest->lenght = 0;
    if (find == 0)
    {
        // printf("\nRESTO.....");
        // showTable(&aux,1);
        *rest = aux;
        *ref = LENWORD;
    }
    else
    {
        *ref = (LENCODE-(index+1));   
    }
    *findBase = find;
    return result;
}
void showTable(Table * table, int lenght)
{
    int i;
    for ( i = 0; i < lenght; i++)
    {
        printf("\n\nTable[%d]:",i);
        printf("\nChar: %c",table[i].word);
        printf("\nCode: %d",table[i].code);
        printf("\nLenght: %d",table[i].lenght);
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
		printf("Elemento: %d \n", listRef);
        printf("Palavra: %c\n", listRef->node.dado.word);
        printf("Quantidade: %d\n", listRef->node.dado.qtd);
        printf("Proximo: %d\n", listRef->listProx);
        printf("Anterior: %d\n", listRef->listAnte);
        printf("\n");
        listRef = listRef->listProx;
    }
}