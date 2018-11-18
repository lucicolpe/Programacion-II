#include "elestack.h"

struct _EleStack {
    Point* info;
};

EleStack * elestack_ini() {
    EleStack *ele;
    ele = (EleStack*) malloc(sizeof (EleStack));
    if (!ele)return NULL;

    ele->info = point_ini();
    if (!ele->info) {
        free(ele);
        return NULL;
    }
    return ele;
}

void elestack_free(EleStack *ele) {
    if (!ele) return;
    if (ele->info)
        point_free(ele->info);
    free(ele);
}

EleStack * elestack_setInfo(EleStack *ele, void *inf) {
    if (!ele || !inf) return NULL;
    ele->info = point_copy(inf);
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
    aux->info=point_copy(ele->info);
    return aux;
}

Bool elestack_equals(const EleStack *ele1, const EleStack *ele2) {
    if (!ele1 || !ele2) return FALSE;
    if (point_equals(ele1->info, ele2->info)) return TRUE;
    else return FALSE;
}

int elestack_print(FILE *f, const EleStack *ele) {
    int retorno;
    if (!ele) return -1;
    retorno=point_print(f, ele->info);
    return retorno;
}
