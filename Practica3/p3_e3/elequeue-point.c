#include <stdio.h>
#include <stdlib.h>
#include "types.h"
#include "point.h"
#include "elequeue.h"

struct _EleQueue {
    Point* info;
};

EleQueue * elequeue_ini() {
    EleQueue *ele;
    ele = (EleQueue*) malloc(sizeof (EleQueue));
    if (!ele) return NULL;

    ele->info = NULL;

    return ele;
}

void elequeue_free(EleQueue *ele) {
    if (!ele) return;
    if (ele->info)
        point_free(ele->info);
    free(ele);
}

EleQueue * elequeue_setInfo(EleQueue *ele, void *inf) {
    if (!ele || !inf) return NULL;
    if(ele->info) point_free(ele->info);
    ele->info = point_copy(inf);
    return ele;
}

void * elequeue_getInfo(EleQueue *ele) {
    if (!ele) return NULL;
    return ele->info;
}

EleQueue * elequeue_copy(const EleQueue *ele) {
    EleQueue *aux = NULL;

    if (!ele) return NULL;

    aux = elequeue_ini();
    if (!aux) return NULL;

    aux->info = point_copy(ele->info);
    return aux;
}

int elequeue_cmp(const EleQueue* ele1, const EleQueue* ele2) {
    int x1, y1, x2, y2;
    Point* aux1;
    Point* aux2;

    if (!ele1 || !ele2) return ERR;

    aux1 = point_copy(ele1->info);
    if (!aux1) return ERR;

    aux2 = point_copy(ele2->info);
    if (!aux2) {
        point_free(aux1);
        return ERR;
    }

    x1 = point_getCoordinateX(aux1);
    x2 = point_getCoordinateX(aux1);
    y1 = point_getCoordinateX(aux2);
    y2 = point_getCoordinateX(aux2);

    if (x1 < x2) return MENOR;
    if (x1 > x2) return MAYOR;
    if (x1 == x2) {
        if (y1 < y2) return MENOR;
        if (y1 > y2) return MAYOR;
    }
    return IGUAL;
}

int elequeue_print(FILE *f, const EleQueue *ele) {
    int retorno;
    if (!ele) return -1;
    retorno = point_print(f, ele->info);
    return retorno;
}