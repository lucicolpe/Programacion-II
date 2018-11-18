#ifndef TYPES_H
#define TYPES_H

typedef enum {
    ERROR = 0, OK = 1
} Status;

typedef enum {
    FALSE = 0, TRUE = 1
} Bool;

typedef enum {
    FAIL = 0, NADA = 1, EXPLORADO = 2, DESCUBIERTO = 3 
}Estado;

typedef enum {
    ERR = -2, MENOR = -1, IGUAL = 0, MAYOR = 1
} Comp;

#endif /* TYPES_H */