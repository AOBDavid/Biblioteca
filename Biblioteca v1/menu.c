#include "htable.h"

void menuPrincipal(HashTable *hash)
{
    int opcao;

    do
    {
        printf("\n");
        printf("=====================================\n");
        printf(" SISTEMA DE GESTAO DE BIBLIOTECA AVL\n");
        printf("=====================================\n");
        printf("1 - Inserir Livro\n");
        printf("2 - Pesquisar Livro\n");
        printf("3 - Remover Livro\n");
        printf("4 - Listar Livros de um Curso\n");
        printf("5 - Contar Livros de um Curso\n");
        printf("6 - Contar Livros por Disciplina\n");
        printf("7 - Mostrar Total da Biblioteca\n");
        printf("8 - Listar Cursos\n");
        printf("0 - Sair\n");
        printf("\nOpcao: ");
        scanf("%d", &opcao);

        switch(opcao)
        {
            case 1: inserirLivroHash(hash);     break;
            case 2: pesquisarLivroHash(hash);   break;
            case 3: removerLivroHash(hash);     break;
            case 4: listarLivrosHash(hash);     break;
            case 5: contarLivrosHash(hash);     break;
            case 6: contarDisciplinaHash(hash); break;
            case 7: mostrarTotalHash(hash);     break;
            case 8: mostrarCursos(hash);        break;

            case 0:
                printf("\nPrograma encerrado.\n");
                break;

            default:
                printf("\nOpcao invalida!\n");
        }

    } while(opcao != 0);
}
