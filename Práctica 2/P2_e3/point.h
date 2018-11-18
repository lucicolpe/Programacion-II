#ifndef POINT_H
#define	POINT_H


#include <stdio.h>
#include <stdlib.h>

#include "types.h"

#define ERRORCHAR 'E'
#define INPUT 'i'
#define OUTPUT 'o'
#define BARRIER '+'
#define SPACE ' '
typedef struct _Point Point;
/* Inicializa un punto, reservando memoria y devolviendo el punto inicializado si lo ha hecho correctamente o NULL
si no */
Point * point_ini();
/* Libera la memoria dinámica reservada para un punto*/
void point_free(Point * );
/* Devuelve la coordenada X de un punto dado, o -1 si se produce algún error */
int point_getCoordinateX(const Point * );
/* Devuelve la coordenada Y de un punto dado, o -1 si se produce algún error */
int point_getCoordinateY(const Point * );
/* Devuelve el símbolo de un punto dado, o ERRORCHAR si se produce algún error */
char point_getSymbol(const Point * );
/* Devuelve la coordenada x del padre de un punto dado, o NULL si se produce algún error */
int point_getCoordxPadre(Point *);
/* Devuelve la coordenada y del padre de un punto dado, o NULL si se produce algún error */
int point_getCoordyPadre(Point *);
/* Devuelve el estado de un punto dado, o FAIL si se produce algún error */
Estado point_getEstado(Point *);
/* Modifica la coordenda X de un punto dado, devuelve NULL si se produce algún error */
Point * point_setCoordinateX(Point *, const int );
/* Modifica la coordenda Y de un punto dado, devuelve NULL si se produce algún error */
Point * point_setCoordinateY(Point *, const int );
/* Modifica el símbolo de un punto dado, devuelve NULL si se produce algún error */
Point * point_setSymbol(Point *, const char );
/* Modifica la coordenada x del padre de un punto dado, devuelve NULL si se produce algún error */
Point * point_setCoordxPadre(Point *, const int );
/* Modifica la coordenada y del padre de un punto dado, devuelve NULL si se produce algún error */
Point * point_setCoordyPadre(Point *, const int );
/* Modifica el estado de un punto dado, devuelve NULL si se produce algún error */
Point * point_setEstado(Point *, const Estado );
/* Devuelve TRUE si los dos puntos pasados como argumentos son iguales (revisando todos sus campos).
 Devuelve FALSE en otro caso. */
Bool point_equals(const Point * , const Point * );
/* Copia los datos de un punto a otro devolviendo el punto copiado (incluyendo la reserva de la memoria necesaria)
si todo ha ido bien, o NULL en otro caso */
Point * point_copy(const Point * );
/* Imprime en un fichero dado los datos de un punto con el siguiente formato: [(x,y): symbol]. Por ejemplo, un
punto con símbolo “*”, con coordenada X 3 e Y 7 se representará como [(3, 7): *]. Además devolverá el número de
caracteres que se han escrito con éxito (mirar documentación de fprintf) */
int point_print(FILE *, const Point *); 
#endif	/* POINT_H */