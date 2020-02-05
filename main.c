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
    scanf("%i",&option);
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
        short nodeLenght = 0;
        int strLenghtCurrent = 0;
        NodeList * nodeList = startNodeList();
        while (fread(&c,1,1,pFile)>0)
        {
            //montando a *List
            NodeList * element = searchByWord(nodeList,c);//procurando elemento repetido
            if (element == NULL)//caso nao encontre elemento
            {
                addNodeEndChar(nodeList,c);
                nodeLenght++;
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
            //criando arquivo compacto com final .cp
            strcat(pathFile,".cp");
            FILE * pFileFinal = fopen(pathFile,"wb");
            fprintf(pFileFinal,"%c", 0);//alocando espaco para guardar o lenghtLast
            fwrite((const void*) & nodeLenght,sizeof(short),1,pFileFinal);//Gravando lenghtTable
            NodeList * listAux = nodeList->listProx;
            while (listAux != NULL)
            {
                fprintf(pFileFinal,"%c", listAux->node.dado.word);
                fwrite((const void*) & listAux->node.dado.qtd,sizeof(int),1,pFileFinal);
                listAux = listAux->listProx;
            }
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
            
            // showNodes(node);
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
            
            //---------------Gravando Arquivo--------------
            //Formato lenghtLast + lenghtTable + table + arquivoCompactado
            /*fprintf(pFileFinal,"%c", len);//alocando espaco para guardar o lenghtLast
            fwrite((const void*) & lenght,sizeof(int),1,pFileFinal);//Gravando lenghtTable
            int i;
            for ( i = 0; i < lenght; i++) //Gravando table
            {
                fprintf(pFileFinal,"%c", table[i].word);
                fwrite((const void*) & table[i].code,LENCODE/8,1,pFileFinal);
                fprintf(pFileFinal,"%c", table[i].lenght);
            }*/
            do//Gravando Arquivo Compactado
            {
                strRef = buildCharTable(table,strRef, &rest, &charRead,&len,&strLenghtCurrent);                
                fprintf(pFileFinal,"%c", charRead);
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
        char lenghtLast = 0; //tamanho da palavra final
        short lengthTable = 0;
        fread(&lenghtLast,1,1,pFile);//ler lengthLast
        fread(&lengthTable,sizeof(short),1,pFile); //ler lengthTable
        //ler tabela de codigos
        NodeList * nodeList = startNodeList();
        for (int i = 0; i < lengthTable; i++)
        {
            Dado dado;
            fread(&dado.word,1,1,pFile);
            fread(&dado.qtd,sizeof(int),1,pFile);
            addNodeEndDado(nodeList,dado);
        }
        // showNodeList(*nodeList);
        printf("\n---------------------\n");
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
        pathFile[lengthPath-3] = '\0';//montando o nome do arquivo original
        
        //Criando variaveis
        Table rest;
        rest.code=0;
        rest.lenght=0;
        int pivo = 1;
        int find = FALSE;

        //passando o conteudo compacto para uma string
        while (fread(&charBase,1,1,pFile)>0)
        {
            addEndChar(listStr,charBase);
        }
        fclose(pFile);
        //recriando conteudo orginal
        FILE * pFileFinal = fopen(pathFile,"wb");
        Node * node = &nodeList->listProx->node;
        // showNodes(node);
        listStr = listStr->listProx;
        while (listStr != NULL)
        {
            pivo = 1;
            if (listStr->listProx == NULL)
            {
                pivo = LENWORD - (lenghtLast-1);
            }
            while (pivo <= LENWORD)
            {
                unsigned char result = searchNode(listStr->dado.word,node, lenghtLast, &pivo, &find,&rest);
                if (find == TRUE)
                {
                    // printf("\nResult: %c",result);
                    fprintf(pFileFinal,"%c", result);
                }
                delay(0.5);
            }
            // printf("\n\nSAIU\n");
            listStr = listStr->listProx;
        }
        fclose(pFileFinal);

        end = clock();//parando de contar o tempo
        cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
        printf("\nConcluido!");
        printf("\nDuracao: %.2lf segundos",cpu_time_used);
    }
}