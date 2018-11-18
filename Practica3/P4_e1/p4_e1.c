#include <stdio.h>
#include <stdlib.h>
#include "types.h"
#include "elelist.h"
#include "list.h"
#include "eletree.h"
#include "tree.h"

int main(int argc, char** argv) {
    int num, ret;
    EleTree *ele = NULL;
    Tree *tree = NULL;
    FILE *f = NULL;

    f = fopen(argv[1], "r");
    if (!f) {
        printf("Error al abrir el fichero");
        return -1;
    }

    tree = tree_ini();
    if (!tree) {
        printf("Error al inicializar el árbol");
        fclose(f);
        return -1;
    }

    while (!feof(f)) {
        fscanf(f, "%d\n", &num);

        ele = eletree_ini();
        if (!ele) {
            printf("Error al inicializar el elemento");
            fclose(f);
            tree_free(tree);
            return -1;
        }

        ret = eletree_setInfo(ele, &num);
        if (ret == ERROR) {
            printf("Error al insertar el número en el elemento");
            fclose(f);
            tree_free(tree);
            eletree_free(ele);
            return -1;
        }

        ret = tree_insert(tree, ele);
        if (ret == ERROR) {
            printf("Error al insertar el elemento en el árbol");
            fclose(f);
            tree_free(tree);
            eletree_free(ele);
            return -1;
        }
        eletree_free(ele);
    }
    
    ret = tree_numNodes(tree);
    printf("Numero de nodos: %d\n", ret);

    ret = tree_depth(tree);
    printf("Profundidad: %d\n", ret);

    printf("Introduzca un número:\n");
    scanf("%d", &num);
    printf("Número introducido: %d\n", num);

    ele = eletree_ini();
    if (!ele) {
        printf("Error al inicializar el elemento");
        fclose(f);
        tree_free(tree);
        return -1;
    }

    ret = eletree_setInfo(ele, &num);
    if (ret == ERROR) {
        printf("Error al insertar el número en el elemento");
        fclose(f);
        tree_free(tree);
        eletree_free(ele);
        return -1;
    }

    ret = tree_findEleTree(tree, ele);
    if (ret == TRUE) printf("El dato %d se encuentra dentro del árbol", num);
    else printf("El dato %d no se encuentra dentro del árbol", num);

    eletree_free(ele);
    tree_free(tree);
    fclose(f);
    return 0;
}

