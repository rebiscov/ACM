#include <stdlib.h>
#include <stdio.h>

int opt[100][100][100][100]; /* We're gonna do a dynamic programm, and here also called "brute-force with a fancy name" */
/* opt[i][k][j][l] contains the sum of the rectangle with the top left corner of cordinate (i,k) and bottom right corner (j,l) */
int N;

int main(void){
  int i, j, k, l;
  int max;
  
  while (scanf("%d", &N) != EOF){
    max = 0;
    
    for (i = 0; i < N; i++)
      for (j = 0; j < N; j++){
	scanf("%d", &opt[i][j][i][j]);
	if (i == 0 && j == 0)
	  max = opt[i][j][i][j];
	else if (max < opt[i][j][i][j])
	  max = opt[i][j][i][j];
      }

  
    for (i = 0; i < N; i++){   /* Here we compute all the rectangles on a single line */
      for (k = 0; k < N; k++){
	for (l = k + 1; l < N; l++){
	  opt[i][k][i][l] = opt[i][k][i][l-1]+opt[i][l][i][l];
	  if (max < opt[i][k][i][l])
	    max = opt[i][k][i][l];
	}
      }
    }
    
    for (i = 0; i < N; i++){ /* Here we compute all the rectangles */
      for (j = i + 1; j < N; j++){
	for (k = 0; k < N; k++){
	  for (l = k + 1; l < N; l++){
	    opt[i][k][j][l] = opt[i][k][j-1][l] + opt[j][k][j][l];
	    if (max < opt[i][k][j][l])
	      max = opt[i][k][j][l];
	  }	
	}
      }
    }
    printf("%d\n", max);
  }
  
  return 0;
}
