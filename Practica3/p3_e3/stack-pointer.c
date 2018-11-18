#include <stdio.h>
#include <stdlib.h>
#include "types.h"
#include "elestack.h"
#include "stack.h"

struct _Stack {
    EleStack** top;
    EleStack* item[MAXSTACK];
};

Stack * stack_ini() {
    Stack *s;
    int i;
    s = (Stack*) malloc(sizeof (Stack));
    if (!s) return NULL;
    /*Al inicializar la pila, como está vacía, top apunta a NULL*/
    s->top = NULL;
    for (i = 0; i < MAXSTACK; i++) {
        s->item[i] = NULL;
    }
    return s;
}

void stack_free(Stack *s) {
    if (!s) return;
    /*Se van liberando los elementos a los que apuntan los punteros en la dirección
    del tope mientras este sea mayor o igual que la dirección de la posición 0*/
    while (s->top >= s->item) {
        elestack_free(*s->top);
        s->top--;
    }
    free(s);
}

Status stack_push(Stack *s, const EleStack *ele) {
    EleStack *aux = NULL;
    if (!s) return ERROR;
    if (!ele) return ERROR;
    if (stack_isFull(s)) return ERROR;

    aux = elestack_copy(ele);
    if (!aux) return ERROR;
    /*Si la pila estaba vacía, top apuntaba a NULL. Para incrementarlo se hace que apunte a la posición 0*/
    if (s->top == NULL) s->top = s->item;
    else s->top++;
    *(s->top) = aux;
    return OK;
}

EleStack * stack_pop(Stack *s) {
    EleStack *aux = NULL;
    if (!s) return NULL;
    if (stack_isEmpty(s)) return NULL;
    /*Se guarda en aux la dirección del elemento tope, y en la pila, 
     *el puntero que apuntaba a este elemento, se pone a NULL*/
    aux = *s->top;
    *s->top = NULL;
    /*Se disminuye el tope para que apunte a una dirección menos. Si al extraer un 
     * elemento, la pila queda vacía, se hace que tope apunte a NULL*/
    if (s->top > s->item) {
        s->top--;
    } else s->top = NULL;
    return aux;
}

EleStack * stack_top(const Stack *s) {
    EleStack *ele;
    if (!s) return NULL;
    if (stack_isEmpty(s)) return NULL;

    ele = elestack_copy(*s->top);
    return ele;
}

Bool stack_isEmpty(const Stack *s) {
    /*La condición de que la pila está vacía es que tope esté apuntando a NULL*/
    if (s->top == NULL) return TRUE;
    return FALSE;
}

Bool stack_isFull(const Stack *s) {
    /*La condición de que la pila está llena es que tope esté apuntando a la dirección más alta*/
    if (s->top == &(s->item[MAXSTACK - 1])) return TRUE;
    return FALSE;
}

int stack_print(FILE*f, const Stack *s) {
    int retorno;
    EleStack** i;
    if (!s) return -1;
    /*Para no modificar el tope porque el argumento de entrada es de tipo const,
     * se hace un bucle que asigna a i el valor del tope y llama a la función 
     * que imprime el contenido de i, que es un puntero a elemento*/
    for (retorno = 0, i = s->top; i>=s->item; i--) {
        retorno += elestack_print(f, *i);
        retorno += fprintf(f, "\n");
    }
    return retorno;
}