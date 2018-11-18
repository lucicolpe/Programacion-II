
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

Posible recorrer(Maze *m, Point *o, Stack* rec) {
    int i, x, y, ret;
    char sym;
    Stack *s = NULL;
    EleStack *ele = NULL;
    Point *p = NULL, *aux = NULL;

    if (!m || !o || !rec) return FALLO;

    sym = point_getSymbol(o);
    if (sym != INPUT) return FALLO;

    s = stack_ini();
    if (!s) return FALLO;

    ele = elestack_ini();
    if (!ele) goto ERROR;
/*Se etiqueta al punto de entrada como descubierto. No se hace control de 
 *errores porque el punto no es nulo y DESCUBIERTO es un estado válido*/
    o = point_setEstado(o, DESCUBIERTO);

    ele = elestack_setInfo(ele, o);
    if (!ele) goto ERROR;

    stack_push(s, ele);
    if (!s) goto ERROR;

    while (!stack_isEmpty(s)) {
        ele = stack_pop(s);
        if (!ele) goto ERROR;

        p = elestack_getInfo(ele);
        if (!p) goto ERROR;
/*Se obtienen las coordenadas del punto porque serán las coordenadas padre de los puntos vecinos*/
        x = point_getCoordinateX(p);
        y = point_getCoordinateY(p);
/*Miramos si el estado del punto es DESCUBIERTO. Si no, significa que ya ha sido 
 *EXPLORADO y por tanto, no debe entrar en el bucle */
        if (point_getEstado(p) == DESCUBIERTO) {
            /*Etiquetamos al punto como EXPLORADO y cogemos los puntos vecinos*/
            p = point_setEstado(p, EXPLORADO);
            for (i = RIGHT; i < STAY; i++) {
                aux = maze_getNeighborPoint(m, p, i);                
                /*El punto vecino puede no existir si p está en un borde.*/
                if (aux != NULL) {
                    ret = point_getEstado(aux);
                    /*Se obtiene el estado del punto vecino. Si este ya había 
                     *sido DESCUBIERTO  o EXPLORADO no entra en el bucle*/
                    if (ret == NADA) {
                        /*Se etiqueta al punto como DESCUBIERTO y se ponen las
                         *coordenadas de p como el padre del punto vecino*/
                        aux = point_setEstado(aux, DESCUBIERTO);
                        aux = point_setCoordxPadre(aux, x);
                        aux = point_setCoordyPadre(aux, y);
                        sym = point_getSymbol(aux);
                        /*Se obtiene el símbolo del punto. Si este es OUTPUT, se ha encontrado la salida*/
                        if (sym == OUTPUT) {
                        /*Se libera la pila de puntos descubiertos y en la pila
                         * rec se guardan los puntos del camino encontrado*/
                            stack_free(s);                            
                            ele = elestack_setInfo(ele, aux);
                            ret = stack_push(rec, ele);
                            if(ret == ERROR) goto ERROR;
                            /*En este bucle infinito, se cogen las coordenadas del padre,se obtiene el punto con dichas 
                             *coordenadas y se mete en la pila. Y de este punto, se cogen las coordenadas del padre y 
                             *así sucesivamente hasta llegar al punto de entrada, cuyo padre tiene coordenadas (-1,-1)*/
                            while (1) {
                                x = point_getCoordxPadre(aux);
                                if (x < 0) break;
                                y = point_getCoordyPadre(aux);
                                aux = maze_getPoint(m, x, y);
                                if(!aux) goto ERROR;
                                ele = elestack_setInfo(ele, aux);
                                ret = stack_push(rec, ele);
                                if(ret == ERROR) goto ERROR;
                            }
                            /*Al terminar el bucle, se liberan recursos y devuelve POSIBLE*/
                            elestack_free(ele);
                            return POSIBLE;
                        }
                        /*Si el símbolo es un espacio, se mete en la pila. En otro caso, no se hace nada*/
                        if (sym == SPACE) {
                            ele = elestack_setInfo(ele, aux);
                            if (!ele) goto ERROR;

                            ret = stack_push(s, ele);
                            if (ret == ERROR) goto ERROR;

                        }
                    }
                }
            }
        }
    }
/*Si ha salido del bucle while, significa que no ha encontrado el punto OUTPUT.
*Como no ha encontrado ningún camino, se liberan recursos y devuelve NO_POSIBLE*/
    elestack_free(ele);
    stack_free(s);
    return NO_POSIBLE;
/*Si ha habido algún error durante la ejecución, se liberan recursos y devuelve FALLO*/
ERROR:
    if (ele)
        elestack_free(ele);
    if (s)
        stack_free(s);
    return FALLO;
}

int main(int argc, char** argv) {
    int ret;
    FILE *f = NULL;
    Maze *maze = NULL;
    Point *pinput = NULL;
    Stack* recorrido = NULL;    

    f = fopen(argv[1], "r");
    if (!f) {
        printf("Error al abrir el fichero");
        return -1;
    }

    maze = maze_ini();
    if (!maze) {
        printf("Error al inicializar el laberinto");
        fclose(f);
        return -1;
    }

    recorrido = stack_ini();
    if (!recorrido) {
        printf("Error al inicializar la pila");
        fclose(f);
        maze_free(maze);
        return -1;
    }

    maze = maze_read(f, maze);
    if (!maze) {
        printf("Error al leer el laberinto");
        fclose(f);
        stack_free(recorrido);
        return -1;
    }

    pinput = maze_getInput(maze);
    if (!pinput) {
        printf("Error al obtener el punto de entrada al laberinto");
        fclose(f);
        maze_free(maze);
        stack_free(recorrido);
        return -1;
    }

    ret = recorrer(maze, pinput, recorrido);

    switch (ret) {
        case FALLO:
            printf("Ha ocurrido algún error\n");
            break;

        case POSIBLE:
            printf("Es posible encontrar un camino\n");
            printf("Un posible camino es:\n");
            stack_print(stdout, recorrido);
            break;

        case NO_POSIBLE:
            printf("No es posible encontrar un camino\n");
            break;
    }

    fclose(f);
    maze_free(maze);
    stack_free(recorrido);

    return 0;
}
