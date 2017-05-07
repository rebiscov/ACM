#include <cstdio>
#include <vector>
#include <queue>

unsigned int s, t, n;

void bfs(std::vector<std::vector<unsigned int>> &graph, std::vector<std::vector<unsigned int>> &b, std::vector<unsigned int> &path){
  unsigned int u;
  std::queue<unsigned int> q;
  std::vector<bool> seen(n, false);
  std::vector<unsigned int> pred(n, 0);

  q.push(s); seen[s] = true;
  pred[s] = s;

  while(!q.empty()){
    u = q.back();
    q.pop();
    for (unsigned int i = 0; i < graph[u].size(); i++){
      if (!seen[graph[u][i]] && b[u][graph[u][i]] > 0){
	seen[graph[u][i]] = true;
	q.push(graph[u][i]);
	pred[graph[u][i]] = u;
      }
    }
  }

  u = t;
  while(pred[u] != u){
    path.push_back(u);
    u = pred[u];
  }
  path.push_back(s);

  for (unsigned int i = 0; i < path.size(); i++)
    printf("%u ", path[i]+1);
  printf("\n");
}

int main(void){
  unsigned int c, u, v, w;

  while(scanf("%u", &n) > 0 && n != 0){
    std::vector<std::vector<unsigned int>> graph(n);
    std::vector<std::vector<unsigned int>> f(n, std::vector<unsigned int> (n, 0));
    std::vector<std::vector<unsigned int>> b(n, std::vector<unsigned int> (n, 0));
    
    scanf("%u %u %u", &s, &t, &c);
    s--; t--;
    for (unsigned int i = 0; i < c; i++){
      scanf("%u %u %u", &u, &v, &w);
      u--; v--;
      graph[u].push_back(v);
      graph[v].push_back(u);
      b[u][v] = b[v][u] = w;
    }
    std::vector<unsigned int> path;
    bfs(graph, b, path);
    
  }
  
  return 0;
}
