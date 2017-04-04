#include <cstdio>
#include <vector>

long int m (long int a, long int b){
  if (a > b)
    return a;
  return b;
}

int main(void){
  long int n, temp, max;

  scanf("%d", &n);

  while (n != 0){
    std::vector<long int> bonbons(n+1, 0);
    for (int i = 0; i < n; i++){
      scanf("%ld", &temp);

      if (i > 0)
	bonbons[i+1] = temp + bonbons[i];
      else
	bonbons[i+1] = temp;
    }
    bonbons[0] = 0;

    max = bonbons[1];
    for (int i = 0; i <= n; i ++){
      for (int j = 0; j <= i; j++){
	max = m(max, bonbons[i] - bonbons[j]);
      }
    }
    
    if (max > 0)
      printf("Winning with %ld.\n", max);
    else
      printf("Loose.\n");

    scanf("%d", &n);
  }

  return 0;
}
