#include <stdlib.h>
#include <stdio.h>

long int gcd_function(long int a, long int b){ /* Sooo classic */
  long int temp;
  while (b != 0){
    temp = b;
    b = a%b;
    a = temp;
  }
  return a;
}

int main(void){
  long int ai, max, temp, gcd;
  int i, j, k, t, c;

  scanf("%d", &t);

  for (i = 0; i < t; i++){
    max = 0; ai = 0; gcd = 0;

    scanf("%d", &c);

    for (j = 0; j < c; j++){
      for (k = 0; k < 9; k++){
	scanf("%d", &temp);
	ai += temp;
      }
      scanf("%d", &temp);
      if (temp > max)
	max = temp;
      ai -= temp;
      if (ai < 0)
	ai = -ai;
      gcd = gcd_function(gcd, ai);
    }
    if (gcd == 1 || gcd == 0 || max >= gcd)
      printf("impossible\n");
    else
      printf("%d\n", gcd);
  }

  return 0;
}
