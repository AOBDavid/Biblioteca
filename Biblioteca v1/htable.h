#ifndef HTABLE_H
#define HTABLE_H

#include "dados.h"

/* ==========================
   CONSTANTE
   ========================== */

#define TAM_HASH 11

/* ==========================
   ESTRUTURA CURSO
   ========================== */

typedef struct
{
    char nomeCurso[50];
    No  *raiz;

} Curso;

/* ==========================
   ESTRUTURA HASH TABLE
   ========================== */

typedef struct
{
    Curso cursos[TAM_HASH];

} HashTable;

/* ==========================
   PROTOTIPOS HASH TABLE
   ========================== */

void inicializarHash(HashTable *hash);
void mostrarCursos(HashTable *hash);
int  obterIndiceCurso(int opcao);

/* ==========================
   PROTOTIPOS BIBLIOTECA
   ========================== */

void inserirLivroHash(HashTable *hash);
void pesquisarLivroHash(HashTable *hash);
void removerLivroHash(HashTable *hash);
void listarLivrosHash(HashTable *hash);
void contarLivrosHash(HashTable *hash);
int  totalHash(HashTable *hash);
void mostrarTotalHash(HashTable *hash);
int  contarPorDisciplina(No *raiz, char disciplina[]);
void contarDisciplinaHash(HashTable *hash);
void menuPrincipal(HashTable *hash);

#endif
