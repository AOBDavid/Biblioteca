#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// --- ESTRUTURAS ---

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

typedef struct Curso {
    char nome[60];
    Livro *avlRaiz;
    struct Curso *prox;
} Curso;

#define TAM_HASH 13
Curso *tabelaCursos[TAM_HASH];
int proximoId = 1;

const char *CURSOS_PADRAO[] = {
    "Gestão", "Economia", "Contabilidade", "Geofísica", 
    "Engenharia de Petróleos", "Engenharia Electrotécnica", 
    "Engenharia Mecânica", "Engenharia Informática", 
    "Engenharia de Produção Industrial", "Engenharia Civil", "Engenharia Química"
};

// --- FUNÇÕES AUXILIARES AVL ---

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

Livro* balancear(Livro *n) {
    n->altura = 1 + max(altura(n->esq), altura(n->dir));
    int fb = fatorBalanceamento(n);
    if (fb > 1 && fatorBalanceamento(n->esq) >= 0) return rotarDireita(n);
    if (fb > 1 && fatorBalanceamento(n->esq) < 0) {
        n->esq = rotarEsquerda(n->esq);
        return rotarDireita(n);
    }
    if (fb < -1 && fatorBalanceamento(n->dir) <= 0) return rotarEsquerda(n);
    if (fb < -1 && fatorBalanceamento(n->dir) > 0) {
        n->dir = rotarDireita(n->dir);
        return rotarEsquerda(n);
    }
    return n;
}

Livro* inserirLivro(Livro *raiz, int id, char *nome, char *autor, int ano, int qtd, int procurado) {
    if (!raiz) return criarLivro(id, nome, autor, ano, qtd, procurado);
    if (id < raiz->id) raiz->esq = inserirLivro(raiz->esq, id, nome, autor, ano, qtd, procurado);
    else if (id > raiz->id) raiz->dir = inserirLivro(raiz->dir, id, nome, autor, ano, qtd, procurado);
    else return raiz;
    return balancear(raiz);
}

// --- HASH TABLE ---

int hashCurso(char *nome) {
    unsigned long hash = 5381;
    int c;
    while ((c = *nome++)) hash = ((hash << 5) + hash) + c;
    return hash % TAM_HASH;
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
    if (buscarCurso(nome)) return;
    int indice = hashCurso(nome);
    Curso *novo = (Curso*)malloc(sizeof(Curso));
    strcpy(novo->nome, nome);
    novo->avlRaiz = NULL;
    novo->prox = tabelaCursos[indice];
    tabelaCursos[indice] = novo;
}

// --- PERSISTÊNCIA ---

void gravarRecursivo(Livro *raiz, FILE *f) {
    if (raiz) {
        gravarRecursivo(raiz->esq, f);
        fprintf(f, "ID:%03d|Nome:%s|Autor:%s|Ano:%d|Qtd:%d|Procurado:%d\n", 
                raiz->id, raiz->nome, raiz->autor, raiz->anoLancamento, raiz->quantidade, raiz->vezesProcurado);
        gravarRecursivo(raiz->dir, f);
    }
}

void guardarDados() {
    FILE *f = fopen("dados.txt", "w");
    if (!f) return;
    for (int i = 0; i < TAM_HASH; i++) {
        Curso *c = tabelaCursos[i];
        while (c) {
            fprintf(f, "CURSO:%s\n", c->nome);
            gravarRecursivo(c->avlRaiz, f);
            c = c->prox;
        }
    }
    fclose(f);
}

void carregarDados() {
    FILE *f = fopen("dados.txt", "r");
    if (!f) {
        for (int i = 0; i < 11; i++) inserirCursoNaHash((char*)CURSOS_PADRAO[i]);
        return;
    }
    char linha[512];
    Curso *cursoAtual = NULL;
    while (fgets(linha, sizeof(linha), f)) {
        linha[strcspn(linha, "\n")] = 0;
        if (strncmp(linha, "CURSO:", 6) == 0) {
            char *nomeC = linha + 6;
            inserirCursoNaHash(nomeC);
            cursoAtual = buscarCurso(nomeC);
        } else if (strncmp(linha, "ID:", 3) == 0) {
            int id, ano, qtd, proc;
            char nomeL[150], autor[100];
            sscanf(linha, "ID:%d|Nome:%[^|]|Autor:%[^|]|Ano:%d|Qtd:%d|Procurado:%d", 
                   &id, nomeL, autor, &ano, &qtd, &proc);
            cursoAtual->avlRaiz = inserirLivro(cursoAtual->avlRaiz, id, nomeL, autor, ano, qtd, proc);
            if (id >= proximoId) proximoId = id + 1;
        }
    }
    fclose(f);
}

// --- INTERFACE ---

void listarInOrder(Livro *raiz) {
    if (raiz) {
        listarInOrder(raiz->esq);
        printf("[%03d] %-30s | Stock: %d | Autor: %s\n", raiz->id, raiz->nome, raiz->quantidade, raiz->autor);
        listarInOrder(raiz->dir);
    }
}

void menuPrincipal() {
    int opcao;
    char nomeC[60];
    do {
        printf("\n--- SISTEMA DE BIBLIOTECA ACADEMICA ---\n");
        printf("1. Listar Cursos e Livros\n");
        printf("2. Adicionar Livro\n");
        printf("3. Pesquisar Livro por ID\n");
        printf("0. Sair e Guardar\n");
        printf("Escolha: ");
        scanf("%d", &opcao); getchar();

        if (opcao == 1) {
            for (int i = 0; i < TAM_HASH; i++) {
                Curso *c = tabelaCursos[i];
                while (c) {
                    printf("\n>>> CURSO: %s\n", c->nome);
                    if (!c->avlRaiz) printf("    (Sem livros registados)\n");
                    else listarInOrder(c->avlRaiz);
                    c = c->prox;
                }
            }
        } else if (opcao == 2) {
            printf("Nome do Curso: ");
            fgets(nomeC, 60, stdin); nomeC[strcspn(nomeC, "\n")] = 0;
            Curso *c = buscarCurso(nomeC);
            if (c) {
                char nL[150], aut[100]; int an, qt;
                printf("Nome do Livro: "); fgets(nL, 150, stdin); nL[strcspn(nL, "\n")] = 0;
                printf("Autor: "); fgets(aut, 100, stdin); aut[strcspn(aut, "\n")] = 0;
                printf("Ano: "); scanf("%d", &an);
                printf("Quantidade: "); scanf("%d", &qt);
                c->avlRaiz = inserirLivro(c->avlRaiz, proximoId++, nL, aut, an, qt, 0);
                printf("Livro inserido com ID %d\n", proximoId-1);
            } else printf("Erro: Curso inexistente.\n");
        }
    } while (opcao != 0);
}

int main() {
    for (int i = 0; i < TAM_HASH; i++) tabelaCursos[i] = NULL;
    carregarDados();
    menuPrincipal();
    guardarDados();
    return 0;
}