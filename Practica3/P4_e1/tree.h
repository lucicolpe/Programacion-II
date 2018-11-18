#ifndef TREE_H
#define	TREE_H

typedef struct _Tree Tree;
/* Inicializa el árbol reservando memoria */
Tree* tree_ini();
/* Libera el árbol y todos sus elementos */
void tree_free(Tree *pa);
/* Comprueba si un árbol está vacío */
Bool tree_isEmpty( const Tree *pa);
/* Inserta en el árbol pa el EleTree po, devolviendo ERROR si el elemento ya existía en el árbol */
Status tree_insert(Tree *pa, const EleTree *po);
/* Devuelve TRUE si se puede encontrar pe en el árbol pa */
Bool tree_findEleTree(Tree* pa, const EleTree* pe);
/* Devuelve la profundidad del árbol pa, considerando que un árbol vacío tiene profundidad -1 */
int tree_depth(const Tree *pa);
/* Devuelve el número de nodos del árbol pa, considerando que un árbol vacío tiene 0 nodos */
int tree_numNodes(const Tree *pa);
/******* Funciones de recorrido del árbol (P4_E3) ********/
/* Muestra el recorrido de un árbol en orden previo */
Status tree_preOrder(FILE *f, const Tree *pa);
/* Muestra el recorrido de un árbol en orden medio */
Status tree_inOrder(FILE *f, const Tree *pa);
/* Muestra el recorrido de un árbol en orden posterior */
Status tree_postOrder(FILE *f, const Tree *pa);
/****** Para el ejercicio opcional de P4_E3 *******/
/* Inserta en la lista l el recorrido de un árbol en orden previo */
Status tree_preOrderToList(List *l, const Tree *pa);
/* Inserta en la lista l el recorrido de un árbol en orden medio */
Status tree_inOrderToList(List *l, const Tree *pa);
/* Inserta en la lista l el recorrido de un árbol en orden posterior */
Status tree_postOrderToList(List *l, const Tree *pa);

#endif	/* TREE_H */

