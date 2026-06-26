#include "htable.h"

void inicializarHash(HashTable *hash)
{
    int i;

    strcpy(hash->cursos[0].nomeCurso,  "Contabilidade");
    strcpy(hash->cursos[1].nomeCurso,  "Economia");
    strcpy(hash->cursos[2].nomeCurso,  "Engenharia Civil");
    strcpy(hash->cursos[3].nomeCurso,  "Engenharia de Petroleos");
    strcpy(hash->cursos[4].nomeCurso,  "Engenharia de Producao Industrial");
    strcpy(hash->cursos[5].nomeCurso,  "Engenharia Electrotecnica");
    strcpy(hash->cursos[6].nomeCurso,  "Engenharia Informatica");
    strcpy(hash->cursos[7].nomeCurso,  "Engenharia Mecanica");
    strcpy(hash->cursos[8].nomeCurso,  "Engenharia Quimica");
    strcpy(hash->cursos[9].nomeCurso,  "Geofisica");
    strcpy(hash->cursos[10].nomeCurso, "Gestao Empresarial");

    for(i = 0; i < TAM_HASH; i++)
    {
        hash->cursos[i].raiz = NULL;
    }
}

void mostrarCursos(HashTable *hash)
{
    int i;

    printf("\n===== CURSOS DISPONÍVEIS =====\n");

    for(i = 0; i < TAM_HASH; i++)
    {
        printf(
            "%2d - %s\n",
            i + 1,
            hash->cursos[i].nomeCurso
        );
    }
}

int obterIndiceCurso(int opcao)
{
    if(opcao < 1 || opcao > TAM_HASH)
    {
        return -1;
    }

    return opcao - 1;
}
