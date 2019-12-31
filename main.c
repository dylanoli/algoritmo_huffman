#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <time.h> 
#include"essentials.c"

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
    //recebe diretorio
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
        List * listStr = startList();
        int strLenght = 0;
        int strLenghtCurrent = 0;
        NodeList * nodeList = startNodeList();
        while (fread(&c,1,1,pFile)>0)
        {
            //montando a *List
            NodeList * element = searchByWord(nodeList,c);//procurando elemento repetido
            if (element == NULL)//caso nao encontre elemento
            {
                addNodeEndChar(nodeList,c);
            }
            else
            {
                element->node.dado.qtd++;
            }
            //montando a string
            addEndChar(listStr,c); 
            strLenght++;
        }
        fclose(pFile);
        if (nodeList->listProx != NULL)//verifica se o arquivo está vazio
        {
            printf("\nCompactando arquivo...\n");
            //medindo o tempo
            clock_t start, end;
            double cpu_time_used;
            start = clock();
            
            /*Implementando a arvore do Huffman
            * Consiste em ordenar a lista pela frequencia e
            * transformar os menos frequentes em ramificações de um no,
            * o processo se repete até exista somente um elemento, que eh a raiz da arvore
            */
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

            Node * node = &nodeList->listProx->node;//removendo o ultimo no da lista para torna-lo independente
            int lenght = lengthNodes(node); //identificando o tamanho da arvore, para criar a tabela
            //Criando a tabela e inserindo elementos
            Table* table = (Table*)calloc(lenght,sizeof(Table));
            buildTable(table,node, lenght);

            //criacao de variaveis
            List * strRef = listStr;
            Table rest;
            rest.code = 0;
            rest.lenght = 0;
            unsigned char restLen = 0;
            unsigned char charRead;
            char len = 0;
            //criando arquivo compacto com final .cp
            strcat(pathFile,".cp");
            FILE * pFileFinal = fopen(pathFile,"wb");
            //---------------Gravando Arquivo--------------
            //Formato lenghtLast + lenghtTable + table + arquivoCompactado
            fprintf(pFileFinal,"%c", len);//alocando espaco para guardar o lenghtLast
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
                strRef = buildCharTable(table,strRef, &rest, &charRead,&len,&strLenghtCurrent);                
                fprintf(pFileFinal,"%c", charRead);
                // printf("\rValue of X is: %d", x/114);
                // printf("\r%.2lf%%", ((float)(strLenghtCurrent)/strLenght)*100);
                fflush(stdout);
                
            }
            while (strRef != NULL || rest.lenght > 0);
            fseek(pFileFinal, 0, SEEK_SET);
            fprintf(pFileFinal,"%c", len);//Gravando lengthLast no espaco alocado

            fclose(pFileFinal);

            end = clock();//encerrando contagem de tempo
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
    
    //recebe diretorio
    fflush(stdin);
    char pathFile[200];
    scanf("%s[^\n]",pathFile);
    int lengthPath = strlen(pathFile);
    FILE * pFile = fopen(pathFile,"rb");
    if (pFile == NULL)//verifica se o arquivo existe
    {
        fclose(pFile);
        printf("Arquivo nao encontrado!");
    }
    else
    {
        printf("\nDesompactando arquivo...\n");
     
        //medindo o tempo   
        clock_t start, end;
        double cpu_time_used;
        start = clock();
        
        List * listStr = startList();
        unsigned char charBase;
        int len = 0; //tamanho da palavra final
        int lengthTable = 0;
        fread(&len,1,1,pFile);//ler lengthLast
        fread(&lengthTable,sizeof(int),1,pFile); //ler lengthTable
        //ler tabela de codigos
        Table* table = (Table*)calloc(lengthTable,sizeof(Table));
        int i;
        for (i = 0; i < lengthTable; i++)
        {
            fread(&table[i].word,1,1,pFile);
            fread(&table[i].code,LENCODE/8,1,pFile);
            fread(&table[i].lenght,1,1,pFile);
        }
        pathFile[lengthPath-3] = '\0';//montando o nome do arquivo original
        
        //Criando variaveis
        Table rest;
        rest.code=0;
        rest.lenght=0;
        int ref = 0;
        int find = 0;
        int flagFIM = 0;

        //passando o conteudo compacto para uma string
        while (fread(&charBase,1,1,pFile)>0)
        {
            addEndChar(listStr,charBase);
        }
        fclose(pFile);

        //recriando conteudo orginal
        FILE * pFileFinal = fopen(pathFile,"wb");
        listStr = listStr->listProx;
        while (listStr != NULL)
        {
            if (listStr->listProx == NULL)
            {
                flagFIM = 1;
            }
            while (ref != LENWORD)
            {
                unsigned char result = searchTable(listStr->dado.word, len ,table,lengthTable,&ref, &find, &rest, flagFIM);
                if (find == 1)
                {
                    fprintf(pFileFinal,"%c", result);
                }
            }
            ref = 0;
            listStr = listStr->listProx;
        }
        fclose(pFileFinal);

        end = clock();//parando de contar o tempo
        cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
        printf("\nConcluido!");
        printf("\nDuracao: %.2lf segundos",cpu_time_used);
    }
}