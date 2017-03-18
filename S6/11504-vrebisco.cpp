#include <cstdio>
#include <vector>

std::vector<int> graph[100000];
bool seen[100000];
int end[100000];
int vertices_in[100000];
unsigned int t, nb;

void dfs(unsigned int n, unsigned int m, unsigned int u, bool b){
  unsigned int i, v;
  nb++;
  seen[u] = true;

  for (i = 0; i < graph[u].size(); i++){
    v = graph[u][i];
    if (!seen[v]){
      dfs(n, m, v, b);
    }
  }
  if (b)
    end[t++] = u;
}

int main(void){
  unsigned int n, m, i, j, cases, u, v, count;

  scanf("%d", &cases);

  for (i = 0; i < cases; i++){
    count = 0;
    scanf("%u %u", &n, &m);
    for (j = 0; j < n; j++){
      graph[j].clear();
      vertices_in[j] = 0;
      seen[j] = false;
    }

    
    for (j = 0; j < m; j++){
      scanf("%u %u", &u, &v);
      u--; v--;
      graph[u].push_back(v);
      vertices_in[v]++;
    }
    t = 0;
    
    for (j = 0; j < n; j++){
      if (!seen[j])
	dfs(n, m, j, true);
    }
    for (j = 0; j < n; j++)
      seen[j] = false;
    t--;
    nb = 0; count = 0;
    for (j = t; j >= 0; j--){
      if (!seen[end[j]]){
	dfs(n, m, end[j], false);
	count++;
      }
      if (nb == n)
	break;
    }
    
    
    printf("%u\n", count);
  }
  
  return 0;
}
