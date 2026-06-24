#ifndef HASH_H
#define HASH_H

#define TAM_HASH 11

typedef struct NoAVL NoAVL;

typedef struct
{
    char nomeCurso[50];
    NoAVL *raiz;
    int proximoLivro;
} Curso;

typedef struct
{
    Curso cursos[TAM_HASH];
} HashTable;

void inicializarHash(HashTable *hash);

int obterIndiceCurso(int opcao);

void mostrarCursos();

#endif