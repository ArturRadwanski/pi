#include <stdio.h>
#include <stdlib.h>
#define N 20

typedef struct Ant {
	int pi, pj;
	int direction;
} Ant;
/*N = 0  [+1][+0]
 *E = 1
 *S = 2
 *W = 3
 *
 */

int rnd(const int min, const int max) {
	return (rand() % (max - min)) + min;
}

void print_board(int** board, const int n) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			printf("%d ", board[i][j]);
		}
	}
}

void print_ant(const Ant ant) {
}

void init_board(int*** board, const int n) {
	*board = (int**) malloc(n * sizeof(int*));
	for (int i = 0; i < n; i++) {
		(*board)[i] = (int*) malloc(n * sizeof(int));
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			(*board)[i][j] = rnd(1, 9);
		}
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			printf("%d ", (*board)[i][j]);
		}
	}
}

void free_board(int** board, const int n) {
	for (int i = 0; i < n; i++) {
		free(board[i]);
	}
	free(board);
}

void ant_move(int** board, const int n, Ant* ant) {
}

void ant_simulation(int** board, const int n, Ant* ant, const int steps) {
	ant->pi = 0;
	ant->pj = 0;
	ant->direction = 1;
}

int main(void) {
	int** board;
	int n, steps;
	unsigned seed;
	Ant ant;

	scanf("%d %d %d", &n, &seed, &steps);
	srand(seed);
	init_board(&board, n);
	ant_simulation(board, n, &ant, steps);
	print_board(board, n);
	print_ant(ant);

	free_board(board, n);

	return 0;
}

