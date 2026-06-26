#include "biblioteca.h"

Curso *tabelaCursos[TAM_HASH];
Emprestimo *listaEmprestimos = NULL;
int proximoId = 1;
const char *CURSOS_PADRAO[] = {
    "Gestão", "Economia", "Contabilidade", "Geofísica", 
    "Engenharia de Petróleos", "Engenharia Electrotécnica", 
    "Engenharia Mecânica", "Engenharia Informática", 
    "Engenharia de Produção Industrial", "Engenharia Civil", "Engenharia Química"
};

void menuPrincipal() {
    int opcao;
    char nomeC[60];

    do {
        printf("\n=== BIBLIOTECA ACADEMICA ===\n");
        printf("1. Listar Cursos\n");
        printf("2. Gerir Livros de um Curso\n");
        printf("3. Emprestar Livro\n");
        printf("4. Estatisticas e Alertas\n");
        printf("0. Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        getchar();

        switch(opcao) {
            case 1:
                printf("\n--- Cursos Disponiveis ---\n");
                for(int i=0; i<TAM_HASH; i++) {
                    Curso *c = tabelaCursos[i];
                    while(c) { printf("- %s\n", c->nome); c = c->prox; }
                }
                break;
            case 2:
                printf("Nome do Curso: ");
                fgets(nomeC, 60, stdin); nomeC[strcspn(nomeC, "\n")] = 0;
                Curso *c = buscarCurso(nomeC);
                if(c) {
                    printf("\nLivros em %s:\n", c->nome);
                    listarLivros(c->avlRaiz);
                    // Aqui adicionaria sub-menu para Inserir/Remover
                } else printf("Curso nao encontrado!\n");
                break;
            case 4:
                alertaStockBaixo();
                break;
        }
    } while(opcao != 0);
}

void alertaStockBaixo() {
    printf("\n--- ALERTA DE STOCK BAIXO (<= 2) ---\n");
    for(int i=0; i<TAM_HASH; i++) {
        Curso *c = tabelaCursos[i];
        while(c) {
            // Seria necessário um percurso na AVL para verificar cada livro
            c = c->prox;
        }
    }
}

int main() {
    inicializarHash();
    carregarDados();
    menuPrincipal();
    guardarDados();
    printf("Dados guardados. Ate breve!\n");
    return 0;
}