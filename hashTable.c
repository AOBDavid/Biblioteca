#include <stdio.h>
#include <string.h>
#include "hashTable.h"

void inicializarHash(HashTable *hash)
{
    strcpy(hash->cursos[0].nomeCurso, "Contabilidade");
    strcpy(hash->cursos[1].nomeCurso, "Economia");
    strcpy(hash->cursos[2].nomeCurso, "Engenharia Civil");
    strcpy(hash->cursos[3].nomeCurso, "Engenharia de Petroleos");
    strcpy(hash->cursos[4].nomeCurso, "Engenharia de Producao Industrial");
    strcpy(hash->cursos[5].nomeCurso, "Engenharia Electrotecnica");
    strcpy(hash->cursos[6].nomeCurso, "Engenharia Informatica");
    strcpy(hash->cursos[7].nomeCurso, "Engenharia Mecanica");
    strcpy(hash->cursos[8].nomeCurso, "Engenharia Quimica");
    strcpy(hash->cursos[9].nomeCurso, "Geofisica");
    strcpy(hash->cursos[10].nomeCurso, "Gestao Empresarial");

    for (int i = 0; i < TAM_HASH; i++)
    {
        hash->cursos[i].raiz = NULL;
        hash->cursos[i].proximoLivro = 1;
    }
}

int obterIndiceCurso(int opcao)
{
    if (opcao < 1 || opcao > TAM_HASH)
        return -1;

    return opcao - 1;
}

void mostrarCursos()
{
    printf("\n===== CURSOS =====\n");

    printf("1. Contabilidade\n");
    printf("2. Economia\n");
    printf("3. Engenharia Civil\n");
    printf("4. Engenharia de Petroleos\n");
    printf("5. Engenharia de Producao Industrial\n");
    printf("6. Engenharia Electrotecnica\n");
    printf("7. Engenharia Informatica\n");
    printf("8. Engenharia Mecanica\n");
    printf("9. Engenharia Quimica\n");
    printf("10. Geofisica\n");
    printf("11. Gestao Empresarial\n");
}