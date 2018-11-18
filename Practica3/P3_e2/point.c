#include <stdio.h>
#include <stdlib.h>
#include "types.h"
#include "point.h"

struct _Point {
    char symbol;
    int x;
    int y;
    Estado est;
    int padrex;
    int padrey;
};

Point * point_ini() {
    Point *p;
    p = (Point*) malloc(sizeof (Point));
    if (!p)
        return NULL;
    p->x = 0;
    p->y = 0;
    /*Al incializar el punto, no ha sido descubierto ni explorado, por tanto, 
     * el estado se inicializa a NADA */
    p->est = NADA;
    /*Tampoco tiene padre, por lo que las coordenadas x e y del padre se
    inicializan a -1 para indicar que no existe el padre*/
    p->padrex = -1;
    p->padrey = -1;
    return p;
}

void point_free(Point *p) {
    free(p);
}

int point_getCoordinateX(const Point *p) {
    if (!p) return -1;
    
    return p->x;
}

int point_getCoordinateY(const Point *p) {
    if (!p) return -1;

    return p->y;

}

char point_getSymbol(const Point *p) {
    char sym;
    if (!p) return ERRORCHAR;

    sym = p->symbol;
    if (sym == INPUT || sym == OUTPUT || sym == BARRIER || sym == SPACE)
        return sym;
    else return ERRORCHAR;
}

int point_getCoordxPadre(Point *p){
    if(!p) return -1;
    
    return p->padrex;
}

int point_getCoordyPadre(Point *p){
    if(!p) return -1;
    
    return p->padrey;
}

Estado point_getEstado(Point *p) {
    if (!p) return FAIL;
    return p->est;
}

Point * point_setCoordinateX(Point *p, const int coordxnew) {
    if (!p || coordxnew < 0) return NULL;

    p->x = coordxnew;
    return p;
}

Point * point_setCoordinateY(Point *p, const int coordynew) {
    if (!p || coordynew < 0) return NULL;

    p->y = coordynew;
    return p;
}

Point * point_setSymbol(Point *p, const char symnew) {
    if (!p || (symnew != INPUT && symnew != OUTPUT && symnew != BARRIER && symnew != SPACE)) return NULL;

    p->symbol = symnew;
    return p;
}

Point * point_setCoordxPadre(Point *p, const int pxnew){
    if(!p || pxnew<0) return NULL;
    
    p->padrex = pxnew;
    return p;
}

Point * point_setCoordyPadre(Point *p, const int pynew){
    if(!p || pynew<0) return NULL;
    
    p->padrey = pynew;
    return p;
}

Point * point_setEstado(Point *p, const Estado e) {
    if (!p || (e != DESCUBIERTO && e != EXPLORADO)) return NULL;

    p->est = e;
    return p;
}

Bool point_equals(const Point *p1, const Point *p2) {
    if (p1->symbol == p2->symbol && p1->x == p2->x && p1->y == p2->y && p1->est == p2->est && p1->padrex == p2->padrex && p1->padrey == p2->padrey)
        return TRUE;

    return FALSE;
}

Point * point_copy(const Point *pcopy1) {
    Point *pcopy2 = NULL;

    if (!pcopy1) return NULL;

    pcopy2 = point_ini();
    if (!pcopy2) return NULL;

    *pcopy2 = *pcopy1;
    return pcopy2;
}

int point_print(FILE *fp, const Point *p) {
    if (!p) return -1;
    return fprintf(fp, "[(%d,%d): %c]", p->x, p->y, p->symbol);
}
