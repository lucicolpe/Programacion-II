#include "elestack.h"

struct _EleStack {
    int* info;
};

EleStack * elestack_ini() {
    EleStack *ele;
    ele = (EleStack*) malloc(sizeof (EleStack));
    if (!ele)return NULL;
    ele->info = (int*)malloc(sizeof(int));
    return ele;
}

void elestack_free(EleStack *ele) {
    if (!ele) return;
    if(ele->info!=NULL) free(ele->info);
    free(ele);
}

EleStack * elestack_setInfo(EleStack *ele, void *inf) {
    if (!ele || !inf) return NULL;
    ele->info = (int*)inf;
    return ele;
}

void * elestack_getInfo(EleStack *ele) {
    if (!ele) return NULL;
    return ele->info;
}

EleStack * elestack_copy(const EleStack *ele) {
    EleStack *aux = NULL;

    aux = elestack_ini();
    if (!ele || !aux)return NULL;
    *(aux->info) = *(ele->info);
    return aux;
}

Bool elestack_equals(const EleStack *ele1, const EleStack *ele2) {
    if (!ele1 || !ele2) return FALSE;
    if (*(ele1->info) == *(ele2->info)) return TRUE;
    else return FALSE;
}

int elestack_print(FILE *f, const EleStack *ele) {

    if (!ele) return -1;
    return fprintf(f, "[%d]", *ele->info);
}
