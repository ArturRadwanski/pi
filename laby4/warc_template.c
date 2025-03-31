#include <stdio.h>
#include <stdlib.h>
#define N 20

int cnt[2];
char filler = '_';

int rnd(const int min, const int max) {
    return (rand() % (max - min)) + min;
}

void print(char board[][N], const int n) {
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            printf("%c ", board[i][j]);
        }
        printf("\n");
    }
}

void start(char board[][N], const int n) {

  for(int i = 0; i < n; i++) {
    for(int j = 0; j < n; j++) {
      board[i][j] = filler;
    }
  }

    for(int i = 0; i < 4; i++) {
        for(int j = i % 2 ; j < n; j += 2) {
            board[i][j] = '1';
        }
    }

    for(int i = n - 1; i > n - 5; i--) {
        for(int j = i % 2 ; j < n; j += 2) {
            board[i][j] = '2';
        }
    }
}

int move1(char board[][N], const int i, const int j, const int n) {
    if(i < n - 1){
        if(j < n - 1){
            if(board[i + 1][j + 1] == filler){
                board[i + 1][j + 1] = '1';
                board[i][j] = filler;
                return 1;
            }
        }
        else if(j > 0){
            if(board[i + 1][j - 1] == filler){
                board[i + 1][j - 1] = '1';
                board[i][j] = filler;
                return 1;
            }
        }
    }
    return 0;
}

int move2(char board[][N], const int i, const int j, const int n) {
    if(i > 0){
        if(j < n - 1 && board[i - 1][j + 1] == filler){
                board[i - 1][j + 1] = '2';
                board[i][j] = filler;
                return 1;
        }
        if(j > 0 && board[i - 1][j - 1] == filler){
            board[i - 1][j - 1] = '2';
            board[i][j] = filler;
            return 1;
        }
    }
    return 0;
}

int move(char board[][N], const int i, const int j, const int n) {
  if(board[i][j] == '1') {
    return move1(board, i, j, n);
  }
  if(board[i][j] == '2') {
    return move2(board, i, j, n);
  }
  return 0;
}

int checkCapture1(char board[][N], const int i, const int j, const int n) {
  if(i < n - 2){
      if(j < n - 2 && board[i + 1][j + 1] == '2' && board[i + 2][j + 2] == filler){
          board[i + 1][j + 1] = filler;
          board[i][j] = filler;
          board[i + 2][j + 2] = '1';
          return 1;
      }
      if(j > 1 && board[i + 1][j - 1] == '2' && board[i + 2][j - 2] == filler){
          board[i + 1][j - 1] = filler;
          board[i][j] = filler;
          board[i + 2][j - 2] = '2';
          return 1;
      }
  }
  return 0;
}

int checkCapture2(char board[][N], const int i, const int j, const int n) {
  if(i > 1){
      if(j < n - 2 && board[i - 1][j + 1] == '1' && board[i - 2][j + 2] == filler){
        board[i - 1][j + 1] = filler;
        board[i][j] = filler;
        board[i - 2][j + 2] = '2';
        return 1;
      }
      else if(j > 1 && board[i - 1][j - 1] == '1' && board[i - 2][j - 2] == filler){
        board[i - 1][j - 1] = filler;
        board[i][j] = filler;
        board[i - 2][j - 2] = '2';
        return 1;
      }
  }
  return 0;
}

int capture(char board[][N], const int i, const int j, const int n) {
    if(board[i][j] == '1') {
      return checkCapture1(board, i, j, n);
    }
    else if(board[i][j] == '2') {
      return checkCapture2(board, i, j, n);
    }
    return 0;
}




int main(void) {
    char board[N][N];
    int n, steps;
    unsigned seed;
    scanf("%d %u %d", &n, &seed, &steps);
    srand(seed);
    cnt[0] = cnt[1] = 2 * n;
    start(board, n);
    for (int i = 0; i < steps; i++) {
        int ix, iy;
        const char turn = (i % 2 == 0) ? '1' : '2';
        do {
            ix = rnd(0, n);
            iy = rnd(0, n);
        } while (board[ix][iy] != turn);
        if (!capture(board, ix, iy, n)) {
            move(board, ix, iy, n);
        }
    }
    print(board, n);
    printf("%d %d\n", cnt[0], cnt[1]);

    return 0;
}

