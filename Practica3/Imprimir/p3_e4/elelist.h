#ifndef ELELIST_H
#define	ELELIST_H

typedef struct _EleList EleList;
/* Inicializa un EleList reservando memoria e inicializando todos sus elementos. */
EleList* elelist_ini();
/* Libera un EleList y todos sus elementos. */
void elelist_free(EleList * ele);
/* Modifica los datos de un EleList . */
Status elelist_setInfo(EleList * e, void* p);
/* Devuelve el contenido de un EleList . */
void* elelist_getInfo(EleList * e);
/* Copia reservando memoria un EleList . */
EleList* elelist_copy(const EleList * src);
/* Devuelve un número positivo, negativo o cero según si ele1 es mayor, menor o igual que ele2. */
int elelist_cmp(const EleList * ele1, const EleList * ele2);
/* Imprime un EleList devolviendo el número de caracteres escritos. */
int elelist_print(FILE* pf, const EleList * ele);

#endif	/* ELELIST_H */

