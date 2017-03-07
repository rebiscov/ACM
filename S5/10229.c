#include <stdlib.h>
#include <stdio.h>

void print_matrix(int matrix[2][2]){
  int i, j;

  for (i = 0; i < 2; i++){
    for (j = 0; j < 2; j++){
      printf("%d ", matrix[i][j]);
    } 
    printf("\n");
  } 
}

void mult(int matrix[2][2], int matrix2[2][2], int m){
  int m00, m01, m10, m11; 

  m00 = matrix[0][0]*matrix2[0][0] + matrix[0][1]*matrix2[1][0];
  m01 = matrix[0][0]*matrix2[0][1] + matrix[0][1]*matrix2[1][1];
  m10 = matrix[1][0]*matrix2[0][0] + matrix[1][1]*matrix2[1][0];
  m11 = matrix[1][0]*matrix2[0][1] + matrix[1][1]*matrix2[1][1];

  matrix[0][0] = m00;
  matrix[0][1] = m01;
  matrix[1][0] = m10;
  matrix[1][1] = m11;
}

void expo(int matrix[2][2], int matrix2[2][2], int n, int m){
   int i, j;

   if (n == 1 || n == 2){ 
     for (i = 0; i < 2; i++) 
       for (j = 0; j < 2; j++) 
	 matrix2[i][j] = i|j; 
     if (n == 2) 
       mult(matrix2, matrix2, m); 
   } 
     
   else if (n%2 == 0){ /* n is even... */
     expo(matrix, matrix2, n/2, m); 
     mult(matrix2, matrix2, m); 
   } 
   else{ /* n is odd... */
     expo(matrix, matrix2, (n-1)/2, m); 
     mult(matrix2, matrix2, m); 
     mult(matrix2, matrix, m); 
   } 
}

int main(void){
  int matrix[2][2], matrix2[2][2];
  int n, m, i, j;
  
  while(scanf("%d %d", &n, &m)){
    for (i = 0; i < 2; i++){
      for (j = 0; j < 2; j++){
	matrix[i][j] = i|j;
	matrix2[i][j] = i|j;
      }
    }
    if (n == 0)
      printf("0\n");
    else{
      expo(matrix, matrix2, n, m);
      printf("%d\n", matrix2[1][0]);
    }
  }

  return 0;
}
