#ifndef ELESTACK_H
#define	ELESTACK_H


typedef struct _EleStack EleStack;
/**------------------------------------------------------------------
Inicializa un elemento de pila. Salida: Puntero al elemento inicializado o NULL en caso de error
------------------------------------------------------------------*/
EleStack * elestack_ini();
/**------------------------------------------------------------------
Elimina un elemento. Entrada: Elemento a destruir.
------------------------------------------------------------------*/
void elestack_free(EleStack *);
/**------------------------------------------------------------------
Modifica los datos de un elemento. Entrada: El elemento a modificar y el contenido a guardar en dicho
elemento. Salida: El elemento a modificar o NULL si ha habido error.
------------------------------------------------------------------*/
EleStack * elestack_setInfo(EleStack *, void*);
/**------------------------------------------------------------------
Devuelve el contenido de EleStack. Entrada: El elemento. Salida: El contenido de EleStack o NULL si ha
habido error.
------------------------------------------------------------------*/
void * elestack_getInfo(EleStack *);
/**------------------------------------------------------------------
Copia un elemento en otro, reservando memoria. Entrada: el elemento a copiar. Salida: Devuelve un puntero
al elemento copiado o NULL en caso de error.
------------------------------------------------------------------*/
EleStack * elestack_copy(const EleStack *);
/**------------------------------------------------------------------
Compara dos elementos. Entrada: dos elementos a comparar. Salida: Devuelve TRUE en caso de ser iguales
y si no FALSE
------------------------------------------------------------------*/
Bool elestack_equals(const EleStack *, const EleStack *);
/**------------------------------------------------------------------
Imprime en un fichero ya abierto el elemento. Entrada: Fichero en el que se imprime y el elemento a imprimir.
Salida: Devuelve el número de caracteres escritos.
------------------------------------------------------------------*/
int elestack_print(FILE *, const EleStack *);
#endif	/* ELESTACK_H */


