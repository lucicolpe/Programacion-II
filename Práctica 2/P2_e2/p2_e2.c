
#include "stack.h"
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

int main(int argc, char** argv) {
    Stack *s = NULL;
    Maze *maze = NULL;
    FILE *f = NULL;
    EleStack *aux = NULL;
    int nfilas, ncols, i, j, retorno;

    f = fopen(argv[1], "r");
    if (!f) {
        printf("Error al abrir el fichero");
        return -1;
    }

    aux=elestack_ini();
    if(!aux){
        fclose(f);
        printf("Error al inicializar el elemento");
        return -1;
    }
    
    s = stack_ini();
    if (!s) {
        fclose(f);
        elestack_free(aux);
        printf("Error al inicializar la pila");
        return -1;
    }

    maze = maze_ini();
    if (!maze) {
        fclose(f);
        elestack_free(aux);
        stack_free(s);
        printf("Error al inicializar el laberinto");
        return -1;
    }

    maze = maze_read(f, maze);
    if (!maze) {
        fclose(f);
        elestack_free(aux);
        stack_free(s);
        printf("Error al leer el laberinto");
        return -1;
    }

    nfilas = maze_getNrows(maze);
    if (nfilas <= 0) {
        fclose(f);
        elestack_free(aux);
        stack_free(s);
        maze_free(maze);
        printf("Error al obtener el número de filas del laberinto");
        return -1;
    }

    ncols = maze_getNcols(maze);
    if (ncols <= 0) {
        fclose(f);
        elestack_free(aux);
        stack_free(s);
        maze_free(maze);
        printf("Error al obtener el número de filas del laberinto");
        return -1;
    }

    for (i = 0; i < nfilas; i++) {
        for (j = 0; j < ncols; j++) {
            aux = elestack_setInfo(aux, maze_getPoint(maze, j, i));
            if (!aux) {
                stack_free(s);
                maze_free(maze);
                fclose(f);
                printf("Error al obtener el punto (%d, %d)", j, i);
                return -1;
            }
            retorno = stack_push(s, aux);
            if (retorno == ERROR) {
                elestack_free(aux);
                maze_free(maze);
                fclose(f);
                printf("Error al obtener el punto (%d, %d)", j, i);
                return -1;
            }
        }
    }

    retorno = stack_print(stdout, s);
    if (retorno <= 0) {
        elestack_free(aux);
        stack_free(s);
        maze_free(maze);
        fclose(f);
        printf("Error al imprimir el laberinto");
        return -1;
    }

    elestack_free(aux);
    stack_free(s);
    maze_free(maze);
    fclose(f);
    
    return 0;
}
