#include <cstdio>
#include <vector>

typedef struct edge edge;
struct edge{
  int v;
  int w;
};

std::vector<edge> graph[100];
int dist[100];

int relax(int u, int v, int w){ /* The basic of a shortest path finder algorithm */
  if (dist[u] == -1)
    return dist[v];
  else if (dist[v] == -1 || dist[u] + w < dist[v])
    return dist[u] + w;
  else
    return dist[v];
}


int main(void){ 
  int nb_tests, N, M, E, T, i, j, k, l, u, count;
  edge e;

  scanf("%d", &nb_tests);

  for (i = 0 ; i < nb_tests; i++){
    scanf("%d %d %d %d", &N, &E, &T, &M);

    for (j = 0; j < N; j++){
      graph[j].clear();
      dist[j] = -1;  /* -1 stands for infinity */
    }
    dist[--E] = 0;

    for (j = 0; j < M; j++){
      scanf("%d %d %d", &e.v, &u, &e.w);
      u--; e.v--;
      graph[u].push_back(e); /* We want an a graph with inverted vertices, because we want distances from a destination, not a source */
    }
    
    for (j = 0; j < N-1; j++) /* We just apply the Bellmond-Ford algorithm (I could have done Dijkstra but is was longer to do... */
      for (k = 0; k < N; k++)
	for (l = 0; (unsigned int)l < graph[k].size(); l++)
	  dist[graph[k][l].v] = relax(k, graph[k][l].v, graph[k][l].w);

    count = 0;
    for (j = 0; j < N; j++)
      if (dist[j] != -1 && dist[j] <= T)
	count++;
    printf("%d\n", count);
    if (i != nb_tests-1)
      printf("\n");
  }

  return 0;
}
