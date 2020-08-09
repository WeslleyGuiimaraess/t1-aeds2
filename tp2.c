#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct filme {
    char nome[50];
    char ano[5];
    int alugado;
    struct filme *prox;
};
typedef struct filme filme;

struct lista {
    int tam;
    filme *primeiro;
};
typedef struct lista lista;

lista * cria() {
    lista *li = (lista*)malloc(sizeof(lista));
    li->tam = 0;
    li->primeiro = NULL;
    return li;
}

void adicionaLista(lista *li, char *nome, char *ano) {
    filme *f = (filme*)malloc(sizeof(filme));
    strcpy(f->nome, nome);
    strcpy(f->ano, ano);
    f->alugado = 0;
    f->prox = li->primeiro;
    li->primeiro = f;
    li->tam++;
}

int main (void){
    FILE * fp = fopen("filmes.txt", "r");
    lista * lista_filmes = cria();
    char str[50];
    char ano[5];
    int i, opcao;
    int tamanhostr;
    if(fp == NULL)
        return 1;
    while(!feof(fp)) {
        fgets(str, 50, fp);
        // Planeta dos Macacos,2005\n\0
        tamanhostr = strlen(str);
        for (i = 0; i < tamanhostr-1; i++) {
            if (str[i] == ',') {
                str[i] = '\0';

                ano[0] = str[i+1];
                ano[1] = str[i+2];
                ano[2] = str[i+3];
                ano[3] = str[i+4];
                ano[4] = '\0';

                adicionaLista(lista_filmes, str, ano);
                break;
            }
        }
    }

    printf("Escolha Uma Opção de Busca\n"
            "1- Buscar Filmes de 2000\n"
            "2- Buscar pelo Nome\n"
            "3- Mostrar por ordem de mais alugados\n");

    scanf("%d",&opcao);
    if(opcao == 1){
        filme * filme2000;
        for(filme2000 = lista_filmes->inicio; filme2000 != NULL ; filme2000 = filme2000->prox){
            if(strcmp(filme2000->ano, "2000")==0)
                printf("O filme %s ,Lançado no ano %s ,Foi alugado %d vezes\n", filme2000->nome, filme2000->ano, filme2000->alugado);
        }
    }
    if(opcao == 2){
        filme * nome;
        setbuf(stdin, NULL);
        fgets(str, 50, stdin);
        for(nome = lista_filmes->inicio; nome != NULL ; nome = nome->prox){
            if(strcmp(nome->nome, str)==0)
                printf("O filme %s ,Lançado no ano %s ,Foi alugado %d vezes\n", nome->nome, nome->ano, nome->alugado);
        }
    }
    if(opcao == 3){
        filme * aluga;
        int cont = 0;
        int maioralug = 0;
        for(aluga = lista_filmes->inicio; aluga != NULL ; aluga = aluga->prox){
            if(aluga->alugado > maioralug)
                maioralug = aluga->alugado;
        }
        while(cont < lista_filmes->tam){
            for(aluga = lista_filmes->inicio; aluga != NULL ; aluga = aluga->prox){
                if(aluga->ano == maioralug){
                    printf("O filme %s ,Lançado no ano %s ,Foi alugado %d vezes\n", aluga->nome, aluga->ano, aluga->alugado);
                    cont++;
                }
            }
            maioralug --;
        }
    }
    return 0;        
}
