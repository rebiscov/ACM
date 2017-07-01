#include <cstdio>
#include <cmath>

bool p[1000001];

bool est_premier(long long int p){
  for (long long int i = 2; i <= sqrt(p) + 1; i++)
    if (p%i == 0)
      return false;
  return true;
}

void init(){
  p[0] = p[1] = false;
  p[2] = true;
  for (int i = 3; i < 1000001; i++)
    p[i] = est_premier(i);
}

long long int powint(long long int a, long long int b, long long int p){
  long long int temp;

  if (b == 0)
    return 1;
  else if (b % 2 == 0){
    temp = powint(a, b/2, p) %p;
    return (temp*temp)%p;
  }
  else{
    temp = powint(a, (b-1)/2, p)%p;
    return (temp*temp*a)%p;
  }
}

bool carmichael(long long int a, long long int p){
  return (powint(a, p-1, p)%p) == 1;
}

int main(void){ /* J'aurais pu faire l'algorithme du crible pour les nombres premiers mais c'est pas vraiment long long de calculer les nombres premiers entre 1 et 10^6 */
  long long int a, n1, n2, count;
  
  init();
  while (scanf("%ld %ld %ld", &a, &n1, &n2) > 0){
    count = 0;
    for (int i = n1; i <= n2; i++){
      if ((!p[i]) && carmichael(a, i))
	count++;
    }
    printf("%ld\n", count);
  }
  
  return 0;
}
