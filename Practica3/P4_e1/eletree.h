#ifndef ELETREE_H
#define	ELETREE_H

typedef struct _EleTree EleTree;
/* Inicializa un EleTree reservando memoria */
EleTree* eletree_ini();
/* Libera un EleTree */
void eletree_free(EleTree* pe);
/* Modifica los datos de un EleTree */
Status eletree_setInfo(EleTree* pe, void* info);
/* Devuelve los datos de un EleTree */
void* eletree_getInfo(const EleTree* pe);
/* Compara dos EleTree’s devolviendo un número negativo, cero o positivo según si pe1 es menor, igual o
mayor que pe2 */
int eletree_cmp(const EleTree* pe1, const EleTree* pe2);
/* Copia reservando memoria un EleTree */
EleTree* eletree_copy(const EleTree* pOrigin);
/* Imprime un EleTree devolviendo el número de caracteres escritos */
int eletree_print(FILE* pf, const EleTree* pe);

/***** Estas dos funciones se necesitan a partir del ejercicio P4_E4 *****/
/* Devuelve la dimensión de un EleTree */
/* int eletree_getDim(const EleTree* pe); */
/* Compara la componente dim-ésima entre dos EleTree’s */
/* int eletree_cmpd(const EleTree* pe1, const EleTree* pe2, const int dim); */

#endif	/* ELETREE_H */

