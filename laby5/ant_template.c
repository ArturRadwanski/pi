#include <stdio.h>
#include <stdlib.h>
#define N 20

typedef struct Ant {
	int pi, pj;
	int direction;
} Ant;
/*N = 0  [-1][+0]
 *E = 1  [+0][+1]
 *S = 2  [+1][+0]
 *W = 3  [+0][-1]
 *
 */
enum Direction { UP=0, RIGHT=1, DOWN=2, LEFT=3 };

int rnd(const int min, const int max) {
	return (rand() % (max - min)) + min;
}

void print_board(int** board, const int n) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			printf("%d ", board[i][j]);
		}
		printf("\n");
	}
}

void print_ant(const Ant* ant) {
	char dir;
	switch (ant->direction) {
		case 1:
			dir = 'E';
		break;
		case 2:
			dir = 'S';
		break;
		case 3:
			dir = 'W';
		break;
		default:
			dir = 'N';
		break;
	}
	printf("%d %d %c", ant->pi, ant->pj, dir);
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
}

void free_board(int** board, const int n) {
	for (int i = 0; i < n; i++) {
		free(board[i]);
	}
	free(board);
}

void boardIndex(Ant* ant, const int n) {
	switch (ant->direction) {
		case UP:
			ant->pi--;
			if (ant->pi < 0) {
				ant->pi = n - 1;
			}
			break;
		case RIGHT:
			ant->pj = (ant->pj + 1) % n;
			break;
		case DOWN:
			ant->pi = (ant->pi + 1) % n;
			break;
		case LEFT:
			ant->pj--;
			if (ant->pj < 0) {
				ant->pj = n - 1;
			}
			break;
		default: break;
	}
}

void ant_move(int** board, const int n, Ant* ant) {
	const int i = ant->pi;
	const int j = ant->pj;
	switch (board[i][j]) {
		case 1:
			boardIndex(ant, n);
			board[i][j] = 7;
			break;
		case 2:
			ant->direction++;
			ant->direction %= 4;
			board[i][j] = 4;
			break;
		case 3:
			ant->direction += 3;
		    ant->direction %= 4;
		    board[i][j] = 2;
			break;
		case 4:
			ant->direction++;
		    ant->direction %= 4;
		    boardIndex(ant, n);
		    ant->direction += 3;
		    ant->direction %= 4;
			board[i][j] = 6;
			break;
		case 5:
			ant->direction += 3;
			ant->direction %= 4;
			boardIndex(ant, n);
			ant->direction++;
			ant->direction %= 4;
			board[i][j] = 3;
			break;
		case 6:
			ant->direction += 2;
			ant->direction %= 4;
			boardIndex(ant, n);
			ant->direction += 2;
			ant->direction %=4;
			board[i][j] = 5;
			break;
		case 7:
			ant->direction += 2;
			ant->direction %= 4;
			board[i][j] = 8;
			break;
		case 8:
			board[i][j] = 1;
			break;
		default: break;
	}
}



void ant_simulation(int** board, const int n, Ant* ant, const int steps) {
	ant->pi = 0;
	ant->pj = 0;
	ant->direction = RIGHT;
	for (int i = 0; i < steps; i++) {
		ant_move(board, n, ant);
	}
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
	print_ant(&ant);

	free_board(board, n);

	return 0;
}

