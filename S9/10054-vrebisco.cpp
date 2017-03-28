#include <cstdio>
#include <vector>

int graph[50][50];
unsigned int count;
bool seen[50];

bool parity(void){
  unsigned int n;
  
  for (unsigned int i = 0; i < 50; i++){
    n = 0;
    for (unsigned int j = 0; j < 50; j++){
      n += graph[i][j];
    }
    if (n%2 == 1)
      return false;
  }

  return true;
}

void dfs(unsigned int u){
  unsigned int v;
  seen[u] = true;
  count++;
  
  for (v = 0; v < 50; v++){
    if (!seen[v] && graph[u][v] > 0)
      dfs(v);
  }
}

void init(void){
  for (unsigned int i = 0; i < 50; i++){
    for (unsigned int j = 0; j < 50; j++)
      graph[i][j] = 0;
    seen[i] = false;
  }
}

void init_seen(void){
  for (unsigned int i = 0; i < 50; i++)
    seen[i] = false;
}

int main(void){
  unsigned int T, N, u, v, i, j, nb_beads;
  scanf("%u", &T);

  for (i = 0; i < T; i++){
    count = 0;
    
    if (!(i == 0))
      printf("\n");
    printf("Case #%d\n", i+1);
    
    scanf("%u", &N);
    init();
    nb_beads = 0;

    for (j = 0; j < N; j++){
      scanf("%u %u", &u, &v);
      u--; v--;
      graph[u][v] += 1;
      graph[v][u] += 1;

      if (!seen[u])
	nb_beads++;
      if (!seen[v])
	nb_beads++;
      seen[u] = true; seen[v] = true;
    }
    
    init_seen();
    dfs(0); /* We check if the graph is connected */

    if (nb_beads != count || !parity()){ /* parity checks if the graph can have an Eulerian tour */
      printf("some beads may be lost\n");
      continue;
    }

    printf("Wesh\n");

  }


  return 0;
}
