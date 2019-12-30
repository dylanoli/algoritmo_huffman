#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <time.h> 
#include"list.c"

int makeMenu();
void compress();
void decompress();

int main()
{
    int option = -1;
    while (option != 0)
    {
        option = makeMenu();
    }
    return 0;
}

int makeMenu()
{
    int option = -1;
    printf("\n---------- Menu Principal ----------");
    printf("\n[1] Compactar Arquivo");
    printf("\n[2] Descompactar Arquivo");
    printf("\n[0] Sair");
    printf("\n\nSelecione uma opcao: ");
    scanf("%d",&option);
    system("clear"); //limpa o console no linux
    system("cls"); //limpa o console no windows

    switch (option)
    {
    case 1:
        compress();
        break;
    case 2:
        decompress();
        break;
    case 0:
        printf("\nPrograma finalizado.");
        break;
    default:
        printf("\nOpcao invalida, tente novamente.");
        break;
    }
    return option;
}

void compress()
{
    printf("\n---------- Compactar ----------");
    printf("\nDigite o diretorio do arquivo: ");
    fflush(stdin);
    char pathFile[200];
    scanf("%s[^\n]",pathFile);
    FILE * pFile = fopen(pathFile,"rb");
    if (pFile == NULL)
    {
        fclose(pFile);
        printf("Arquivo nao encontrado!");
    }
    else
    {
        char c;
        List * list = startList();
        List * listStr = startList();
        NodeList * nodeList = startNodeList();
        while (fread(&c,1,1,pFile)>0)
        {
            List * element = searchByWord(list,c);
            if (element == NULL)//caso nao encontre elemento
            {
                addEndChar(list,c);
            }
            else
            {
                element->dado.qtd++;
            }
            addEndChar(listStr,c);
        }
        fclose(pFile);
        // showList(*listStr);
        if (list->listProx != NULL)//verifica se o arquivo está vazio
        {
            printf("\nCompactando arquivo...");
            clock_t start, end;
            double cpu_time_used;
            
            start = clock();
            // while (list->listProx != NULL && nodeList->listProx->listProx != NULL)
            // {
            //     quicksort(list, 1, list->id-1);//organiza a lista encadeada
            // }
            while (list->listProx != NULL )
            {
                Node * node = transformNode(list->listProx->dado);
                removeStart(list);
                addNodeStart(nodeList, *node);
            }
            // bubblesortNodeList(nodeList);
            // showNodeList(*nodeList);
            while (nodeList->listProx->listProx != NULL)
            {
                bubblesortNodeList(nodeList);
                Node * nodeLeft = &nodeList->listAnte->node;
                removeNodeLast(nodeList);
                Node * nodeRight = &nodeList->listAnte->node;
                removeNodeLast(nodeList);
                Node * node = startNodeWithElements(*nodeRight,*nodeLeft);       
                addNodeEnd(nodeList,*node);
            }
            Node * node = &nodeList->listProx->node;
            int lenght = lengthNodes(node);
            // printf("\nLEN: %d",lenght);
            Table* table = (Table*)calloc(lenght,sizeof(Table));
            buildTable(table,node, lenght);

            // showTable(table, lenght);
            List * strRef = listStr;
            Table rest;
            rest.code = 0;
            rest.lenght = 0;
            unsigned char restLen = 0;
            strcat(pathFile,".cp");
            FILE * pFileFinal = fopen(pathFile,"wb");
            unsigned char charRead;
            int len = 0;
            //---------------Gravando Arquivo--------------
            //Formato lenghtLast + lenghtTable + table + arquivoCompactado
            fprintf(pFileFinal,"%c", len);
            fwrite((const void*) & lenght,sizeof(int),1,pFileFinal);//Gravando lenghtTable
            int i;
            for ( i = 0; i < lenght; i++) //Gravando table
            {
                fprintf(pFileFinal,"%c", table[i].word);
                fwrite((const void*) & table[i].code,LENCODE/8,1,pFileFinal);
                fprintf(pFileFinal,"%c", table[i].lenght);
            }
            do//Gravando Arquivo Compactado
            {
                strRef = buildCharTable(table,strRef, &rest, &charRead,&len);
                
                // if (strRef != NULL && strRef->listAnte->dado.word == 'p')
                // {
                    // printf("\n[%d]\n", charRead);
                // }
                
                fprintf(pFileFinal,"%c", charRead);
            }
            while (strRef != NULL || rest.lenght > 0);
            fseek(pFileFinal, 0, SEEK_SET);
            fprintf(pFileFinal,"%c", len);
            fclose(pFileFinal);
            end = clock();
            cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
            printf("\nConcluido!");
            printf("\nDuracao: %.2lf segundos",cpu_time_used);
        }
        else
        {
            printf("\nO arquivo esta vazio!");
        }
    }  
}

void decompress()
{
    printf("\n---------- Descompactar ----------");
    printf("\nDigite o diretorio do arquivo: ");
    fflush(stdin);
    char pathFile[200];
    scanf("%s[^\n]",pathFile);
    int lengthPath = strlen(pathFile);
    FILE * pFile = fopen(pathFile,"rb");
    if (pFile == NULL)
    {
        fclose(pFile);
        printf("Arquivo nao encontrado!");
    }
    else
    {
        printf("\nDesompactando arquivo...\n");
        clock_t start, end;
        double cpu_time_used;
        
        start = clock();
        unsigned char charBase;
        int len = 0; //tamanho da palavra final
        int lengthTable = 0;
        fread(&len,1,1,pFile);
        fread(&lengthTable,sizeof(int),1,pFile);
        Table* table = (Table*)calloc(lengthTable,sizeof(Table));
        int i;
        for (i = 0; i < lengthTable; i++)
        {
            fread(&table[i].word,1,1,pFile);
            fread(&table[i].code,LENCODE/8,1,pFile);
            fread(&table[i].lenght,1,1,pFile);
        }
        // showTable(table,lengthTable);
        // printf("\n");
        pathFile[lengthPath-3] = '\0';
        Table rest;
        rest.code=0;
        rest.lenght=0;
        int ref = 0;
        int find = 0;
        int flagFIM = 0;
        FILE * pFileFinal = fopen(pathFile,"wb");
        while (fread(&(charBase),1,1,pFile)>0 && flagFIM == 0)
        {
            char trash;
            if (fread(&trash,1,1,pFile)==0)
            {
                flagFIM = 1;
            }
            fseek(pFile, -1, SEEK_CUR);
            while (ref != LENWORD)
            {
                unsigned char result = searchTable(charBase, len ,table,lengthTable,&ref, &find, &rest, flagFIM);
                // printf("%d ", result);
                if (find == 1)
                {
                    fprintf(pFileFinal,"%c", result);
                }
            }
            ref = 0;
        }
        fclose(pFile);
        fclose(pFileFinal);
        end = clock();
        cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
        printf("\nConcluido!");
        printf("\nDuracao: %.2lf segundos",cpu_time_used);
    }
}