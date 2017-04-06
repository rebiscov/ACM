#include <cstdio>
#include <vector>
#include <queue>

unsigned int graph[50][50];
unsigned int count;
bool seen[50];
std::queue<unsigned int> q;

bool has_n(unsigned int u){ /* true if u has a neighbour */
  for (unsigned i = 0; i < 50; i++)
    if (graph[u][i] > 0)
      return true;
  return false;
}

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

void eulerian_tour (unsigned int u){
  unsigned int i, v = u;
  std::queue<unsigned int> s;

  do{
    for (i = 0; i < 50; i++) /* We search a tour */
      if (graph[v][i] > 0){
	graph[v][i]--;
	graph[i][v]--;
	v = i;
	s.push(v);
	break;
      }
  } while (u != v);

  while (!s.empty()){
    unsigned int a;
    a = s.front();
    s.pop();
    printf("%u ", a+1);
    q.push(a+1);
    if (has_n(a))
      eulerian_tour(a);
  }
}

int main(void){
  unsigned int T, N, u, v, i, j, nb_beads;
  scanf("%u", &T);

  for (i = 0; i < T; i++){
    count = 0;
    
    if (i != 0)
      printf("\n");
    printf("Case #%d\n", i+1);
    
    scanf("%u", &N);
    init(); /* We initialise boolean array seen to false and the matrix of the graph to 0 */
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
    count = 0;
    dfs(0); /* We check if the graph is connected */

    if (nb_beads != count || !parity()){ /* parity checks if the graph can have an Eulerian tour */
      printf("some beads may be lost\n");
      continue;
    }


    printf("1 ");
    q.push(1);
    eulerian_tour(0);
    printf("\n");
    while (!q.empty()){
      unsigned int beta = q.front();
      q.pop();
      printf("%u ", beta);
    }
    printf("\n");
    
  }


  return 0;
}
