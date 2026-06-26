#ifndef BIBLIOTECA_H
#define BIBLIOTECA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Estrutura do Livro (Nó da AVL)
typedef struct Livro {
    int id;
    char nome[150];
    char autor[100];
    int anoLancamento;
    int quantidade;
    int vezesProcurado;
    int altura;
    struct Livro *esq;
    struct Livro *dir;
} Livro;

// Estrutura de Empréstimo (Lista Ligada)
typedef struct Emprestimo {
    int idLivro;
    char nomeCurso[60];
    char estudante[100];
    char data[20];
    struct Emprestimo *prox;
} Emprestimo;

// Estrutura do Curso (Nó da Hash Table)
typedef struct Curso {
    char nome[60];
    Livro *avlRaiz;
    struct Curso *prox;
} Curso;

#define TAM_HASH 13
extern Curso *tabelaCursos[TAM_HASH];
extern Emprestimo *listaEmprestimos;
extern int proximoId;

// Cursos Padrão
extern const char *CURSOS_PADRAO[];
#define NUM_CURSOS 11

// Protótipos: Hash
int hashCurso(char *nome);
Curso* buscarCurso(char *nome);
void inicializarHash();

// Protótipos: AVL
Livro* inserirLivro(Livro *raiz, int id, char *nome, char *autor, int ano, int qtd, int procurado);
Livro* buscarLivro(Livro *raiz, int id);
Livro* buscarLivroPorNome(Livro *raiz, char *nome);
Livro* removerLivro(Livro *raiz, int id);
void listarLivros(Livro *raiz);
void liberarAVL(Livro *raiz);

// Protótipos: Empréstimos
void emprestarLivro();
void devolverLivro();
void listarEmprestimos();

// Protótipos: Ficheiro
void carregarDados();
void guardarDados();

// Protótipos: Estatísticas e Menu
void rankingLivros();
void alertaStockBaixo();
void menuPrincipal();

#endif