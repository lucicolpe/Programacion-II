#include <stdio.h>
#include <stdlib.h>
#include "types.h"
#include "elelist.h"
#include "list.h"
#include "eletree.h"
#include "tree.h"

typedef struct _NodeBT {
    EleTree *info;
    struct _NodeBT *left;
    struct _NodeBT *right;
} NodeBT;

struct _Tree {
    NodeBT *root;
};

NodeBT* nodebt_ini() {
    NodeBT *n = NULL;

    n = (NodeBT*) malloc(sizeof (NodeBT));
    if (!n) return NULL;

    n->info = NULL;
    n->left = NULL;
    n->right = NULL;
    return n;
}

void nodebt_free(NodeBT *n) {
    if (!n) return;

    if (n->info) eletree_free(n->info);
    free(n);
}

Tree* tree_ini() {
    Tree *t = NULL;

    t = (Tree*) malloc(sizeof (Tree));
    if (!t) return NULL;

    t->root = NULL;
    return t;
}

void tree_freeRC(NodeBT *n) {
    if (!n) return;
    if (n->left) tree_freeRC(n->left);
    if (n->right) tree_freeRC(n->right);
    free(n);
    return;
}

void tree_free(Tree *pa) {
    if (!pa) return;
    tree_freeRC(pa->root);
    return;
}

Bool tree_isEmpty(const Tree *pa) {
    if (!pa || !pa->root) return TRUE;
    return FALSE;
}

Status tree_insertRC(NodeBT **n, const EleTree *po) {
    int ret;
    if (!*n) {
        *n = nodebt_ini();
        if (!*n) return ERROR;
        (*n)->info = eletree_copy(po);
        if (!(*n)->info) return ERROR;
        return OK;
    }
    ret = eletree_cmp(po, (*n)->info);
    if (ret == IGUAL || ret == ERR) return ERROR;
    if (ret == MENOR) tree_insertRC(&(*n)->left, po);
    if (ret == MAYOR) tree_insertRC(&(*n)->right, po);
    return OK;
}

/* Inserta en el árbol pa el EleTree po, devolviendo ERROR si el elemento ya existía en el árbol */
Status tree_insert(Tree *pa, const EleTree *po) {
    if (!pa || !po) return ERROR;

    return tree_insertRC(&pa->root, po);

}

Bool tree_findEleTreeRC(NodeBT *n, const EleTree* pe) {
    int ret;
    if (!n) return FALSE;

    ret = eletree_cmp(pe, n->info);
    if (ret == ERR) return FALSE;
    if (ret == IGUAL) return TRUE;
    if (ret == MENOR) return tree_findEleTreeRC(n->left, pe);
    return tree_findEleTreeRC(n->right, pe);
}

Bool tree_findEleTree(Tree* pa, const EleTree* pe) {
    int ret;
    if (!pa || !pe || !pa->root) return FALSE;

    ret = eletree_cmp(pe, pa->root->info);
    if (ret == ERR) return FALSE;
    if (ret == IGUAL) return TRUE;
    if (ret == MENOR) return tree_findEleTreeRC(pa->root->left, pe);
    return tree_findEleTreeRC(pa->root->right, pe);
}

int max(int a, int b) {
    if (a < b) return a;
    return b;
}

int tree_depthRC(NodeBT *n) {
    int left, right;
    if (!n) return 0;
    left = tree_depthRC(n->left);
    right = tree_depthRC(n->left);
    return 1 + max(left, n->right);

}

/* Devuelve la profundidad del árbol pa, considerando que un árbol vacío tiene profundidad -1 */
int tree_depth(const Tree *pa) {
    int left, right;
    if (!pa) return ERR;
    if (!pa->root) return ERROR;

    return tree_depthRC(pa->root);
}

int tree_numNodesRC(NodeBT *n) {
    if (!n) return 0;

    return 1 + tree_numNodesRC(n->left) + tree_numNodesRC(n->right);
}

/* Devuelve el número de nodos del árbol pa, considerando que un árbol vacío tiene 0 nodos */
int tree_numNodes(const Tree *pa) {
    if (!pa) return ERROR;
    if (!pa->root) return 0;

    return (tree_numNodesRC(pa->root));
}

void print_nodoPreOrderRC(FILE *f, NodeBT *n) {
    int *aux = NULL;
    if (!n) return;
    aux = eletree_getInfo(n->info);
    fprintf(f, "[%d]", *aux);
    print_nodoPreOrderRC(f, n->left);
    print_nodoPreOrderRC(f, n->right);
    return;
}

/******* Funciones de recorrido del árbol (P4_E3) ********/

/* Muestra el recorrido de un árbol en orden previo */
Status tree_preOrder(FILE *f, const Tree *pa) {
    if (!f || !pa) return ERROR;
    print_nodoPreOrderRC(f, pa->root);
    return OK;
}

void print_nodoInOrderRC(FILE *f, NodeBT *n) {
    int *aux = NULL;
    if (!n) return;
    print_nodoPreOrderRC(f, n->left);
    aux = eletree_getInfo(n->info);
    fprintf(f, "[%d]", *aux);
    print_nodoPreOrderRC(f, n->right);
    return;
}

/* Muestra el recorrido de un árbol en orden medio */
Status tree_inOrder(FILE *f, const Tree *pa) {
    if (!f || !pa) return ERROR;
    print_nodoInOrderRC(f, pa->root);
    return OK;
}

void print_nodoPostOrderRC(FILE *f, NodeBT *n) {
    int *aux = NULL;
    if (!n) return;
    print_nodoPreOrderRC(f, n->left);
    print_nodoPreOrderRC(f, n->right);
    aux = eletree_getInfo(n->info);
    fprintf(f, "[%d]", *aux);

    return;
}

/* Muestra el recorrido de un árbol en orden posterior */
Status tree_postOrder(FILE *f, const Tree *pa) {
    if (!f || !pa) return ERROR;
    print_nodoPostOrderRC(f, pa->root);
    return OK;
}

Status tree_nodoPreOrderToListRC(List *l, NodeBT *n) {
    EleList *ele = NULL;
    int ret;
    if (!n) return OK;
    ele = elelist_ini();
    if (!ele) return ERROR;
    ret = elelist_setInfo(ele, n->info);
    if (ret == ERROR) return ERROR;
    ret = list_insertLast(l, ele);
    if (ret == ERROR) return ERROR;
    ret == tree_nodoPreOrderToListRC(l, n->left);
    if (ret == ERROR) return ERROR;
    ret == tree_nodoPreOrderToListRC(l, n->right);
    if (ret == ERROR) return ERROR;
    return OK;
}

/****** Para el ejercicio opcional de P4_E3 *******/

/* Inserta en la lista l el recorrido de un árbol en orden previo */
Status tree_preOrderToList(List *l, const Tree *pa) {
    if (!l || !pa) return ERROR;
    return tree_nodoPreOrderToListRC(l, pa->root);

}

Status tree_nodoInOrderToListRC(List *l, NodeBT *n) {
    int ret;
    EleList *ele = NULL;
    if (!n) return OK;
    ret = tree_nodoInOrderToListRC(l, n->left);
    if (ret == ERROR) return ERROR;
    ele = elelist_ini();
    if (!ele) return ERROR;
    ret = elelist_setInfo(ele, n->info);
    if (ret == ERROR) return ERROR;
    ret = list_insertLast(l, ele);
    if (ret == ERROR) return ERROR;
    ret = tree_nodoInOrderToListRC(l, n->right);
    if (ret == ERROR) return ERROR;
    return OK;
}

/* Inserta en la lista l el recorrido de un árbol en orden medio */
Status tree_inOrderToList(List *l, const Tree *pa) {
    if (!l || !pa) return ERROR;
    return tree_nodoInOrderToListRC(l, pa->root);
}

Status tree_nodoPostOrderToListRC(List *l, NodeBT *n) {
    EleList *ele = NULL;
    int ret;
    if (!n) return OK;
    ret = tree_nodoPostOrderToListRC(l, n->left);
    if (ret == ERROR) return ERROR;
    ret = tree_nodoPostOrderToListRC(l, n->right);
    if (ret == ERROR) return ERROR;
    ele = elelist_ini();
    if (!ele) return ERROR;
    ret = elelist_setInfo(ele, n->info);
    if (ret == ERROR) return ERROR;
    ret = list_insertLast(l, ele);
    if (ret == ERROR) return ERROR;
    return OK;
}

/* Inserta en la lista l el recorrido de un árbol en orden posterior */
Status tree_postOrderToList(List *l, const Tree *pa) {
    if (!l || !pa) return ERROR;
    return tree_nodoPostOrderToListRC(l, pa->root);
}
