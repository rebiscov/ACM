#include <stdlib.h>
#include <stdio.h>

long int opt[100][100][100][100]; /* We're gonna do a dynamic programm, and here also called "brut-eforce with a fancy name" */
int N;

void affiche(void){
  int i, j;
  for (i = 0; i < N; i++){
    for (j = 0; j < N; j++){
      printf("%d ", opt[i][j][i][j]);
    }
    printf("\n");
  }
}

int main(void){
  int i, j, k, l;
  long int max = 0;
  
  scanf("%d", &N);
  
  for (i = 0; i < N; i++)
    for (j = 0; j < N; j++){
      scanf("%d", &opt[i][j][i][j]);
      if (max > opt[i][j][i][j])
	max = opt[i][j][i][j];
    }

  affiche();
  
  for (i = 0; i < N; i++){
    for (k = 0; k < N; k++){
      for (l = k + 1; l < N; l++){
	opt[i][k][i][l] = opt[i][k][i][l-1]+opt[i][l][i][l];
	if (max > opt[i][k][i][l])
	  max = opt[i][k][i][l];
      }
    }
  }

  for (i = 0; i < N; i++){
    for (j = i + 1; j < N; j++){
      for (k = 0; k < N; k++){
	for (l = k + 1; l < N; l++){
	  opt[i][k][j][l] = opt[i][k][j-1][l] + opt[j][k][j][l];
	  if (max > opt[i][k][j][l])
	    max = opt[i][k][j][l];
	}	
      }
    }
  }
  printf("%d\n", opt[1][0][3][1]);
  
  return 0;
}
