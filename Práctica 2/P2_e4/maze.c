#include "maze.h"

struct _Maze {
    int row;
    int col;
    Point *p[MAX];
};

Maze * maze_ini() {
    Maze *maze;
    int i;
    maze = (Maze*) malloc(sizeof (Maze));
    if (!maze) return NULL;

    for (i = 0; i < MAX; i++)
        maze->p[i] = NULL;
    maze->row = 0;
    maze->col = 0;

    return maze;
}

void maze_free(Maze *maze) {
    int i;
    for (i = 0; i < maze->col * maze->row; i++)
        point_free(maze->p[i]);
    free(maze);
}

int maze_getNrows(const Maze *maze) {
    int filas;
    if (!maze) return -1;
    filas = maze->row;
    return filas;
}

int maze_getNcols(const Maze *maze) {
    int columnas;
    if (!maze) return -1;
    columnas = maze->col;
    return columnas;
}

Point * maze_getInput(const Maze *maze) {
    int i;
    char sym;
    if (!maze) return NULL;
    for (i = 0; i < maze->col * maze->row; i++) {
        sym = point_getSymbol(maze->p[i]);
        if (sym == ERRORCHAR) {
            return NULL;
        } else if (sym == 'i') {
            return maze->p[i];
        }
    }
    /* Devuelvo Null si no he encontrado el punto de entrada en ninguna de las iteraciones */
    return NULL;
}

/* Devuelve el punto de salida en un laberinto dado, o NULL si se produce algún error */
Point * maze_getOutput(const Maze *maze) {
    int i;
    char sym;
    if (!maze) return NULL;
    for (i = 0; i < maze->col * maze->row; i++) {
        sym = point_getSymbol(maze->p[i]);
        if (sym == ERRORCHAR) {
            return NULL;
        } else if (sym == 'o') {
            return maze->p[i];
        }
    }
    return NULL;
}

Point * maze_getPoint(const Maze *maze, const int x, const int y) {
    int i;
    if (x < 0 || y < 0 || !maze) return NULL;

    i = (maze->col) * y + x;
    return maze->p[i];
}

Point * maze_getNeighborPoint(const Maze *maze, const Point *p, const Move mov) {
    int x;
    int y;
    if (!maze || !p) return NULL;

    x = point_getCoordinateX(p);
    if (x < 0) return NULL;

    y = point_getCoordinateY(p);
    if (y < 0) return NULL;

    switch (mov) {
        case RIGHT:
            return maze_getPoint(maze, x + 1, y);
        case UP:
            return maze_getPoint(maze, x, y - 1);
        case LEFT:
            return maze_getPoint(maze, x - 1, y);
        case DOWN:
            return maze_getPoint(maze, x, y + 1);
        case STAY:
            return maze_getPoint(maze, x, y);
        default:
            return NULL;
    }
}

Maze* maze_setSize(Maze *maze, int nrow, int ncol) {
    int i, j;
    if (!maze || nrow <= 0 || ncol <= 0) return NULL;
    maze->row = nrow;
    maze->col = ncol;
    for (i = 0; i < nrow * ncol; i++) {
        maze->p[i] = point_ini();
        if (!maze->p[i]) {
            for (j = 0; j < i; j++) {
                point_free(maze->p[i]);
            }
            return NULL;
        }
    }
    return maze;
}

Maze * maze_addPoint(Maze *maze, const Point* p) {
    int x, y, i;

    Point *paux = NULL;
    if (!maze || !p) return NULL;

    paux = point_copy(p);
    if (!paux) return NULL;

    x = point_getCoordinateX(paux);
    if (x < 0) {
        point_free(paux);
        return NULL;
    }

    y = point_getCoordinateY(paux);
    if (y < 0) {
        point_free(paux);
        return NULL;
    }

    i = (maze->col) * y + x;

    maze->p[i] = paux;

    return maze;
}

int maze_print(FILE *f, const Maze *maze) {
    Point *temp;
    int j, k, retorno;
    char symbol;

    if (!maze) return -1;

    temp = point_ini();
    if (!temp) return -1;

    for (j = 0, retorno = 0; j < maze->row; j++) {
        for (k = 0; k < maze->col; k++) {
            temp = maze_getPoint(maze, k, j);
            if (!temp) return -1;
            symbol = point_getSymbol(temp);
            if (symbol == ERRORCHAR) {
                point_free(temp);
                return -1;
            }
            retorno += fprintf(f, "%c", symbol);
            if (retorno <= 0) {
                point_free(temp);
                return -1;
            }
        }
        retorno += fprintf(f, "\n");
    }
    point_free(temp);
    return retorno;
}