
/*AUTORES:
 * LUCÍA COLMENAREJO
 * ANTONIO MARTÍN
 * ALFONSO VILLAR
 * 
 * GRUPO DE PRÁCTICAS: 2102
 */

#include <stdio.h>
#include <stdlib.h>
#include "maze.h"

Maze * maze_read(FILE *pf, Maze *pl) {
    char buff[MAX];
    int j, k, nrows, ncols;
    Point *temp;

    if (pl == NULL || pf == NULL) return NULL;
    /*creamos punto que se utiliza como buffer*/
    temp = point_ini();
    if (temp == NULL) return NULL;
    /* asignamos dimensión al laberinto */
    fgets(buff, MAX, pf);
    sscanf(buff, "%d %d", &nrows, &ncols);

    if (nrows <= 0 || ncols <= 0) return NULL;
    pl = maze_setSize(pl, nrows, ncols);
    if (pl == NULL) return NULL;
    /* leemos el fichero linea a linea */
    for (k = 0; k < nrows; k++) {
        fgets(buff, MAX, pf);
        for (j = 0; j < ncols; j++) {
            /* ajustamos los atributos del punto leído (falta añadir control de errores) */
            temp = point_setCoordinateX(temp, j);
            if (!temp) return NULL;

            temp = point_setCoordinateY(temp, k);
            if (!temp) return NULL;

            temp = point_setSymbol(temp, buff[j]);
            if (!temp) return NULL;
            /* insertamos el punto en el laberinto (falta añadir control de errores) */
            pl = maze_addPoint(pl, temp);
            if (!pl) {
                point_free(temp);
                return NULL;
            }
        }
    }    
    /* libera recursos */
    point_free(temp);
    /* no cerramos el fichero ya que lo han abierto fuera */
    return pl;
}

int main() {
    FILE *fichero = NULL;
    Maze *maze = NULL;
    int numcol, numfilas, retorno;

    fichero = fopen("maze.txt", "r");
    if (!fichero) {
        printf("Error al abrir el fichero");
        return -1;
    }

    maze = maze_ini();
    if (!maze) {
        fclose(fichero);
        printf("Error al inicializar el laberinto");
        return -1;
    }

    maze = maze_read(fichero, maze);
    if (!maze) {
        fclose(fichero);
        printf("Error al leer el laberinto");
        return -1;
    }

    numcol = maze_getNcols(maze);
    if (numcol < 0) {
        fclose(fichero);
        maze_free(maze);
        printf("Error al obtener el número de columnas");
        return -1;
    } else printf("El número de columnas del laberinto es %d\n", numcol);

    numfilas = maze_getNrows(maze);
    if (numfilas < 0) {
        fclose(fichero);
        maze_free(maze);
        printf("Error al obtener el número de filas");
        return -1;
    } else printf("El número de filas del laberinto es %d\n", numfilas);

    retorno = maze_print(stdout, maze);
    if (retorno != numfilas*numcol+numfilas) {
        fclose(fichero);
        maze_free(maze);
        printf("Error al imprimir el laberinto en el fichero");
        return -1;
    }

    fclose(fichero);
    maze_free(maze);

    return 0;
}