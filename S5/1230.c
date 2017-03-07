#include <stdlib.h>
#include <stdio.h>

int expo(int x, int y, int n){
  long int res = 0;

  if (y == 1)
    res = x%n;
  else if (y == 2)
    res = (x*x)%n;
  else if (y%2 == 0){ /* If y is even ...*/
    res = expo(x, y/2, n) %n;
    res *= res %n;
    res = res%n;
  }
  else{ /* If y is odd... */
    res = expo(x, (y-1)/2, n) %n;
    res *= res %n;
    res *= x%n;
    res = res%n;
  }

  return res;
}

int main(void){
  long int x, y, n, res;
  int cases, i; /* number of cases */

  scanf("%d", &cases);

  for (i = 0; i < cases; i++){
    scanf("%d %d %d", &x, &y, &n);
    printf("%d\n", expo(x, y, n));
  }
  
  
  return 0;
}
