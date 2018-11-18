#ifndef SOLUTION_H
#define	SOLUTION_H

typedef struct _Solution Solution;
/* Inicializa un EleList reservando memoria e inicializando todos sus elementos. */
Solution* solution_ini();
/* Libera un EleList y todos sus elementos. */
void solution_free(Solution *sol);
/* Modifica el array de movimientos de un Solution . */
Status solution_setMove(Solution *sol, const Move *m);
/* Modifica el tad usado (pila o cola) de un Solution . */
Status solution_setTADusado(Solution *sol, char *p);
/* Modifica el número de movimientos de un Solution . */
Status solution_setNumero(Solution *sol, const int num);
/* Devuelve el array de movimientos de un Solution . */
void* solution_getMove(Solution *sol);
/* Devuelve el tad usado (pila o cola) de un Solution . */
void* solution_getTADusado(Solution *sol);
/* Devuelve el número de movimientos de un Solution . */
int solution_getNumero(Solution *sol);
/* Copia reservando memoria un EleList . */
Solution* solution_copy(const Solution *sol);
/* Imprime un EleList devolviendo el número de caracteres escritos. */
int solution_print(FILE* pf, const Solution *sol);

#endif	/* SOLUTION_H */

