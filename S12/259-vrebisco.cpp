#include <cstdio>
#include <vector>
#include <queue>

unsigned int s, t, n, count;

bool bfs(std::vector<std::vector<unsigned int>> &graph, std::vector<std::vector<unsigned int>> &b, std::vector<unsigned int> &path){
  unsigned int u;
  std::queue<unsigned int> q;
  std::vector<bool> seen(n, false);
  std::vector<int> pred(n, -1);

  q.push(s); seen[s] = true;
  pred[s] = s;

  while(!q.empty()){
    u = q.front();
    q.pop();
    for (unsigned int i = 0; i < graph[u].size(); i++){
      if (!seen[graph[u][i]] && b[u][graph[u][i]] > 0){
	seen[graph[u][i]] = true;
	q.push(graph[u][i]);
	pred[graph[u][i]] = u;
      }
    }
  }

  if (pred[t] == -1)
    return false;

  u = t;
  while(pred[u] != u){
    path.push_back(u);
    u = pred[u];
  }
  path.push_back(s);

  return true;
}

void adjust(std::vector<std::vector<unsigned int>> &graph, std::vector<std::vector<unsigned int>> &b, std::vector<unsigned int> &path){
  unsigned int min = b[path[1]][path[0]];
  for(unsigned int i = 0; i < path.size() - 1; i++){
    if (b[path[i+1]][path[i]] < min)
      min = b[path[i+1]][path[i]];
  }
  for(unsigned int i = 0; i < path.size() - 1; i++){
    b[path[i+1]][path[i]] -= min;
    b[path[i]][path[i+1]] += min;
  }
  count += min;
}

int main(void){
  unsigned int c, u, v, w, tests = 0;

  while(scanf("%u", &n) > 0 && n != 0){
    std::vector<std::vector<unsigned int>> graph(n);
    std::vector<std::vector<bool>> seen(n, std::vector<bool>(n, false));    
    std::vector<std::vector<unsigned int>> f(n, std::vector<unsigned int> (n, 0));
    std::vector<std::vector<unsigned int>> b(n, std::vector<unsigned int> (n, 0));
    count = 0;
    
    scanf("%u %u %u", &s, &t, &c);
    s--; t--;
    for (unsigned int i = 0; i < c; i++){
      scanf("%u %u %u", &u, &v, &w);
      u--; v--;
      if (!seen[u][v] && !seen[v][u]){
	graph[u].push_back(v);
	graph[v].push_back(u);	
      }
      seen[u][v] = true; seen[v][u] = true;
      b[u][v] += w;
      b[v][u] += w;
    }
    std::vector<unsigned int> path;
    while(bfs(graph, b, path)){
	adjust(graph, b, path);
	path.clear();
    }
    printf("Network %u\nThe bandwidth is %u.\n\n", ++tests, count);
  }
  
  return 0;
}
