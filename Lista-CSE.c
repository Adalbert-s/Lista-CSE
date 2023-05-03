//Circular Simplesmente Encadeada
//autor: Adalberto dos Santos Pinheiro
/*Objetivo: implementar uma circular simplsmente encadeada para fins didaticos*/

#include<stdio.h>
#include<stdlib.h>

typedef struct no {

    int dado;
    struct no *ant;
    struct no *prox;   

} No;

typedef struct {

    No *inicio;
    No *fim;

} ListaCSE;

//funcoes de manipulacao

void cria(ListaCSE *l);
int insere(ListaCSE *l, int dado);
int retira(ListaCSE *l, int dado);

//funcoes de visualizacao

int estaVazia(ListaCSE l);
void mostra(ListaCSE);
int verifica(ListaCSE l, int dado);


int main(){

    ListaCSE l;
    int dado, sucesso, opcao;

    cria(&l);

    //INSERINDO DESORDENADO
    sucesso = insere(&l, 400); // eu optei por nao verificar se houve sucesso na insercao
    sucesso = insere(&l, 250);
    sucesso = insere(&l, 666);
    sucesso = insere(&l, 5000);
    sucesso = insere(&l, 10);
    if(!estaVazia(l)){ //exibindo a lista
        printf("\n-------------------------------------------------\n");
        mostra(l);
    }
    opcao = 1;
    while(opcao == 1){ // remover ate o usuario nao querer mais


        printf("\n-------------------------------------------------\n");
        printf("Qual dado deseja remover? ");
        scanf("%d", &dado);
        getchar();

        verifica(l, dado);
        sucesso = retira(&l, dado); // removo o elemento solicitado pelo usuario
        if(!sucesso)
            printf("FALHA EM REMOVER: %d\n\n", dado);
        else{
            printf("Removido com sucesso\n");
            mostra(l); // exibo a lista atualizada
        }
            
            if(!estaVazia(l)){
            printf("\nDeseja remover mais algum elemento? \n1 - sim \n2 - nao\n");
            scanf("%d", &opcao);
            getchar();
            }
            else
            return 0;
    }
}

void cria(ListaCSE *l){

    l->inicio = NULL;
    l->fim = NULL;
}

int insere(ListaCSE *l, int dado){

    // alocando no na memoria e checando se deu certo
    No *aux = (No *) malloc(sizeof(No));

    if(aux == NULL)
        return 0;

    // guardando o dado e incrementando o anho da lista
    aux->dado = dado;


    // 1o caso: primeiro elemento
    if(l->inicio == NULL){

        l->inicio = aux;
        l->fim = aux;
        aux->prox = l->inicio;
        aux->ant = l->fim;

        return 1;
    }
    else{
        // 2o caso: ja ha elementos, insere no fim
        aux->ant = l->fim;          //ant do novo fim aponta para antigo fim
        aux->prox = l->inicio;      //prox do novo fim aponta pra inicio
        l->fim->prox = aux;         //prox do antigo fim aponta para novo fim
        l->fim = aux;               //l->fim aponta para novo fim
        l->inicio->ant = l->fim;    //ant do inicio aponta para novo fim

        return 1;
    }
}

int verifica(ListaCSE l, int dado){
    No *aux;

    aux = l.inicio;
    while(aux->prox != NULL){
        aux = aux->prox;
        if(dado == aux->dado){
            printf("Dado encontrado!\n");
            return 1;
        }
        if(aux->prox == NULL && aux->dado != dado)
        printf("Dado nao encontrado\n");
        return 0;          
    }
    return 0;
}

int retira(ListaCSE *l, int dado){

    No *aux ;

    if(l->inicio == NULL){
        printf("Lista vazia\n");
        return 0;
    }

    /* 1o caso: lista unitaria */
    if((dado == l->inicio->dado) && (l->inicio == l->fim)) {
        aux = l->inicio;            // aux aponta para o no que vou remover
        l->inicio = NULL;           //inicio aponta pra null
        l->fim = NULL;              // fim aponta pra null
        free(aux);                  // libero a memoria
        printf("Dado unitario removido com sucesso.\n");

        return 1;
    }

    /* 2o caso: removendo primeiro elemento */
    if(dado == l->inicio->dado ) {

        aux = l->inicio;            // aux aponta para o no que vou remover
        l->inicio = aux->prox;      //inicio aponta para o novo inicio (o segundo elemento)
        l->inicio->ant = l->fim;    // o anterior do novo inicio aponta para o fim
        l->fim->prox = l->inicio;   // o proximo do fim aponta para o novo inicio
        free(aux);                  //libero memoria
        printf("Dado removido com sucesso..\n");

        return 1;
    }

    /* 3o caso: removendo ultimo elemento */
    else if(dado == l->fim->dado) {

        aux = l->fim;               // aux aponta para o no que vou remover
        l->fim = aux->ant;          //fim aponta para o novo fim (penultimo elemento)
        l->fim->prox = l->inicio;   // o proximo do novo fim aponta para o inicio
        l->inicio->ant = l->fim;    // o anterior do inicio aponta para o novo fim
        free(aux);                  //libero a memoria
        printf("Dado removido com sucesso.\n");

        return 1;
    }

    /* 4o caso: removendo elemento no meio */
    else {
        aux = l->inicio->prox;

        while ((aux != l->fim) && (aux->dado != dado)) {
            aux = aux->prox;
        }

        if (aux == l->fim) {
            printf("Dado nao encontrado.\n");
            return 0;
        }
        aux->prox->ant = aux->ant; // o anterior do proximo a aux aponta para o elemento anterior a aux
        aux->ant->prox = aux->prox; // o proximo do anterior a aux aponta para o proximo elemento em relacao a aux
        free(aux);
        printf("Dado removido.\n");
        return 1;
    }
     free(aux);
}

int estaVazia(ListaCSE l){

    if(l.inicio == NULL)
        return 1;

    return 0;
}

void mostra(ListaCSE l){

    No *aux;

    if(l.inicio == NULL)// lista vazia, nao mostra nada
            printf("Lista vazia!\n\n");

    else { // lista possui elementos, mostra dependendo do sentido

        printf("\n-------------------------------------------------\n");
        printf("Mostrando Lista\n\n");
        // percorrendo do inicio ao fim
            aux = l.inicio;
            do{
                printf("Dado: %d\n", aux->dado);
                aux = aux->prox;
            }while(aux != l.inicio);
    }
}
