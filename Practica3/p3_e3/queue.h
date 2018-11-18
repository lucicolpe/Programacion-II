
#ifndef QUEUE_H
#define	QUEUE_H

#define MAXQUEUE 4096

typedef struct _Queue Queue;
/**------------------------------------------------------------------
Inicializa la cola: reserva memoria para ella e inicializa todos sus elementos. Es importante que no se reserve
memoria para los elementos de la cola.
------------------------------------------------------------------*/
Queue* queue_ini();
/**------------------------------------------------------------------
Libera la cola y todos sus elementos.
------------------------------------------------------------------*/
void queue_free(Queue *q);
/**------------------------------------------------------------------
Comprueba si la cola está vacía.
------------------------------------------------------------------*/
Bool queue_isEmpty(const Queue *q);
/**------------------------------------------------------------------
Comprueba si la cola está llena.
------------------------------------------------------------------*/
Bool queue_isFull(const Queue* queue);
/**------------------------------------------------------------------
Inserta un elemento en la cola realizando para ello una copia del mismo, reservando memoria nueva para él.
------------------------------------------------------------------*/
Status queue_insert(Queue *q, const EleQueue* pElem);
/**------------------------------------------------------------------
Extrae un elemento de la cola. Es importante destacar que la cola deja de apuntar a este elemento por lo que
la gestión de su memoria debe ser coherente: devolver el puntero al elemento o devolver una copia liberando
el elemento en la cola.
------------------------------------------------------------------*/
EleQueue* queue_extract(Queue *q);
/**------------------------------------------------------------------
Devuelve el número de elementos de la cola.
------------------------------------------------------------------*/
int queue_size(const Queue *q);
/**------------------------------------------------------------------
Imprime toda la cola, devolviendo el número de caracteres escritos.
------------------------------------------------------------------*/
int queue_print(FILE *pf, const Queue *q);

#endif	/* QUEUE_H */
