#include <stdlib.h>
#include <stdio.h>
#define SIZE 1000000

int tab[SIZE];

void affiche(void){
  int i;
  
  tab[0] = 1; tab[1] = 1;
  for (i = 2; i < SIZE; i++)
    if (tab[i] == 0)
      printf("%d est premier\n", i);
}

int find_next(int i){
  int j = i+1;
  while (tab[j] && j < SIZE)
    j++;
  if (j == SIZE)
    return -1;
  else
    return j;
}

void crible(void){
  int i = 2, j;
  while (i*i < SIZE){
    for (j = 2*i; j < SIZE; j +=i){
      tab[j] = 1;
    }
    i = find_next(i);
  }
}

int main(void){
  int i;
  for (i = 0; i < SIZE; i++){
    tab[i] = 0;
  }
  crible(); /* We now have a boolean array wich contains all the prime numbers between 2 and SIZE */

  

  return 0;
}
