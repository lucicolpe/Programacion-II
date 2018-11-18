#include <stdio.h>
#include <stdlib.h>
#include "types.h"
#include "point.h"
#include "maze.h"
#include "elequeue.h"
#include "queue.h"
#include "elestack.h"
#include "stack.h"
#include "solver_mazes.h"

Status maze_read(FILE *pf, Maze *pl) {
    char buff[MAX];
    int j, k, nrows, ncols;
    Point *temp;

    if (pl == NULL || pf == NULL) return ERROR;
    /*creamos punto que se utiliza como buffer*/
    temp = point_ini();
    if (temp == NULL) return ERROR;
    /* asignamos dimensión al laberinto */
    fgets(buff, MAX, pf);
    sscanf(buff, "%d %d", &nrows, &ncols);

    if (nrows <= 0 || ncols <= 0) return ERROR;
    pl = maze_setSize(pl, nrows, ncols);
    if (pl == NULL) return ERROR;
    /* leemos el fichero linea a linea */
    for (k = 0; k < nrows; k++) {
        fgets(buff, MAX, pf);
        for (j = 0; j < ncols; j++) {
            /* ajustamos los atributos del punto leído (falta añadir control de errores) */
            temp = point_setCoordinateX(temp, j);
            if (!temp) return ERROR;

            temp = point_setCoordinateY(temp, k);
            if (!temp) return ERROR;

            temp = point_setSymbol(temp, buff[j]);
            if (!temp) return ERROR;
            /* insertamos el punto en el laberinto (falta añadir control de errores) */
            pl = maze_addPoint(pl, temp);
            if (!pl) {
                point_free(temp);
                return ERROR;
            }
        }
    }
    /* libera recursos */
    point_free(temp);
    /* no cerramos el fichero ya que lo han abierto fuera */
    return OK;
}

int mazesolver_stack(const char* maze_file, const Move strat[4]) {
    int i, x, y, ret, mov;
    char sym;
    FILE *f;
    Maze *m;
    Stack *s = NULL, *rec = NULL;
    EleStack *ele = NULL, *auxele = NULL;
    Point *o = NULL, *p = NULL, *aux = NULL;

    if (!maze_file) return -1;

    f = fopen(maze_file, "r");
    if (!f) return -1;

    m = maze_ini();
    if (!m) {
        fclose(f);
        return -1;
    }

    ret = maze_read(f, m);
    if (ret == ERROR) goto ERROR;

    o = maze_getInput(m);
    if (!o) goto ERROR;

    s = stack_ini();
    if (!s) return FALLO;

    ele = elestack_ini();
    if (!ele) goto ERROR;

    o = point_setEstado(o, DESCUBIERTO);

    ele = elestack_setInfo(ele, o);
    if (!ele) goto ERROR;

    stack_push(s, ele);
    if (!s) goto ERROR;

    elestack_free(ele);

    while (!stack_isEmpty(s)) {
        ele = stack_pop(s);
        if (!ele) goto ERROR;

        p = elestack_getInfo(ele);
        if (!p) goto ERROR;

        x = point_getCoordinateX(p);
        y = point_getCoordinateY(p);

        if (point_getEstado(p) == DESCUBIERTO) {
            p = point_setEstado(p, EXPLORADO);
            for (i = 0; i < 4; i++) {
                aux = maze_getNeighborPoint(m, p, strat[i]);
                if (aux != NULL) {
                    ret = point_getEstado(aux);
                    if (ret == NADA) {
                        aux = point_setEstado(aux, DESCUBIERTO);
                        aux = point_setCoordxPadre(aux, x);
                        aux = point_setCoordyPadre(aux, y);
                        sym = point_getSymbol(aux);
                        if (sym == OUTPUT) {
                            stack_free(s);
                            rec = stack_ini();
                            if (!rec) goto ERROR;
                            ele = elestack_setInfo(ele, aux);
                            ret = stack_push(rec, ele);
                            if (ret == ERROR) goto ERROR;
                            elestack_free(ele);
                            mov = 0;
                            while (1) {
                                x = point_getCoordxPadre(aux);
                                if (x < 0) break;
                                y = point_getCoordyPadre(aux);
                                aux = maze_getPoint(m, x, y);
                                if (!aux) goto ERROR;
                                ele = elestack_ini();
                                if (!ele) goto ERROR;
                                ele = elestack_setInfo(ele, aux);
                                ret = stack_push(rec, ele);
                                if (ret == ERROR) goto ERROR;
                                elestack_free(ele);
                                mov++;
                            }
                            fclose(f);
                            maze_free(m);
                            stack_free(rec);
                            return mov;
                        }

                        if (sym == SPACE) {
                            auxele = elestack_ini();
                            if (!auxele) goto ERROR;

                            auxele = elestack_setInfo(auxele, aux);
                            if (!auxele) goto ERROR;

                            ret = stack_push(s, auxele);
                            if (ret == ERROR) goto ERROR;
                            elestack_free(auxele);
                        }
                    }
                }
            }
        }
        elestack_free(ele);
    }

    fclose(f);
    maze_free(m);
    stack_free(s);
    return 0;

ERROR:
    if (m) maze_free(m);
    if (auxele) elestack_free(auxele);
    if (ele) elestack_free(ele);
    if (s) stack_free(s);
    if (rec) stack_free(rec);
    fclose(f);
    return -1;
}

int mazesolver_queue(const char* maze_file, const Move strat[4]) {
    int i, x, y, ret;
    char sym;
    FILE *f = NULL;
    Maze *m = NULL;
    Queue *s = NULL, *rec = NULL;
    EleQueue *ele = NULL, *auxele = NULL;
    Point *o = NULL, *p = NULL, *aux = NULL;

    if (!maze_file) return FALLO;

    f = fopen(maze_file, "r");
    if (!f) return -1;

    m = maze_ini();
    if (!m) goto ERROR;

    ret = maze_read(f, m);
    if (ret == ERROR) goto ERROR;

    o = maze_getInput(m);
    if (!o) goto ERROR;

    s = queue_ini();
    if (!s) goto ERROR;

    ele = elequeue_ini();
    if (!ele) goto ERROR;

    o = point_setEstado(o, DESCUBIERTO);

    ele = elequeue_setInfo(ele, o);
    if (!ele) goto ERROR;

    queue_insert(s, ele);
    if (!s) goto ERROR;

    elequeue_free(ele);

    while (!queue_isEmpty(s)) {
        ele = queue_extract(s);
        if (!ele) goto ERROR;

        p = elequeue_getInfo(ele);
        if (!p) goto ERROR;

        x = point_getCoordinateX(p);
        y = point_getCoordinateY(p);

        if (point_getEstado(p) == DESCUBIERTO) {
            p = point_setEstado(p, EXPLORADO);
            for (i = 0; i < 4; i++) {
                aux = maze_getNeighborPoint(m, p, strat[i]);
                if (aux != NULL) {
                    ret = point_getEstado(aux);
                    if (ret == NADA) {
                        aux = point_setEstado(aux, DESCUBIERTO);
                        aux = point_setCoordxPadre(aux, x);
                        aux = point_setCoordyPadre(aux, y);
                        sym = point_getSymbol(aux);
                        if (sym == OUTPUT) {
                            queue_free(s);
                            ele = elequeue_setInfo(ele, aux);
                            rec = queue_ini();
                            if (!rec) goto ERROR;
                            ret = queue_insert(rec, ele);
                            if (ret == ERROR) goto ERROR;
                            elequeue_free(ele);
                            while (1) {
                                x = point_getCoordxPadre(aux);
                                if (x < 0) break;
                                y = point_getCoordyPadre(aux);
                                aux = maze_getPoint(m, x, y);
                                if (!aux) goto ERROR;
                                ele = elequeue_ini(ele);
                                if (!ele) goto ERROR;
                                ele = elequeue_setInfo(ele, aux);
                                ret = queue_insert(rec, ele);
                                if (ret == ERROR) goto ERROR;
                                elequeue_free(ele);
                            }
                            fclose(f);
                            maze_free(m);
                            ret = queue_size(rec);
                            queue_free(rec);
                            return ret - 1;
                        }
                        if (sym == SPACE) {
                            auxele = elequeue_ini();
                            if (!auxele) goto ERROR;

                            auxele = elequeue_setInfo(auxele, aux);
                            if (!auxele) goto ERROR;

                            ret = queue_insert(s, auxele);
                            if (ret == ERROR) goto ERROR;
                            elequeue_free(auxele);
                        }
                    }
                }
            }
        }
        elequeue_free(ele);
    }

    fclose(f);
    maze_free(m);
    queue_free(s);
    return 0;

ERROR:
    if (m) maze_free(m);
    if (auxele) elequeue_free(auxele);
    if (ele) elequeue_free(ele);
    if (s) queue_free(s);
    if (rec) queue_free(rec);
    fclose(f);
    return -1;
}

void mazesolver_run(const char* maze_file, Move strat[][4], const int num_strategies) {
    int i, ret;

    for (i = 0; i < num_strategies; i++) {
        if (!strat[i]) return;
        printf("ESTRATEGIA %d%d%d%d:\n", strat[i][0], strat[i][1], strat[i][2], strat[i][3]);
        ret = mazesolver_stack(maze_file, strat[i]);
        printf("PILA: ");
        if (ret < 0) return;
        if (ret == 0) printf("SALIDA NO ENCONTRADA\n");
        if (ret > 0) printf("SALIDA ENCONTRADA CON %d MOVIMIENTOS\n", ret);

        ret = mazesolver_queue(maze_file, strat[i]);
        printf("COLA: ");
        if (ret < 0) return;
        if (ret == 0) printf("SALIDA NO ENCONTRADA\n\n");
        if (ret > 0) printf("SALIDA ENCONTRADA CON %d MOVIMIENTOS\n\n", ret);
    }

    return;
}

int main(int argc, char** argv) {
    Move strategies[][4] = {
        {RIGHT, LEFT, UP, DOWN},
        {DOWN, RIGHT, LEFT, UP},
        {UP, DOWN, RIGHT, LEFT},
        {LEFT, UP, DOWN, RIGHT}
    };

    mazesolver_run(argv[1], strategies, 4);

    return 0;
}