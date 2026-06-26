#include "dados.h"

int altura(No *n)
{
    if(n == NULL) return 0;
    return n->altura;
}

int max(int a, int b)
{
    return (a > b) ? a : b;
}

int fatorBalanceamento(No *n)
{
    if(n == NULL) return 0;
    return altura(n->esq) - altura(n->dir);
}

No* rotacaoDireita(No *y)
{
    No *x  = y->esq;
    No *T2 = x->dir;

    x->dir = y;
    y->esq = T2;

    y->altura = 1 + max(altura(y->esq), altura(y->dir));
    x->altura = 1 + max(altura(x->esq), altura(x->dir));

    return x;
}

No* rotacaoEsquerda(No *x)
{
    No *y  = x->dir;
    No *T2 = y->esq;

    y->esq = x;
    x->dir = T2;

    x->altura = 1 + max(altura(x->esq), altura(x->dir));
    y->altura = 1 + max(altura(y->esq), altura(y->dir));

    return y;
}

No* criarNo(char titulo[], char autor[], char disciplina[], int ano)
{
    No *novo = (No*) malloc(sizeof(No));

    strcpy(novo->titulo,     titulo);
    strcpy(novo->autor,      autor);
    strcpy(novo->disciplina, disciplina);

    novo->ano    = ano;
    novo->altura = 1;
    novo->esq    = NULL;
    novo->dir    = NULL;

    return novo;
}

No* inserir(No *raiz, char titulo[], char autor[], char disciplina[], int ano)
{
    int cmp;

    if(raiz == NULL)
        return criarNo(titulo, autor, disciplina, ano);

    cmp = strcmp(titulo, raiz->titulo);

    if(cmp < 0)
        raiz->esq = inserir(raiz->esq, titulo, autor, disciplina, ano);
    else if(cmp > 0)
        raiz->dir = inserir(raiz->dir, titulo, autor, disciplina, ano);
    else
        return raiz;

    raiz->altura = 1 + max(altura(raiz->esq), altura(raiz->dir));

    int fb = fatorBalanceamento(raiz);

    if(fb > 1  && strcmp(titulo, raiz->esq->titulo) < 0)
        return rotacaoDireita(raiz);

    if(fb < -1 && strcmp(titulo, raiz->dir->titulo) > 0)
        return rotacaoEsquerda(raiz);

    if(fb > 1  && strcmp(titulo, raiz->esq->titulo) > 0)
    {
        raiz->esq = rotacaoEsquerda(raiz->esq);
        return rotacaoDireita(raiz);
    }

    if(fb < -1 && strcmp(titulo, raiz->dir->titulo) < 0)
    {
        raiz->dir = rotacaoDireita(raiz->dir);
        return rotacaoEsquerda(raiz);
    }

    return raiz;
}

No* pesquisar(No *raiz, char titulo[])
{
    int cmp;

    if(raiz == NULL) return NULL;

    cmp = strcmp(titulo, raiz->titulo);

    if(cmp == 0) return raiz;

    if(cmp < 0)
        return pesquisar(raiz->esq, titulo);

    return pesquisar(raiz->dir, titulo);
}

No* menorValor(No *no)
{
    No *atual = no;

    while(atual != NULL && atual->esq != NULL)
        atual = atual->esq;

    return atual;
}

No* removerLivro(No *raiz, char titulo[])
{
    int cmp;
    int fb;

    if(raiz == NULL) return NULL;

    cmp = strcmp(titulo, raiz->titulo);

    if(cmp < 0)
        raiz->esq = removerLivro(raiz->esq, titulo);
    else if(cmp > 0)
        raiz->dir = removerLivro(raiz->dir, titulo);
    else
    {
        if(raiz->esq == NULL || raiz->dir == NULL)
        {
            No *temp = (raiz->esq != NULL) ? raiz->esq : raiz->dir;

            if(temp == NULL)
            {
                temp = raiz;
                raiz = NULL;
            }
            else
            {
                *raiz = *temp;
            }

            free(temp);
        }
        else
        {
            No *temp = menorValor(raiz->dir);

            strcpy(raiz->titulo,     temp->titulo);
            strcpy(raiz->autor,      temp->autor);
            strcpy(raiz->disciplina, temp->disciplina);
            raiz->ano = temp->ano;

            raiz->dir = removerLivro(raiz->dir, temp->titulo);
        }
    }

    if(raiz == NULL) return raiz;

    raiz->altura = 1 + max(altura(raiz->esq), altura(raiz->dir));

    fb = fatorBalanceamento(raiz);

    if(fb > 1  && fatorBalanceamento(raiz->esq) >= 0)
        return rotacaoDireita(raiz);

    if(fb > 1  && fatorBalanceamento(raiz->esq) < 0)
    {
        raiz->esq = rotacaoEsquerda(raiz->esq);
        return rotacaoDireita(raiz);
    }

    if(fb < -1 && fatorBalanceamento(raiz->dir) <= 0)
        return rotacaoEsquerda(raiz);

    if(fb < -1 && fatorBalanceamento(raiz->dir) > 0)
    {
        raiz->dir = rotacaoDireita(raiz->dir);
        return rotacaoEsquerda(raiz);
    }

    return raiz;
}

void listarLivros(No *raiz)
{
    if(raiz != NULL)
    {
        listarLivros(raiz->esq);

        printf("\nTitulo:     %s", raiz->titulo);
        printf("\nAutor:      %s", raiz->autor);
        printf("\nDisciplina: %s", raiz->disciplina);
        printf("\nAno:        %d\n", raiz->ano);

        listarLivros(raiz->dir);
    }
}

int contarLivros(No *raiz)
{
    if(raiz == NULL) return 0;
    return 1 + contarLivros(raiz->esq) + contarLivros(raiz->dir);
}
