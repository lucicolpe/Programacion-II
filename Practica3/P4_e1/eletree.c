#include <stdio.h>
#include <stdlib.h>
#include "types.h"
#include "eletree.h"

struct _EleTree{
    int *dato;
};

EleTree* eletree_ini(){
    EleTree *ele = NULL;
    
    ele = (EleTree *)malloc(sizeof(EleTree));
    if(!ele) return NULL;
    
    ele->dato = (int *)malloc(sizeof(int));
    if(!ele->dato){
        free(ele);
        return NULL;
    }
    return ele;
}

void eletree_free(EleTree* pe){
    if(!pe) return;
    if(pe->dato) free(pe->dato);
    
    free(pe);
}

Status eletree_setInfo(EleTree* pe, void* info){
    if(!pe || !info) return ERROR;
    
    *pe->dato = *(int*)info;
    return OK;
}

void* eletree_getInfo(const EleTree* pe){
    if(!pe) return;
    
    return pe->dato;
}

int eletree_cmp(const EleTree* pe1, const EleTree* pe2){
    if(!pe1 || !pe2 || !pe1->dato || !pe2->dato) return ERR;
    
    if(*pe1->dato < *pe2->dato) return MENOR;
    if(*pe1->dato > *pe2->dato) return MAYOR;
    return IGUAL;
}

EleTree* eletree_copy(const EleTree* pOrigin){
    EleTree *ele = NULL;
    if(!pOrigin || !pOrigin->dato) return NULL;
    
    ele = eletree_ini();
    if(!ele) return NULL;
    
    *ele->dato = *pOrigin->dato;
    return ele;
}

int eletree_print(FILE* pf, const EleTree* pe){
    int ret;
    if(!pf || !pe || !pe->dato) return -1;
    
    ret = fprintf(pf, "[%d]/n", *pe->dato);
    
    return ret;
}