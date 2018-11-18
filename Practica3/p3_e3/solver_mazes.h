#ifndef SOLVER_MAZES_H
#define	SOLVER_MAZES_H

int mazesolver_stack(const char* maze_file, const Move strat[4]);

int mazesolver_queue(const char* maze_file, const Move strat[4]);

void mazesolver_run(const char* maze_file, Move strat[][4], const int num_strategies);

#endif	/* SOLVER_MAZES_H */