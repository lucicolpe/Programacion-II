
#ifndef ELEQUEUE_H
#define	ELEQUEUE_H

typedef struct _EleQueue EleQueue;
/* Inicializa un EleQueue reservando memoria e inicializando todos sus elementos. */
EleQueue* elequeue_ini();
/* Libera un EleQueue y todos sus elementos. */
void elequeue_free(EleQueue * ele);
/* Modifica los datos de un EleQueue. */
EleQueue* elequeue_setInfo(EleQueue * e, void* p);
/* Devuelve el contenido de un EleQueue. */
void* elequeue_getInfo(EleQueue * e);
/* Copia reservando memoria un EleQueue. */
EleQueue* elequeue_copy(const EleQueue * src);
/* Devuelve un número positivo, negativo o cero según si ele1 es mayor, menor o igual que ele2. */
int elequeue_cmp(const EleQueue * ele1, const EleQueue * ele2);
/* Imprime un EleQueue devolviendo el número de caracteres escritos. */
int elequeue_print(FILE* pf, const EleQueue * ele);

#endif	/* ELEQUEUE_H */