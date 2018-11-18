#include "stack.h"

struct _Stack {
    int top;
    EleStack* item[MAXSTACK];
};

Stack * stack_ini() {
    Stack *s;
    int i;
    s = (Stack*) malloc(sizeof (Stack));
    if (!s) return NULL;

    s->top = -1;
    for (i = 0; i < MAXSTACK; i++) {
        s->item[i] = NULL;
    }
    return s;
}

void stack_free(Stack *s) {
    if (!s) return;
    for (; s->top>-1; s->top--) {
        elestack_free(s->item[s->top]);
    }
    free(s);
}

Status stack_push(Stack *s, const EleStack *ele) {
    EleStack *aux = NULL;
    if (!s) return ERROR;
    if (!ele) return ERROR;
    if(stack_isFull(s)) return ERROR;
    
    aux = elestack_copy(ele);
    if (!aux) return ERROR;

    s->top++;
    s->item[s->top] = aux;
    return OK;
}

EleStack * stack_pop(Stack *s) {
    EleStack *aux = NULL;
    if (!s) return NULL;
    aux = s->item[s->top];
    s->item[s->top] = NULL;
    s->top--;
    return aux;
}

EleStack * stack_top(const Stack *s) {
    EleStack *ele;
    if (!s) return NULL;
    ele = elestack_copy(s->item[s->top]);
    return ele;
}

Bool stack_isEmpty(const Stack *s) {
    if (s->top == -1) return TRUE;
    return FALSE;
}

Bool stack_isFull(const Stack *s) {
    if (s->top == MAXSTACK - 1) return TRUE;
    return FALSE;
}

int stack_print(FILE*f, const Stack *s) {
    int retorno, i;
    if (!s) return -1;

    for (retorno = 0, i = s->top; i >= 0; i--) {
        retorno += elestack_print(f, s->item[i]);
        retorno += fprintf(f, "\n");
    }
    return retorno;
}
