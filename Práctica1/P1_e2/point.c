#include "point.h"

struct _Point {
    char symbol;
    int x;
    int y;
};

Point * point_ini() {
    Point *p;
    p = (Point*) malloc(sizeof (Point));
    if (!p)
        return NULL;

    p->x = 0;
    p->y = 0;
    return p;
}

void point_free(Point *p) {
    free(p);
}

int point_getCoordinateX(const Point *p) {
    int coordx;
    if (!p) return -1;

    coordx = p->x;
    if (coordx >= 0)
        return coordx;
    else return -1;
}

int point_getCoordinateY(const Point *p) {
    int coordy;
    if (!p) return -1;

    coordy = p->y;
    if (coordy >= 0)
        return coordy;
    else return -1;
}

char point_getSymbol(const Point *p) {
    char sym;
    if (!p) return 'E';

    sym = p->symbol;
    if (sym == INPUT || sym == OUTPUT || sym == BARRIER || sym == SPACE)
        return sym;
    else return 'E';
}

Point * point_setCoordinateX(Point *p, const int coordxnew) {
    if (!p || coordxnew<0) return NULL;

    p->x = coordxnew;
    return p;
}

Point * point_setCoordinateY(Point *p, const int coordynew) {
    if (!p || coordynew<0) return NULL;

    p->y = coordynew;
    return p;
}

Point * point_setSymbol(Point *p, const char symnew) {
    if (!p || (symnew != INPUT && symnew != OUTPUT && symnew != BARRIER && symnew != SPACE)) return NULL;

    p->symbol = symnew;
    return p;
}

Bool point_equals(const Point *p1, const Point *p2) {
    if (p1->symbol == p2->symbol && p1->x == p2->x && p1->y == p2->y)
        return TRUE;
    else return FALSE;
}

Point * point_copy(const Point *pcopy1) {
    Point *pcopy2=NULL;

    pcopy2 = point_ini();
    if (!pcopy1 || !pcopy2) return NULL;
    *pcopy2 = *pcopy1;
    
    return pcopy2;
}

int point_print(FILE *fp, const Point *p) {
    if(!p) return -1;
    return fprintf(fp, "[(%d,%d): %c]", p->x, p->y, p->symbol);
}

