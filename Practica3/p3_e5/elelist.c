#include <stdio.h>
#include <stdlib.h>
#include "types.h"
#include "point.h"
#include "maze.h"
#include "solution.h"
#include "elelist.h"

struct _EleList {
    Solution* info;
};

EleList* elelist_ini() {
    EleList* ele;

    ele = (EleList*) malloc(sizeof (EleList));
    if (!ele) return NULL;

    ele->info = NULL;
    return ele;
}

void elelist_free(EleList * ele) {
    if (!ele) return;
    if (ele->info != NULL) solution_free(ele->info);
    free(ele);
}

Status elelist_setInfo(EleList * e, void* p) {
    if (!e || !p) return ERROR;
    if(!e->info) solution_free(e->info);
    e->info = solution_copy(p);
    if (!e->info) return ERROR;
    return OK;
}

void* elelist_getInfo(EleList * e) {
    if (!e) return NULL;
    return e->info;
}

EleList* elelist_copy(const EleList * src) {
    EleList *aux = NULL;
    if (!src) return NULL;

    aux = elelist_ini();
    if (!aux) return NULL;

    aux->info = solution_copy(src->info);
    return aux;
}

int elelist_cmp(const EleList * ele1, const EleList * ele2) {
    int inf1, inf2;
    if (!ele1 || !ele2) return ERR;

    inf1 = solution_getNumero(ele1->info);
    inf2 = solution_getNumero(ele2->info);

    if (inf1 < inf2) return MENOR;
    if (inf1 > inf2) return MAYOR;
    return IGUAL;
}

int elelist_print(FILE* pf, const EleList * ele) {
    if (!ele) return -1;
    return solution_print(pf, ele->info);
}