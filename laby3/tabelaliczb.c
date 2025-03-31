//
// Created by arradwan on 17.03.25.
//
#include <stdio.h>
int N[100] = {0};
void fillZeros(void){
  for(int i = 0; i < 100; i++) {
    N[i] = 0;
  }
}
void printNumbers(const int start, const int end) {
  for(int i = start; i < end; i++) {
    printf("%d ", N[i]);
  }
}

void setValue(const int index, const int value) {
  N[index] = value;
}

int sumValues(const int start, const int end) {
  int sum = 0;
  for(int i = start; i < end; i++) {
    sum += N[i];
  }
  return sum;
}

int findDiff(const int pattern) {
  int diff = 0;
  for(int i = 0; i < 100; i++)
      if(pattern != N[i]) diff++;
  return diff;
}

void swap(const int i, int j) {
  const int temp = N[i];
  N[i] = N[j];
  N[j] = temp;
}
long long int pow(int base_index, int pow_index) {
  long long int result = 1;
  for(int i = 0; i < N[pow_index]; i++) {
    result *= N[base_index];
  }
}

int main() {


  for (int i = 1; i <= 100; i++) {
    printf("N[%d] = %d\n", i, N[i]);
  }
  return 0;
}