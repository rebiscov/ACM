#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#define SIZE 1000000

int tab[SIZE];
long int *primes = NULL;
int nb_primes = 0;

long int log_b(long double x, long double b){ /* It computes logarithm in base b */
  long int res = (long int)(logl(x)/logl(b));
  return res;
}


void count_prime(void){
  int i;
  for (i = 0; i < SIZE; i++){
    if (tab[i] == 0)
      nb_primes++;
  }
}

void tab_primes(void){
  long int i, j = 0;

  count_prime();
  primes = malloc(sizeof(long int)*nb_primes);
  for (i = 0; i < SIZE; i++){
    if (tab[i] == 0){
      primes[j] = i;
      j++;
    }
  }
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

void crible(void){ /* Classical algorithm to find prime numbers */
  int i = 2, j;
  while (i*i < SIZE){
    for (j = 2*i; j < SIZE; j += i){
      tab[j] = 1;
    }
    i = find_next(i);
  }
}

long int count_p(long int p, long int low, long int high){ /* count the number of almost prime numbers with divisor p between low and high */
  long int m = log_b((long double)low, p), M = log_b((long double)high, p);

  if (M - m <= 0){
    return 0;
  }
  else
    return M - m - 1;
}

long int count(long int low, long int high){
  long int i;
  long int sum = 0;
  for (i = 0; /* primes[i]*primes[i] <= high */ i<nb_primes; i++){
    sum += count_p(primes[i], low, high);
  }
  
  return sum;
}

int main(void){
  int i, N;
  long int low, high;
  
  tab[0] = 1; tab[1] = 1;
  for (i = 2; i < SIZE; i++){
    tab[i] = 0;
  }
  crible(); /* We now have a boolean array wich contains all the prime numbers between 2 and SIZE */
  tab_primes(); /* Now we have an array with the prime numbers */


  scanf("%d", &N);

  for (i = 0; i < N; i++){
    scanf("%ld %ld", &low, &high);
    printf("%ld\n", count(low, high));
  }

  return 0;
}
