#include <stdio.h>
#include <stdlib.h>
#include "types.h"
#include "elelist.h"

struct _EleList {
    int* info;
};

EleList* elelist_ini() {
    EleList* ele;

    ele = (EleList*) malloc(sizeof (EleList));
    if (!ele) return NULL;

    ele->info = (int*) malloc(sizeof (int));
    if (!ele->info) {
        free(ele);
        return NULL;
    }
    return ele;
}

void elelist_free(EleList * ele) {
    if (!ele) return;
    if (ele->info != NULL) free(ele->info);
    free(ele);
}

Status elelist_setInfo(EleList * e, void* p) {
    if (!e || !p) return ERROR;
    *(e->info) = *((int*) p);
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

    *(aux->info) = *(src->info);
    return aux;
}

int elelist_cmp(const EleList * ele1, const EleList * ele2) {
    int inf1, inf2;
    if (!ele1 || !ele2 || !ele1->info || !ele2->info) return ERR;

    inf1 = *(ele1->info);
    inf2 = *(ele2->info);

    if (inf1 < inf2) return MENOR;
    if (inf1 > inf2) return MAYOR;
    return IGUAL;
}

int elelist_print(FILE* pf, const EleList * ele) {
    if (!ele) return -1;
    return fprintf(pf, "[%d]", *ele->info);
}