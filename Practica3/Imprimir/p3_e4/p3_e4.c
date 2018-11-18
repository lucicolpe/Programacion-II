#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"
#include "elelist.h"
#include "list.h"
#define MAX 100

int main(int argc, char** argv) {
    List *lista, *orden;
    EleList *ele;
    FILE *f;
    int i, inf, ret, tam;
    char buff[MAX];
    char *token = NULL;

    f = fopen(argv[1], "r");
    if (!f) {
        printf("Error al abrir el fichero");
        return -1;
    }

    lista = list_ini();
    if (!lista) {
        printf("Error al inicializar la lista");
        fclose(f);
        return -1;
    }

    fgets(buff, MAX, f);
    token = strtok(buff, " ");
    while (token) {
        inf = atoi(token);
        if (inf < 0) {
            printf("Error: el número no puede ser negativo");
            fclose(f);
            list_free(lista);
            return -1;
        }

        ele = elelist_ini();
        if (!ele) {
            printf("Error al inicializar el elemento");
            fclose(f);
            list_free(lista);
            return -1;
        }

        ret = elelist_setInfo(ele, &inf);
        if (ret == ERROR) {
            printf("Error al insertar el entero en el elemento");
            fclose(f);
            list_free(lista);
            elelist_free(ele);
            return -1;
        }

        if (inf % 2 == 0) {
            ret = list_insertFirst(lista, ele);
            if (ret == ERROR) {
                printf("Error al insertar el elemento en la lista");
                fclose(f);
                list_free(lista);
                elelist_free(ele);
                return -1;
            }
        }

        if (inf % 2 == 1) {
            ret = list_insertLast(lista, ele);
            if (ret == ERROR) {
                printf("Error al insertar el elemento en la lista");
                fclose(f);
                list_free(lista);
                elelist_free(ele);
                return -1;
            }
        }
        printf("\nLista con %d elementos:\n", list_size(lista));
        ret = list_print(stdout, lista);
        if (ret <= 0) {
            printf("Error al imprimir la lista");
            fclose(f);
            list_free(lista);
            return -1;
        }
        elelist_free(ele);
        token = strtok(NULL, " ");
    }

    orden = list_ini();
    if (!orden) {
        printf("Error al inicializar la lista ordenada");
        fclose(f);
        list_free(lista);
        return -1;
    }

    tam = list_size(lista);
    for (i = 0; i < tam / 2; i++) {
        ele = list_extractFirst(lista);
        if (!ele) {
            printf("Error al extraer el elemento de la lista");
            fclose(f);
            list_free(lista);
            list_free(orden);
            return -1;
        }

        printf("\nElemento extraido: ");
        ret = elelist_print(stdout, ele);
        if (ret <= 0) {
            printf("Error al imprimir el elemento extraído");
            fclose(f);
            list_free(lista);
            list_free(orden);
            return -1;
        }

        printf("\n\nLista con %d elementos:\n", list_size(lista));
        ret = list_print(stdout, lista);
        if (ret <= 0) {
            printf("Error al imprimir la lista después de la extracción");
            fclose(f);
            list_free(lista);
            list_free(orden);
            return -1;
        }

        ret = list_insertInOrder(orden, ele);
        if (ret == ERROR) {
            printf("Error al insertar el elemento en la lista ordenada");
            fclose(f);
            list_free(lista);
            list_free(orden);
            elelist_free(ele);
            return -1;
        }
        printf("\nLista ordenada con %d elementos:\n", list_size(orden));
        ret = list_print(stdout, orden);
        if (ret <= 0) {
            printf("Error al imprimir la lista ordenada");
            fclose(f);
            list_free(lista);
            list_free(orden);
            return -1;
        }
        elelist_free(ele);
    }

    while (!list_isEmpty(lista)) {
        ele = list_extractLast(lista);
        if (!ele) {
            printf("Error al extraer el elemento de la lista");
            fclose(f);
            list_free(lista);
            list_free(orden);
            return -1;
        }

        printf("\nElemento extraido: ");
        ret = elelist_print(stdout, ele);
        if (ret <= 0) {
            printf("Error al imprimir el elemento extraído");
            fclose(f);
            list_free(lista);
            list_free(orden);
            return -1;
        }

        if (!list_isEmpty(lista)) {
            printf("\n\nLista con %d elementos:\n", list_size(lista));
            ret = list_print(stdout, lista);
            if (ret <= 0) {
                printf("Error al imprimir la lista después de la extracción");
                fclose(f);
                list_free(lista);
                list_free(orden);
                return -1;
            }
        } else printf("\n");
        
        ret = list_insertInOrder(orden, ele);
        if (ret == ERROR) {
            printf("Error al insertar el elemento en la lista ordenada");
            fclose(f);
            list_free(lista);
            list_free(orden);
            elelist_free(ele);
            return -1;
        }

        printf("\nLista ordenada con %d elementos:\n", list_size(orden));
        ret = list_print(stdout, orden);
        if (ret <= 0) {
            printf("Error al imprimir la lista ordenada");
            fclose(f);
            list_free(lista);
            list_free(orden);
            return -1;
        }
        elelist_free(ele);
    }

    fclose(f);
    list_free(lista);
    list_free(orden);
    return 0;
}

