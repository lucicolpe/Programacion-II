#ifndef TYPES_H
#define TYPES_H

typedef enum {
 ERROR = 0, OK = 1
} Status;

typedef enum {
 FALSE = 0, TRUE = 1
} Bool;

/*Se ha definido una enumeración para la función que recorre el laberinto.
 * Esta devuelve POSIBLE o NO_POSIBLE, según se pueda salir o no del laberinto,
 * y FALLO si ha habido algún error*/
typedef enum {
    FALLO = 0, POSIBLE = 1, NO_POSIBLE = 2
}Posible;

/*La función que recorre el laberinto, etiqueta el punto como DESCUBIERTO si ha 
 * llegado hasta él, EXPLORADO si ya ha descubierto todos los puntos vecinos.
 El punto se inicializa con el estado NADA y la función que devuelve el estado
 del punto, devuelve FAIL si ha ocurrido algún error*/
typedef enum {
    FAIL = 0, NADA = 1, EXPLORADO = 2, DESCUBIERTO = 3 
}Estado;

typedef enum {
 ERR = -2, MENOR = -1, IGUAL = 0, MAYOR = 1
} Comp;

#endif /* TYPES_H */