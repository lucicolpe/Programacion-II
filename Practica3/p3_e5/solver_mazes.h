#ifndef SOLVER_MAZES_H
#define	SOLVER_MAZES_H

Status mazesolver_stack(const char* maze_file, const Move strat[4], List *l);

Status mazesolver_queue(const char* maze_file, const Move strat[4], List *l);

void mazesolver_run(const char* maze_file, Move strat[][4], const int num_strategies, List *lista);

#endif	/* SOLVER_MAZES_H */