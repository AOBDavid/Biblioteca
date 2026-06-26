#include "biblioteca.h"

int altura(Livro *n) { return n ? n->altura : 0; }
int max(int a, int b) { return (a > b) ? a : b; }

int fatorBalanceamento(Livro *n) {
    return n ? altura(n->esq) - altura(n->dir) : 0;
}

Livro* criarLivro(int id, char *nome, char *autor, int ano, int qtd, int procurado) {
    Livro *n = (Livro*)malloc(sizeof(Livro));
    n->id = id;
    strcpy(n->nome, nome);
    strcpy(n->autor, autor);
    n->anoLancamento = ano;
    n->quantidade = qtd;
    n->vezesProcurado = procurado;
    n->altura = 1;
    n->esq = n->dir = NULL;
    return n;
}

Livro* rotarDireita(Livro *y) {
    Livro *x = y->esq;
    Livro *T2 = x->dir;
    x->dir = y;
    y->esq = T2;
    y->altura = max(altura(y->esq), altura(y->dir)) + 1;
    x->altura = max(altura(x->esq), altura(x->dir)) + 1;
    return x;
}

Livro* rotarEsquerda(Livro *x) {
    Livro *y = x->dir;
    Livro *T2 = y->esq;
    y->esq = x;
    x->dir = T2;
    x->altura = max(altura(x->esq), altura(x->dir)) + 1;
    y->altura = max(altura(y->esq), altura(y->dir)) + 1;
    return y;
}

Livro* inserirLivro(Livro *raiz, int id, char *nome, char *autor, int ano, int qtd, int procurado) {
    if (!raiz) return criarLivro(id, nome, autor, ano, qtd, procurado);

    if (id < raiz->id) raiz->esq = inserirLivro(raiz->esq, id, nome, autor, ano, qtd, procurado);
    else if (id > raiz->id) raiz->dir = inserirLivro(raiz->dir, id, nome, autor, ano, qtd, procurado);
    else return raiz;

    raiz->altura = 1 + max(altura(raiz->esq), altura(raiz->dir));
    int fb = fatorBalanceamento(raiz);

    if (fb > 1 && id < raiz->esq->id) return rotarDireita(raiz);
    if (fb < -1 && id > raiz->dir->id) return rotarEsquerda(raiz);
    if (fb > 1 && id > raiz->esq->id) {
        raiz->esq = rotarEsquerda(raiz->esq);
        return rotarDireita(raiz);
    }
    if (fb < -1 && id < raiz->dir->id) {
        raiz->dir = rotarDireita(raiz->dir);
        return rotarEsquerda(raiz);
    }
    return raiz;
}

Livro* buscarLivro(Livro *raiz, int id) {
    if (!raiz || raiz->id == id) {
        if (raiz) raiz->vezesProcurado++;
        return raiz;
    }
    if (id < raiz->id) return buscarLivro(raiz->esq, id);
    return buscarLivro(raiz->dir, id);
}

void listarLivros(Livro *raiz) {
    if (raiz) {
        listarLivros(raiz->esq);
        printf("[%03d] %-30s | Stock: %d | Autor: %s\n", raiz->id, raiz->nome, raiz->quantidade, raiz->autor);
        listarLivros(raiz->dir);
    }
}

void liberarAVL(Livro *raiz) {
    if (raiz) {
        liberarAVL(raiz->esq);
        liberarAVL(raiz->dir);
        free(raiz);
    }
}