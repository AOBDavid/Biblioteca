#include "htable.h"

void inserirLivroHash(HashTable *hash)
{
    int  opcao;
    int  ano;
    int  idx;
    char titulo[100];
    char autor[100];
    char disciplina[100];

    mostrarCursos(hash);

    printf("\nEscolha o curso: ");
    scanf("%d", &opcao);

    idx = obterIndiceCurso(opcao);

    if(idx == -1)
    {
        printf("\nCurso invalido!\n");
        return;
    }

    getchar();

    printf("\nTitulo: ");
    fgets(titulo, 100, stdin);
    titulo[strcspn(titulo, "\n")] = '\0';

    printf("Autor: ");
    fgets(autor, 100, stdin);
    autor[strcspn(autor, "\n")] = '\0';

    printf("Disciplina: ");
    fgets(disciplina, 100, stdin);
    disciplina[strcspn(disciplina, "\n")] = '\0';

    printf("Ano: ");
    scanf("%d", &ano);

    hash->cursos[idx].raiz =
    inserir(
        hash->cursos[idx].raiz,
        titulo,
        autor,
        disciplina,
        ano
    );

    printf("\nLivro inserido com sucesso!\n");
}

void pesquisarLivroHash(HashTable *hash)
{
    int  i;
    char titulo[100];
    No   *livro;

    getchar();

    printf("\nDigite o titulo: ");
    fgets(titulo, 100, stdin);
    titulo[strcspn(titulo, "\n")] = '\0';

    for(i = 0; i < TAM_HASH; i++)
    {
        livro = pesquisar(hash->cursos[i].raiz, titulo);

        if(livro != NULL)
        {
            printf("\n===== LIVRO ENCONTRADO =====\n");
            printf("Titulo:     %s\n", livro->titulo);
            printf("Autor:      %s\n", livro->autor);
            printf("Disciplina: %s\n", livro->disciplina);
            printf("Ano:        %d\n", livro->ano);
            printf("Curso:      %s\n", hash->cursos[i].nomeCurso);
            return;
        }
    }

    printf("\nLivro nao encontrado!\n");
}

void removerLivroHash(HashTable *hash)
{
    int  i;
    char titulo[100];
    No   *livro;

    getchar();

    printf("\nTitulo do livro a remover: ");
    fgets(titulo, 100, stdin);
    titulo[strcspn(titulo, "\n")] = '\0';

    for(i = 0; i < TAM_HASH; i++)
    {
        livro = pesquisar(hash->cursos[i].raiz, titulo);

        if(livro != NULL)
        {
            hash->cursos[i].raiz =
            removerLivro(
                hash->cursos[i].raiz,
                titulo
            );

            printf("\nLivro removido com sucesso!\n");
            printf("Curso: %s\n", hash->cursos[i].nomeCurso);
            return;
        }
    }

    printf("\nLivro nao encontrado!\n");
}

void listarLivrosHash(HashTable *hash)
{
    int opcao;
    int idx;

    mostrarCursos(hash);

    printf("\nEscolha o curso: ");
    scanf("%d", &opcao);

    idx = obterIndiceCurso(opcao);

    if(idx == -1)
    {
        printf("\nCurso invalido!\n");
        return;
    }

    if(hash->cursos[idx].raiz == NULL)
    {
        printf("\nNenhum livro neste curso.\n");
        return;
    }

    printf(
        "\n===== LIVROS DE %s =====\n",
        hash->cursos[idx].nomeCurso
    );

    listarLivros(hash->cursos[idx].raiz);
}

void contarLivrosHash(HashTable *hash)
{
    int opcao;
    int idx;

    mostrarCursos(hash);

    printf("\nEscolha o curso: ");
    scanf("%d", &opcao);

    idx = obterIndiceCurso(opcao);

    if(idx == -1)
    {
        printf("\nCurso invalido!\n");
        return;
    }

    printf(
        "\nTotal de livros em %s: %d\n",
        hash->cursos[idx].nomeCurso,
        contarLivros(hash->cursos[idx].raiz)
    );
}

int totalHash(HashTable *hash)
{
    int i;
    int total = 0;

    for(i = 0; i < TAM_HASH; i++)
    {
        total += contarLivros(hash->cursos[i].raiz);
    }

    return total;
}

void mostrarTotalHash(HashTable *hash)
{
    printf(
        "\nTotal geral de livros: %d\n",
        totalHash(hash)
    );
}

int contarPorDisciplina(No *raiz, char disciplina[])
{
    int total;

    if(raiz == NULL) return 0;

    total = (strcmp(raiz->disciplina, disciplina) == 0) ? 1 : 0;

    return total
         + contarPorDisciplina(raiz->esq, disciplina)
         + contarPorDisciplina(raiz->dir, disciplina);
}

void contarDisciplinaHash(HashTable *hash)
{
    int  i;
    int  total = 0;
    char disciplina[100];

    getchar();

    printf("\nDisciplina: ");
    fgets(disciplina, 100, stdin);
    disciplina[strcspn(disciplina, "\n")] = '\0';

    for(i = 0; i < TAM_HASH; i++)
    {
        total += contarPorDisciplina(
            hash->cursos[i].raiz,
            disciplina
        );
    }

    printf("\nLivros encontrados: %d\n", total);
}
