#include <cstdio>
#include <vector>
#include <cstring>
#include <time.h>

int measure (int x, int y, std::vector<int>const & tab){
  return tab[y] - tab[x-1];
}

void set(int x, int r, std::vector<int>& tab, int N){
  int correction = r - measure(x, x, tab);

  for (int i = x; i <= N; i++){
    tab[i] += correction;
  }
}

int main(void){
  int N, a, b, S, temp, count = 0;
  char entree[5];
  double time = clock();

  while(scanf("%d", &N)){
    if (N == 0) 
      break;
    if (count > 0)
      printf("\n");

    std::vector<int>tab(N+1,0);

    S = 0;
    for (int i = 1; i <= N; i++){
      scanf("%d", &temp);
      S += temp;
      tab[i] = S;
    }

    printf("Case %d:\n", ++count);

    scanf("%s", entree);
    while (strcmp(entree, "END") != 0 ) {
      scanf(" %d %d", &a, &b);
      
      if (strcmp(entree, "S") == 0)
	set(a, b, tab, N);
      else if (strcmp(entree, "M") == 0)
	printf("%d\n", measure(a, b, tab));
       else
 	printf("ERREUR ENTREE\n"); /* Normalement, vous ne verrez pas ce "else", ça me sert juste à debugger, mais il se peut que j'ai oublié de le retirer... */
       scanf("%s", entree);
    }
  }

  printf("\nTime: %f\n", (clock() - time)*(1.0/CLOCKS_PER_SEC));
  return 0;
}


