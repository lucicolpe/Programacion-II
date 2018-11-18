#ifndef LIST_H
#define	LIST_H

typedef struct _List List;
/* Inicializa la lista reservando memoria e inicializa todos sus elementos. */
List* list_ini();
/* Libera la lista y todos sus elementos. */
void list_free(List* list);
/* Inserta al principio de la lista realizando una copia del elemento. */
Status list_insertFirst(List* list, const EleList *elem);
/* Inserta al final de la lista realizando una copia del elemento. */
Status list_insertLast(List* list, const EleList *elem);
/* Inserta en orden en la lista realizando una copia del elemento. */
Status list_insertInOrder(List *list, const EleList *pElem);
/* Extrae del principio de la lista realizando una copia del elemento almacenado en dicho nodo. */
EleList* list_extractFirst(List* list);
/* Extrae del final de la lista realizando una copia del elemento almacenado en dicho nodo. */
EleList* list_extractLast(List* list);
/* Comprueba si una lista está vacía o no. */
Bool list_isEmpty(const List* list);
/* Devuelve el tamaño de una lista. */
int list_size(const List* list);
/* Imprime una lista devolviendo el número de caracteres escritos. */
int list_print(FILE *fd, const List* list);

#endif	/* LIST_H */

