#include <stdio.h>
#include <stdlib.h>
#include "types.h"
#include "elelist.h"
#include "list.h"

typedef struct _Node {
 EleList* data;
 struct _Node *next;
} Node;

struct _List {
 Node *node;
};

Node* node_ini(){
    Node *n = NULL;
    n = (Node*)malloc(sizeof(Node));
    if(!n) return NULL;
    n->data = NULL;
    n->next = NULL;
    
    return n;    
}

void node_free(Node* n){
    if(!n) return;
    if(n->data) elelist_free(n->data);
    free(n);
}

List* list_ini(){
    List *lista = NULL;
    
    lista = (List*)malloc(sizeof(List));
    if(!lista) return NULL;
    
    lista->node = NULL;
    return lista;
}

void list_free(List* list){
    Node *aux = NULL;
    if(!list) return;
    if(!list->node){
        free(list);
        return;
    }
    while(list->node != NULL){
        aux = list->node;
        list->node = list->node->next;
        node_free(aux);
    }
    free(list);
}

Status list_insertFirst(List* list, const EleList *elem){
    Node *n = NULL, *aux = NULL;
    if(!list || !elem) return ERROR;
    
    n = node_ini();
    if(!n) return ERROR;
    
    n->data = elelist_copy(elem);
    if(!n->data){
        node_free(n);
        return ERROR;
    }
    aux = list->node;
    list->node = n;
    n->next = aux;
    aux = NULL;
    return OK;
}

Status list_insertLast(List* list, const EleList *elem){
    Node *n = NULL, *aux = NULL;
    if(!list || !elem) return ERROR;
    
    n = node_ini();
    if(!n) return ERROR;
    
    n->data = elelist_copy(elem);
    if(!n->data){
        node_free(n);
        return ERROR;
    }    
    if(!list->node){
        list->node = n;
        return OK;
    }    
    for(aux = list->node; aux->next != NULL; aux = aux->next);
    aux->next = n;
    return OK;
}

Status list_insertInOrder(List *list, const EleList *pElem){
    int comp;
    Node *n = NULL, *aux = NULL;
    if(!list || !pElem) return ERROR;
    
    if(!list->node) return list_insertFirst(list, pElem);
    
    comp = elelist_cmp(list->node->data, pElem);
    if(comp == ERR) return ERROR;
    if(comp >= 0) return list_insertFirst(list, pElem);
    
    aux = list->node;
    while(1){
        if(!aux->next) return list_insertLast(list, pElem);
        comp = elelist_cmp(aux->next->data, pElem);
        if(comp == ERR) return ERROR;
        if(comp >= 0) break;
        aux = aux->next;
    }
    n = node_ini();
    if(!n) return ERROR;
    
    n->data = elelist_copy(pElem);
    if(!n->data){
        node_free(n);
        return ERROR;
    }
    
    n->next = aux->next;
    aux->next = n;    
    return OK;
}

EleList* list_extractFirst(List* list){
    Node *aux = NULL;
    EleList *ele = NULL;
    if(!list || !list->node) return NULL;
    
    aux = list->node;
    list->node = aux->next;
    
    ele = elelist_copy(aux->data);
    node_free(aux);
    return ele;
}

EleList* list_extractLast(List* list){
    Node *aux1 = NULL, *aux2 = NULL;
    EleList *ele = NULL;
    
    if(!list || !list->node) return NULL;
    
    aux1 = list->node;
    if(!aux1->next) return list_extractFirst(list);
        
    while(aux1->next->next != NULL) aux1 = aux1->next;
    
    aux2 = aux1->next;
    aux1->next = NULL;
    
    ele = elelist_copy(aux2->data);
    node_free(aux2);
    return ele;    
}

Bool list_isEmpty(const List* list){
    if(!list->node) return TRUE;
    return FALSE;
}

int list_size(const List* list){
    int tam = 0;
    Node *aux = NULL;    
    if(!list) return -1;
    
    for(aux = list->node; aux != NULL; aux = aux->next) tam++;
    return tam;
}

int list_print(FILE *fd, const List* list){
    int ret = 0, i = 0;
    Node *aux = NULL;    
    if(!list) return -1;
    
    for(ret =0, aux = list->node; aux != NULL; aux = aux->next){
        i = elelist_print(fd, aux->data);
        if(i <= 0) return -1;
        ret +=i;
        fprintf(fd, "\n");
    }
    return ret;
}
