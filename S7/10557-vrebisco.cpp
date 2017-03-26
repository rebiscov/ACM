#include <cstdio>
#include <vector>
#include <algorithm>

bool seen[100];
int energy[100];
int distances[100]; /* Distances from the first vertice */
std::vector<unsigned int> graph[100];

bool dfs(int u, int v){ /* Look if we can go to v from u by a depth-first search */
  if (u == v)
    return true;
  seen[u] = true;
  for (int i = 0; i < graph[u].size(); i++){
    if (!seen[graph[u][i]] && dfs(graph[u][i], v))
	return true;
  }
  return false;
}

int main(void){
  int n, i, j, k;
  bool c;
  
  scanf("%d", &n);
  while (n >= 0){
    
    for (i = 0; i < n; i++){ /* We get the graph */
      graph[i].clear();
      scanf("%d %d", &energy[i], &k);
      for (j = 0; j < k; j++){
	int v;
	scanf("%d", &v);
	graph[i].push_back(--v);
      }
    }

    distances[0] = 100;
    for (i = 1; i < n; i++)
      distances[i] = -1000000000; /* This is small enough to be -infinity */

    for (i = 0; i < n-1; i++){ /* Let's do Bellmond-Ford */
      for (j = 0; j < n; j++){
	for (k = 0; k < graph[j].size(); k++){
	  if (distances[j] <= 0)
	    continue;
	  distances[graph[j][k]] = std::max(distances[graph[j][k]], distances[j] + energy[graph[j][k]]);
	}
      }
    }

    if (distances[n-1] > 0){
      printf("winnable\n");
      scanf("%d", &n);
      continue;
    }
    
    c = false; /* Let's see if we can go to a cycle */
    for (i = 0; i < n; i++)
      seen[i] = false;
    
    for (i = 0; i < n; i++){
      if (distances[i] > 0){
	for (j = 0; j < graph[i].size(); j++){
	    c |= distances[i] + energy[graph[i][j]] > distances[graph[i][j]] && dfs(i, n-1);
	}
      }
    }

    if (distances[n-1] > 0 || c)
      printf("winnable\n");
    else
      printf("hopeless\n");

    scanf("%d", &n);
  }

  return 0;
}
