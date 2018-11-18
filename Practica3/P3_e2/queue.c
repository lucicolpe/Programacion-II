#include <stdio.h>
#include <stdlib.h>
#include "types.h"
#include "elequeue.h"
#include "queue.h"

struct _Queue {
    EleQueue** head;
    EleQueue** end;
    EleQueue* item[MAXQUEUE];
};

Queue* queue_ini() {
    int i;
    Queue* q = NULL;

    q = (Queue*) malloc(sizeof (Queue));
    if (!q) return NULL;

    for (i = 0; i < MAXQUEUE; i++)
        q->item[i] = NULL;

    q->head = q->item;
    q->end = q->item;

    return q;
}

void queue_free(Queue *q) {
    if (!q) return;

    if (q->head <= q->end) {
        while (q->head != q->end) {
            elequeue_free(*q->head);
            q->head++;
        }
        free(q);
        return;
    } else {
        while (q->head != q->end) {
            elequeue_free(*q->head);
            q->head++;
            if (q->head == q->item + MAXQUEUE) q->head = q->item;
        }
        free(q);
    }
    return;
}

Bool queue_isEmpty(const Queue* q) {
    if (q->head == q->end) return TRUE;
    return FALSE;
}

Bool queue_isFull(const Queue* q) {
    if (q->end == &q->item[MAXQUEUE - 1]) {
        if (q->head == q->item) return TRUE;
    } else if (q->end + 1 == q->head) return TRUE;
    return FALSE;
}

Status queue_insert(Queue* q, const EleQueue* ele) {
    EleQueue* aux = NULL;
    if (!q || !ele || queue_isFull(q)) return ERROR;

    aux = elequeue_copy(ele);
    if (!aux) return ERROR;

    *q->end = aux;
    q->end++;
    if (q->end == q->item + MAXQUEUE) q->end = q->item;

    return OK;
}

EleQueue* queue_extract(Queue* q) {
    EleQueue* aux = NULL;
    if (!q || queue_isEmpty(q)) return NULL;

    aux = *q->head;
    q->head++;
    if (q->head == q->item + MAXQUEUE) q->head = q->item;

    return aux;
}

int queue_size(const Queue* q) {
    if(!q) return -1;
    if (q->head <= q->end) {
        return (q->end - q->head);
    } else return (MAXQUEUE - (q->head - q->end));
}

int queue_print(FILE* pf, const Queue* q) {
    EleQueue** aux = NULL;
    int ret = 0;
    if (!q || !pf) return -1;

    for (aux = q->head; aux != q->end; aux++) {
        ret += elequeue_print(pf, *aux);
        fprintf(pf, "\n");
        if (aux == q->item + MAXQUEUE)
            aux = (EleQueue **)q->item;
    }
    return ret;
}
