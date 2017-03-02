#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

typedef struct element element;
struct element{
  int value;
  element *next;
};

typedef element* llist;

llist create(void);
void push(llist *list, int a);
int pop(llist *list);
void initialize (unsigned int *matrix, int N);
void read_input(char string[]);

int main(void){
  unsigned int N, i, j;
  unsigned int *matrix = NULL; /* where we will put our graph */
  unsigned int *visited = NULL; /* array to track which nodes were visited */
  char input[15];

  while (scanf("%d", &N)){
    matrix = malloc(sizeof(unsigned int)*pow(N,2)); /* Matrix of size N^2 */
    visited = malloc(sizeof(unsigned int)*N);
    
    initialize(matrix, pow(N,2)); /* We initialize our matrix with 0 everywhere */
    initialize(visited, N);

    fgets(input, 12, stdin); /* Emptying the input buffer */
    while(1){
      read_input(input); /* input contains the input entered by the user + \n */
      if (input[0] == '\n')
	break;
      i = atoi(strtok(input, "-")) - 1;
      j = atoi(strtok(NULL, "\n")) - 1;
      matrix[N*i+j] = 1;
      matrix[N*j+i] = 1;
    }
  }
  
  return 0;
}

/* Classic functions to handle lists */

llist create(void){ /* Create an empty list */
  llist list = NULL;

  return list;
}

void push(llist *list, int a){ /* Add an element at the top of the list */
  llist new_list = malloc(sizeof(element));

  new_list->value =  a;
  new_list->next = (*list);
  (*list) = new_list;
}

int pop(llist *list){ /* Remove and return the first element of the list, return -1 if the list is empty */
  int a;
  llist old_list = *list;
  if (list == NULL)
    return -1; /* our lists will only contain positive integers */
  else{
    a = (*list)->value;
    (*list) = (*list)->next;
    free(old_list);
    return a;
  }
}

void initialize(unsigned int *matrix, int N){
  int i;
  for (i = 0; i < N; i++)
    matrix[i] = 0;
}

/* I'm sick of scanf and fgets, I'm making my own function do read inputs with getchar */

void read_input(char string[]){
  int i = 0;
  do{
    string[i] = getchar();
    i++;
  } while (string[i-1] != '\n');
}
