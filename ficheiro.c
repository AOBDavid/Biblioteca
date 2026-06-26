#include "biblioteca.h"

void percorrerEGravar(Livro *raiz, FILE *f) {
    if (raiz) {
        percorrerEGravar(raiz->esq, f);
        fprintf(f, "ID:%03d|Nome:%s|Autor:%s|Ano:%d|Qtd:%d|Procurado:%d\n", 
                raiz->id, raiz->nome, raiz->autor, raiz->anoLancamento, raiz->quantidade, raiz->vezesProcurado);
        percorrerEGravar(raiz->dir, f);
    }
}

void guardarDados() {
    FILE *f = fopen("dados.txt", "w");
    if (!f) return;

    for (int i = 0; i < TAM_HASH; i++) {
        Curso *c = tabelaCursos[i];
        while (c) {
            fprintf(f, "CURSO:%s\n", c->nome);
            percorrerEGravar(c->avlRaiz, f);
            c = c->prox;
        }
    }
    fclose(f);
}

void carregarDados() {
    FILE *f = fopen("dados.txt", "r");
    if (!f) {
        // Criar cursos padrão se não existir ficheiro
        for (int i = 0; i < NUM_CURSOS; i++) {
            inserirCursoNaHash((char*)CURSOS_PADRAO[i]);
        }
        return;
    }

    char linha[512];
    Curso *cursoAtual = NULL;
    while (fgets(linha, sizeof(linha), f)) {
        linha[strcspn(linha, "\n")] = 0;
        if (strncmp(linha, "CURSO:", 6) == 0) {
            char *nomeC = linha + 6;
            if (!(cursoAtual = buscarCurso(nomeC))) {
                inserirCursoNaHash(nomeC);
                cursoAtual = buscarCurso(nomeC);
            }
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