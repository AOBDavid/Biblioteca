#include "biblioteca.h"

int hashCurso(char *nome) {
    unsigned long hash = 5381;
    int c;
    while ((c = *nome++)) hash = ((hash << 5) + hash) + c;
    return hash % TAM_HASH;
}

void inicializarHash() {
    for (int i = 0; i < TAM_HASH; i++) tabelaCursos[i] = NULL;
}

Curso* buscarCurso(char *nome) {
    int indice = hashCurso(nome);
    Curso *atual = tabelaCursos[indice];
    while (atual) {
        if (strcmp(atual->nome, nome) == 0) return atual;
        atual = atual->prox;
    }
    return NULL;
}

void inserirCursoNaHash(char *nome) {
    int indice = hashCurso(nome);
    Curso *novo = (Curso*)malloc(sizeof(Curso));
    strcpy(novo->nome, nome);
    novo->avlRaiz = NULL;
    novo->prox = tabelaCursos[indice];
    tabelaCursos[indice] = novo;
}