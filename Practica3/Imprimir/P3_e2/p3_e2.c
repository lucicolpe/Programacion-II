#include <stdio.h>
#include <stdlib.h>
#include "types.h"
#include "elequeue.h"
#include "queue.h"
#include "point.h"
#include "maze.h"

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

Posible recorrer(Maze *m, Point *o, Queue* rec) {
    int i, x, y, ret;
    char sym;
    Queue* s = NULL;
    EleQueue *ele = NULL, *auxele = NULL;
    Point *p = NULL, *aux = NULL;

    if (!m || !o || !rec) return FALLO;

    sym = point_getSymbol(o);
    if (sym != INPUT) return FALLO;

    s = queue_ini();
    if (!s) return FALLO;

    ele = elequeue_ini();
    if (!ele) goto ERROR;

    o = point_setEstado(o, DESCUBIERTO);

    ele = elequeue_setInfo(ele, o);
    if (!ele) goto ERROR;

    ret = queue_insert(s, ele);
    if (ret == ERROR) goto ERROR;

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
            for (i = RIGHT; i < STAY; i++) {
                aux = maze_getNeighborPoint(m, p, i);
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
                            ret = queue_insert(rec, ele);
                            if (ret == ERROR) goto ERROR;
                            elequeue_free(ele);
                            while (1) {
                                x = point_getCoordxPadre(aux);
                                if (x < 0) break;
                                y = point_getCoordyPadre(aux);
                                aux = maze_getPoint(m, x, y);
                                if (!aux) goto ERROR;
                                ele = elequeue_ini();
                                if (!ele) goto ERROR;
                                ele = elequeue_setInfo(ele, aux);
                                ret = queue_insert(rec, ele);
                                if (ret == ERROR) goto ERROR;
                                elequeue_free(ele);
                            }
                            return POSIBLE;
                        }
                        
                        if (sym == SPACE) {
                            auxele = elequeue_ini();
                            if(!auxele) goto ERROR;
                            
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
    queue_free(s);
    return NO_POSIBLE;

ERROR:
    if (auxele)
        elequeue_free(auxele);
    if (ele)
        elequeue_free(ele);
    if (s)
        queue_free(s);
    return FALLO;
}

int main(int argc, char** argv) {
    int i, ret, tam;
    FILE *f = NULL;
    Maze *maze = NULL;
    Point *pinput = NULL;
    EleQueue *ele1 = NULL, *ele2 = NULL;
    Queue *recorrido = NULL, *aux1 = NULL, *aux2 = NULL;

    f = fopen(argv[1], "r");
    if (!f) {
        printf("Error al abrir el fichero");
        return -1;
    }

    maze = maze_ini();
    if (!maze) {
        printf("Error al inicializar el laberinto");
        goto ERROR;
    }

    recorrido = queue_ini();
    if (!recorrido) {
        printf("Error al inicializar la cola");
        goto ERROR;
    }

    ret = maze_read(f, maze);
    if (ret == ERROR) {
        printf("Error al leer el laberinto");
        goto ERROR;
    }

    pinput = maze_getInput(maze);
    if (!pinput) {
        printf("Error al obtener el punto de entrada al laberinto");
        goto ERROR;
    }

    ret = recorrer(maze, pinput, recorrido);
    switch (ret) {
        case FALLO:
            printf("Ha ocurrido algún error\n");
            break;

        case POSIBLE:
            printf("Es posible encontrar un camino\n");
            tam = queue_size(recorrido);
            if (tam < 2) {
                printf("Error al encontrar un posible camino");
                fclose(f);
                maze_free(maze);
                queue_free(recorrido);
            }
            aux1 = queue_ini();
            if (!aux1) {
                printf("Error al inicializar la cola auxiliar 1");
                fclose(f);
                maze_free(maze);
                queue_free(recorrido);
                return -1;
            }
            aux2 = queue_ini();
            if (!aux2) {
                printf("Error al inicializar la cola auxiliar 2");
                goto ERROR;
            }
            for (i = 0; i < tam; i++) {
                ele1 = queue_extract(recorrido);
                while (!queue_isEmpty(aux1)) {
                    ele2 = queue_extract(aux1);
                    if(!ele2){
                        printf("Error al extraer un elemento de la cola auxiliar 1");
                        goto ERROR;
                    }
                    ret = queue_insert(aux2, ele2);
                    if(ret == ERROR){
                        printf("Error al insertar un elemento en la cola auxiliar 2");
                        goto ERROR;
                    }
                    elequeue_free(ele2);
                }
                ret = queue_insert(aux1, ele1);
                if(ret == ERROR){
                    printf("Error al insertar un elemento en la cola auxiliar 1");
                    goto ERROR;
                }
                while (!queue_isEmpty(aux2)) {
                    ele2 = queue_extract(aux2);
                    if(!ele2){
                        printf("Error al extraer un elemento de la cola auxiliar 2");
                        goto ERROR;
                    }
                    ret = queue_insert(aux1, ele2);
                    if(ret == ERROR){
                    printf("Error al insertar un elemento en la cola auxiliar 1");
                    goto ERROR;
                }
                    elequeue_free(ele2);
                }
                elequeue_free(ele1);
            }
            printf("Un posible camino es:\n");
            queue_print(stdout, aux1);
            break;

        case NO_POSIBLE:
            printf("No es posible encontrar un camino\n");
            break;
    }

    fclose(f);
    maze_free(maze);
    queue_free(recorrido);
    queue_free(aux1);
    queue_free(aux2);
    return 0;

ERROR:
    if (recorrido) queue_free(recorrido);
    if (aux1) queue_free(aux1);
    if(aux2) queue_free(aux2);
    if(ele1) elequeue_free(ele1);
    if(ele2) elequeue_free(ele2);
    if(maze) maze_free(maze);
    fclose(f);   
    return -1;
}
