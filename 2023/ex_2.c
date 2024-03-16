#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int heaviest_path(unsigned int **matrix, int height, int width );
int heaviest_path_helper(unsigned int **matrix, int height, int width, int i, int j);

int main() {
  int width = 7;
  int height = 5;
  unsigned int **matrix = (unsigned int**)malloc(height * sizeof(unsigned int*));
  for (int i = 0; i < width; i++) {
    matrix[i] = (unsigned int*)malloc(width * sizeof(unsigned int));
  }
  unsigned int arr[5][7] = {
    { 1, 2, 0, 4, 5, 6, 7 },
    { 2, 3, 1, 4, 6, 2, 4 },
    { 6, 7, 7, 8, 9, 9, 9 },
    { 8, 8, 8, 8, 8, 3, 1 },
    { 5, 7, 7, 3, 4, 2, 9 }
  };
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++)
      matrix[i][j] = arr[i][j];
  }
  printf("Heaviest path is: %d\n", heaviest_path(matrix, height, width));
  return 0;
}

int heaviest_path(unsigned int **matrix, int height, int width ) {
  return heaviest_path_helper(matrix, height, width, 0, 0);
}

int heaviest_path_helper(unsigned int **matrix, int height, int width, int i, int j) {
  if (i >= height) return 0;
  if (j >= width) return 0;
  int downWeight = matrix[i][j] + heaviest_path_helper(matrix, height, width, i+1, j);
  int rightWeight = matrix[i][j] + heaviest_path_helper(matrix, height, width, i, j+1);

  if (matrix[i+1][j] < matrix[i][j]) downWeight = matrix[i][j];
  if (matrix[i][j+1] < matrix[i][j]) rightWeight = matrix[i][j];
  return (downWeight > rightWeight) ? downWeight : rightWeight;
}
