#include "stack.h"

int main(int argc, char** argv) {
    int i, ret, numpila, *aux = NULL, inf;
    Stack *stotal = NULL, *spar = NULL, *simpar = NULL;
    EleStack *eleaux = NULL;

    numpila = atoi(argv[1]);
    if (numpila > MAXSTACK || numpila <= 0) {
        printf("El número de elementos a leer por teclado no es válido");
        return -1;
    }
    stotal = stack_ini();
    if (!stotal) {
        printf("Error al inicializar la pila total");
        return -1;
    }
    spar = stack_ini();
    if (!spar) {
        printf("Error al inicializar la pila de números pares");
        goto ERROR;
    }
    simpar = stack_ini();
    if (!simpar) {
        printf("Error al inicializar la pila de números impares");
        goto ERROR;
    }

    eleaux = elestack_ini();
    if (!eleaux) {
        printf("Error al inicializar el elemento");
        goto ERROR;
    }

    if (!stack_isFull(stotal)) {
        printf("Pila total (no llena, ");
        if (stack_isEmpty(stotal)) {
            printf("vacía):\n\n");
        } else printf("no vacía):\n\n");
    } else {
        printf("Pila total (llena, no vacía):\n\n");
    }

    for (i = 0; i < numpila; i++) {
        printf("Introduce un número: ");
        scanf("%d", &inf);
        eleaux = elestack_setInfo(eleaux, &inf);
        if (!eleaux) {
            printf("Error al insertar el número en el elemento");
            goto ERROR;
        }
        ret = stack_push(stotal, eleaux);
        if (ret == ERROR) {
            printf("Error al inserta un elemento en la pila total");
            goto ERROR;
        }
    }

    if (!stack_isFull(stotal)) {
        printf("\nPila total (no llena, ");
        if (stack_isEmpty(stotal)) {
            printf("vacía):\n");
        } else printf("no vacía):\n");
    } else {
        printf("\nPila total (llena, no vacía):\n");
    }

    ret = stack_print(stdout, stotal);
    if (ret <= 0) {
        printf("Error al imprimir la pila total");
        goto ERROR;
    }

    for (i = 0; i < numpila; i++) {
        eleaux = stack_pop(stotal);
        if (!eleaux) {
            printf("Error al sacar un elemento de la pila total");
            goto ERROR;
        }
        aux = elestack_getInfo(eleaux);
        if (!aux) {
            printf("Error al obtener el número entero de un elemento");
            goto ERROR;
        }
        if (*aux % 2 == 0) {
            ret = stack_push(spar, eleaux);
            if (ret == ERROR) {
                printf("Error al inserta un elemento en la pila de números pares");
                goto ERROR;
            }
        } else if (*aux % 2 == 1) {
            ret = stack_push(simpar, eleaux);
            if (ret == ERROR) {
                printf("Error al insertar un elemento en la pila de números impares");
                goto ERROR;
            }
        } else {
            printf("Error: el contenido del elemento es negativo");
            goto ERROR;
        }
    }

    printf("\nImprimiendo la pila ");
    if (!stack_isFull(spar)) {
        printf(" (no llena, ");
        if (stack_isEmpty(spar)) {
            printf("vacía) ");
        } else printf("no vacía) ");
    } else {
        printf("Pila total (llena, no vacía) ");
    }
    printf("con número pares:\n");

    ret = stack_print(stdout, spar);
    if (ret < 0) {
        printf("Error al imprimir la pila de números pares");
        goto ERROR;
    }

    printf("Imprimiendo la pila ");
    if (!stack_isFull(simpar)) {
        printf(" (no llena, ");
        if (stack_isEmpty(simpar)) {
            printf("vacía) ");
        } else printf("no vacía) ");
    } else {
        printf("Pila total (llena, no vacía) ");
    }
    printf("con número impares:\n");

    ret = stack_print(stdout, simpar);
    if (ret <= 0) {
        printf("Error al imprimir la pila de números impares");
        goto ERROR;
    }

    if (!stack_isFull(stotal)) {
        printf("\nPila total (no llena, ");
        if (stack_isEmpty(stotal)) {
            printf("vacía):");
        } else printf("no vacía):");
    } else {
        printf("\nPila total (llena, no vacía):");
    }

    goto ERROR;

ERROR:
    aux = NULL;
    if (eleaux != NULL)
        elestack_free(eleaux);
    if (simpar != NULL)
        stack_free(simpar);
    if (spar != NULL)
        stack_free(spar);
    if (stotal != NULL)
        stack_free(stotal);

    return 0;
}
