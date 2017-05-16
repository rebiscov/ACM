#include <cstdio>
#include <cmath>

bool p[1000001];

bool est_premier(int p){
  for (int i = 2; i <= sqrt(p) + 1; i++)
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

int powint(int a, int b, int p){
  int res = 1;
  int n = 0;
  for (int i = 0; i < b; i++){
    res = (res*a)% p;
  }
  return res;
}

bool carmichael(int a, int p){
  return (powint(a, p-1, p)%p) == 1;
}

int main(void){ /* J'aurais pu faire l'algorithme du crible pour les nombres premiers mais c'est pas vraiment long de calculer les nombres premiers entre 1 et 10^6 */
  int a, n1, n2, count;
  bool b = false;
  
  init();
  while (scanf("%d %d %d", &a, &n1, &n2) > 0){
    count = 0;
    for (int i = n1; i <= n2; i++){
      if ((!p[i]) && carmichael(a, i))
	count++;
    }
    if (b)
      printf("\n");
    b = true;
    printf("%d", count);
  }
  
  return 0;
}
