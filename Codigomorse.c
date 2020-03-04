// - Trabalho Estrutura de Dados 1 - Conversao de Codificacao em Morse para Texto - 
// Alunos : Fillipe Augusto de S Gomes e Kaio Nink Cardoso

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//Defining Tree Struct 
typedef struct treeW{
    char value;
    char morseCode[10];
    struct treeW *left; //root
    struct treeW *right;//root
}treeW;

treeW *buildTree(treeW *root,char Lcode[],int tam,char value,int pos);
void PreOrder(treeW *root);
void Translate(treeW **root,char morseCode[],int pos,int tam);


//goes all the way to the tree allocating nodes til it satisfies the morsecode tabs
//ps: * is used to mark nodes with no letters allocated
treeW *buildTree(treeW *root, char Lcode[], int tam, char value, int pos)
{
    if (root == NULL)
    {
        root = (treeW*) malloc(sizeof(treeW));
        root->left = NULL;
        root->right = NULL;
        root->value = '*';
    }

    if (pos < tam)
    {
        if (Lcode[pos] == '.')
        {
            root->left = buildTree(root->left,Lcode,tam,value,pos+1);
        }else{
            root->right = buildTree(root->right,Lcode,tam,value,pos+1);
        } 

    }else{
        if (root->value == '*')
        {
            root->value = value;
            Lcode[pos] = '\0';
            strcpy(root->morseCode,Lcode);
        }else{
            puts("ERROR - CANT LOAD TREE FILE");
            printf("%c\n",value);
        }   
    }
    return root;
}

// print treeW
void PreOrder(treeW *root)
{
    if (root != NULL)
    {
        if(root->value != '*')
            printf("%s %c\n", root->morseCode,root->value);
    
    PreOrder(root->left);
    PreOrder(root->right);
    }
}


//goes all the way to the letter node that needs to be translated
void Translate(treeW **root, char morseCode[], int pos, int tam)
{
    treeW *node;
    node = *root;
    if (pos < tam)
    {
        if (morseCode[pos] == '.')
        {
            Translate(&(node)->left,morseCode,pos+1,tam);
        } else if(morseCode[pos] == '-'){
            Translate(&(node)->right,morseCode,pos+1,tam);
        }

    }else
    {
        if (node->value != '*')
            printf("%c", node->value);
    }
}

int main(){

    char Lcode[10],symbol,letter;
    int count;
    treeW *root;
    
    //allocating empty root
    root = (treeW*) malloc(sizeof (treeW) );
    root->left = NULL;
    root->right = NULL;
    root->value = '*';
    FILE *arqv;
    arqv = fopen("LoadMorseTab.txt", "r");
    if (arqv == NULL)
        printf("ERROR - CANT OPEN FILE.\n");
    
    count = 0 ;
    while (fscanf(arqv, "%c", &symbol) != EOF)
    {
        if (symbol == ' ')
        {
            fscanf(arqv, "%c", &letter);
            root = buildTree(root, Lcode, count, letter,0);
            count = 0;
        }else if (symbol != '\n'){
            Lcode[count++] = symbol;
        }
    }
    fclose(arqv);

    int op, i;
    char morseCode[10], cod;
    do{
        puts("\nChoose an option: \n1- Show PreOrder\n2- Transcription\n0-Exit");
        scanf("%d", &op);
        system("clear");
        switch (op)
        {
        case 1:
            PreOrder(root);
            break;

        case 2:
            count = 0;
            arqv= fopen("InputMorseCode.txt", "r");
            if (arqv == NULL)
            {
                printf("ERROR - CAN´T OPEN FILE.\n");
            }
            while (fscanf(arqv, "%c",&cod) != EOF)
            {
                if ((cod != ' ') && (cod != '/') && (cod != '\n')){
                    morseCode[count++] = cod;
                }else if (cod == '/'){
                    printf(" ");
                }else if ((cod == ' ') || (cod == '\n')){
                    Translate(&root,morseCode,0,count);
                    count = 0;
                }
                if (cod == '\n'){
                    puts(" ");
                }
                
            }
            break;
        default:
            break;
        }
    }while (op != 0);

    return 0;
}
