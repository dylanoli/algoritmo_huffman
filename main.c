#include<stdio.h>
#include<stdlib.h>
#include<string.h>
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
    // fgets(pathFile, 200,stdin);
    FILE * pFile = fopen(pathFile,"rb");
    if (pFile == NULL)
    {
        fclose(pFile);
        printf("Arquivo nao encontrado !");
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
            printf("%c   ",c);
        }
        printf("\n");
        showList(*listStr);
        fclose(pFile);
        if (list->listProx != NULL)//verifica se o arquivo está vazio
        {
            quicksort(list, 1, list->id-1);//organiza a lista encadeada
            while (list->listProx != NULL)
            {
                Node * node = transformNode(list->listProx->dado);
                removeStart(list);
                addNodeStart(nodeList, *node);
            }
            while (nodeList->listProx != NULL && nodeList->listProx->listProx != NULL)
            {
                NodeList * nodeListAux = startNodeList();
                while (nodeList->listProx != NULL && nodeList->listProx->listProx != NULL)
                {
                    Node * nodeRight = &nodeList->listAnte->node;
                    removeNodeLast(nodeList);
                    Node * nodeLeft = &nodeList->listAnte->node;
                    removeNodeLast(nodeList);
                    Node * node = startNodeWithElements(*nodeRight,*nodeLeft);       
                    addNodeStart(nodeListAux,*node);
                }
                if (nodeList->listProx != NULL)
                {
                    addNodeStart(nodeListAux,(nodeList->listProx->node));
                    removeNodeLast(nodeList);
                }
                while (nodeListAux->listProx != NULL)
                {
                    addNodeStart(nodeList,nodeListAux->listAnte->node);
                    removeNodeLast(nodeListAux);  
                }
            }
            Node * node = &nodeList->listProx->node;
            int lenght = lengthNodes(node);
            char ** table = (char **)calloc(lenght,sizeof(char*));
            int i;
            for (i = 0; i < lenght; i++)
            {
                table[i] = (char *)calloc(2,sizeof(char));
            }
            buildTable(table,lenght,node);
            showTable(table,lenght);
            // FILE * pFileFinal = fopen("Final.cp","wb");
            // fclose(pFileFinal);
        }
        else
        {
            printf("O arquivo esta vazio!");
        }
    }  
}

void decompress()
{

}