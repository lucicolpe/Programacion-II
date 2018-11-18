
/*AUTORES:
 * LUCÍA COLMENAREJO
 * ANTONIO MARTÍN
 * ALFONSO VILLAR
 * 
 * GRUPO DE PRÁCTICAS: 2102
 */

#include <stdio.h>
#include <stdlib.h>
#include "point.h"

int main() {

    Point *punto1 = NULL, *punto2 = NULL;
    int retorno_int;
    char retorno_char;

    punto1 = point_ini();
    if (!punto1) {
        printf("Error al crear el primer punto");
        return -1;
    }

    punto2 = point_ini();
    if (!punto2) {
        printf("Error al crear el segundo punto");
        point_free(punto1);
        return -1;
    }

    punto1 = point_setCoordinateX(punto1, 1);
    if (!punto1) {
        printf("Error al modificar la componente x del primer punto");
        point_free(punto2);
        return -1;
    }
    punto1 = point_setCoordinateY(punto1, 2);
    if (!punto1) {
        printf("Error al modificar la componente y del primer punto");
        point_free(punto2);
        return -1;
    }
    punto1 = point_setSymbol(punto1, BARRIER);
    if (!punto1) {
        printf("Error al modificar el símbolo del primer punto");
        point_free(punto2);
        return -1;
    }

    punto2 = point_setCoordinateX(punto2, 3);
    if (!punto1) {
        printf("Error al modificar la componente x del segundo punto");
        point_free(punto1);
        return -1;
    }
    punto2 = point_setCoordinateY(punto2, 4);
    if (!punto1) {
        printf("Error al modificar la componente y del segundo punto");
        point_free(punto1);
        return -1;
    }
    punto2 = point_setSymbol(punto2, OUTPUT);
    if (!punto1) {
        printf("Error al modificar el símbolo del segundo punto");
        point_free(punto1);
        return -1;
    }

    retorno_int = point_print(stdout, punto1);
    if (retorno_int <= 0) {
        printf("Error al imprimir el primer punto por pantalla");
        point_free(punto1);
        point_free(punto2);
    }

    retorno_int = point_print(stdout, punto2);
    if (retorno_int <= 0) {
        printf("Error al imprimir el segundo punto por pantalla");
        point_free(punto1);
        point_free(punto2);
    }

    printf("\nSon iguales? ");
    if (point_equals(punto1, punto2)) {
        printf("Si");
    } else printf("No");

    retorno_char = point_getSymbol(punto1);
    if (retorno_char == ERRORCHAR) {
        printf("Error al obtener el símbolo del primer punto");
        point_free(punto1);
        point_free(punto2);
        return -1;
    } else printf("\nEl símbolo del primer punto es: %c", retorno_char);

    retorno_int = point_getCoordinateX(punto2);
    if (retorno_int < 0) {
        printf("Error al obtener la componente x del segundo punto");
        point_free(punto1);
        point_free(punto2);
        return -1;
    } else printf("\nLa coordenada x del segundo punto es: %d\n", retorno_int);

    punto2 = point_copy(punto1);
    if (!punto1 || !punto2) {
        printf("Error al copiar los puntos");
        point_free(punto1);
        point_free(punto2);
        return -1;
    }

    retorno_int = point_print(stdout, punto1);
    if (retorno_int <= 0) {
        printf("Error al imprimir el primer punto por pantalla");
        point_free(punto1);
        point_free(punto2);
    }

    retorno_int = point_print(stdout, punto2);
    if (retorno_int <= 0) {
        printf("Error al imprimir el segundo punto por pantalla");
        point_free(punto1);
        point_free(punto2);
    }

    printf("\nSon iguales? ");
    if (point_equals(punto1, punto2)) {
        printf("Si\n");
    } else printf("No\n");

    point_free(punto1);
    point_free(punto2);

    return 0;
}

