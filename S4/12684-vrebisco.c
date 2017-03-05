#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

void initialize(unsigned int tab[], int N);
void affiche_m(unsigned int matrix[], int N);
int visit(unsigned int matrix[], unsigned int coloration[], int N, int vertice);

int main(void){
  size_t size = 15;
  int N, i, j, bool = 0;
  unsigned int *matrix = NULL; /* where we will put our graph */
  unsigned int *coloration = NULL; /* array to track which nodes have been colored */
  char *input;

  input = malloc(15*sizeof(char));

  while (getline(&input, &size, stdin) > 1){
    count++;
    if (bool)
      printf("\n");
    bool = 1;
    
    N = atoi(strtok(input, "\n"));
    matrix = malloc(sizeof(unsigned int)*pow(N,2)); /* Matrix of size N^2 */
    coloration = malloc(sizeof(unsigned int)*N);
  
    initialize(matrix, pow(N,2)); /* We initialize our matrix with 0 everywhere */
    initialize(coloration, N);

    /* fgets(input, 12, stdin); */ /* Emptying the input buffer */
    while(1){
      if (getline(&input, &size, stdin) < 1){ /* input contains the input entered by the user + \n */
	break;
      }
      if (input[0] == '\n')
	break;
      i = atoi(strtok(input, "-")) -1;
      j = atoi(strtok(NULL, "\n")) -1;
      if (i >= 0 && j >= 0){
	matrix[N*i+j] = 1;
	matrix[N*j+i] = 1;
      }
    }

    visit(matrix, coloration, N, 0);

    for (i = 0; i < N; i++){
      printf("%d %d\n", i+1, coloration[i]);
    }
    
    
    free(coloration);
    free(matrix);
  }

  return 0;
}

void initialize(unsigned int tab[], int N){
  int i;
  for (i = 0; i < N; i++)
    tab[i] = 0;
}

void affiche(unsigned int tab[], int N){
  int i;
  for (i = 0; i < N; i++){
    printf("%d ", tab[i]);
  }
  printf("\n");
}

/* Function wich visit a node */

int visit(unsigned int matrix[], unsigned int coloration[], int N, int vertice){
  int neighbour[5] = {0, 0, 0, 0, 0} , i;
  
  for (i = 0; i < N; i++){ /* We look the color of the neighbour */
    if (matrix[N*i+vertice])
      neighbour[coloration[i]] = 1;
  }

  for (i = 1; i < 5; i++){ /* We look which color are available */
    if (!neighbour[i]){
      coloration[vertice] = i;
  
      if (coloration[vertice] >  4){
	coloration[vertice] = 0;
	return -1; /* Coloration has failed */
      }
      
      else if (vertice == N-1) /* If we finished, return 0 (success */
	return 0;
      
      else{
	if (visit(matrix, coloration, N, vertice+1) == -1){ /* Else we visit the next vertice */
	  continue;
	}
	return 0;
      }
    }
  }
  
  coloration[i] = 0;
  return -1;
}
