#ifndef DADOS_H
#define DADOS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ==========================
   ESTRUTURA DO NÓ AVL
   ========================== */

typedef struct No
{
    char titulo[100];
    char autor[100];
    char disciplina[100];

    int ano;
    int altura;

    struct No *esq;
    struct No *dir;

} No;

/* ==========================
   PROTÓTIPOS AVL
   ========================== */

int  altura(No *n);
int  max(int a, int b);
int  fatorBalanceamento(No *n);
No*  rotacaoDireita(No *y);
No*  rotacaoEsquerda(No *x);
No*  criarNo(char titulo[], char autor[], char disciplina[], int ano);
No*  inserir(No *raiz, char titulo[], char autor[], char disciplina[], int ano);
No*  pesquisar(No *raiz, char titulo[]);
No*  menorValor(No *no);
No*  removerLivro(No *raiz, char titulo[]);
void listarLivros(No *raiz);
int  contarLivros(No *raiz);

#endif
