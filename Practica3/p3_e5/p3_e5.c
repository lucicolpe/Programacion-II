#include <stdio.h>
#include <stdlib.h>
#include "types.h"
#include "point.h"
#include "maze.h"
#include "elelist.h"
#include "list.h"
#include "solver_mazes.h"

int main(int argc, char** argv) {
    int ret;
    List *lista = NULL;
    Move strategies [][4] = {
        {RIGHT, LEFT, UP, DOWN},
        {RIGHT, LEFT, DOWN, UP},
        {DOWN, RIGHT, LEFT, UP},
        {DOWN, LEFT, UP, RIGHT},
        {UP, DOWN, RIGHT, LEFT},
        {UP, RIGHT, LEFT, DOWN},
        {LEFT, DOWN, RIGHT, UP},
        {LEFT, UP, DOWN, RIGHT}
    };

    lista = list_ini();
    if(!lista){
        printf("Error al inicializar la lista");
        return -1;
    }
    
    mazesolver_run(argv[1], strategies, 8, lista);
    
    printf("Lista con %d elementos", list_size(lista));
    ret = list_print(stdout, lista);
    if(ret <= 0){
        printf("Error al imprimir la pila");
        return -1;
    }    
    list_free(lista);
    return 0;
}

