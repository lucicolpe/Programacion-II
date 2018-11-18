#include <stdio.h>
#include <stdlib.h>
#include "types.h"
#include "point.h"
#include "maze.h"
#include "solution.h"

struct _Solution {
    Move strat[4];
    char tad[5];
    int nummov;
};

Solution* solution_ini() {
    Solution *sol = NULL;

    sol = (Solution*) malloc(sizeof (Solution));
    if (!sol) return NULL;
    sol->nummov = -1;
    
    return sol;
}

void solution_free(Solution *sol) {
    if (!sol) return;
    free(sol);
}

Status solution_setMove(Solution *sol, const Move *m) {
    int i;
    if (!sol || !m) return ERROR;

    for (i = 0; i < 4; i++) sol->strat[i] = m[i];

    return OK;
}

Status solution_setTADusado(Solution *sol, char *p) {
    int i;
    if (!sol || !p) return ERROR;

    for (i = 0; i < 5; i++) sol->tad[i] = p[i];

    return OK;
}

Status solution_setNumero(Solution *sol, const int num) {
    if (!sol || num <= 0) return ERROR;

    sol->nummov = num;

    return OK;
}

void* solution_getMove(Solution *sol) {
    if (!sol) return NULL;

    return sol->strat;
}

void* solution_getTADusado(Solution *sol) {
    if (!sol) return NULL;

    return sol->tad;
}

int solution_getNumero(Solution *sol) {
    if (!sol) return -1;

    return sol->nummov;
}

Solution* solution_copy(const Solution *sol) {
    Solution *aux = NULL;
    int i;
    
    if (!sol) return ERROR;

    aux = solution_ini();
    if (!aux) return NULL;

    for(i = 0; i < 4; i++) aux->strat[i] = sol->strat[i];
    for(i = 0; i < 5; i++) aux->tad[i] = sol->tad[i];
    aux->nummov = sol->nummov;

    return aux;
}

int solution_print(FILE* pf, const Solution *sol) {
    int ret;
    if (!sol) return -1;

    ret = fprintf(pf, "[%d%d%d%d, %s, %d]\n", sol->strat[0], sol->strat[1], sol->strat[2], sol->strat[3], sol->tad, sol->nummov);
    return ret;
}
