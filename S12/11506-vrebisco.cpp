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
  unsigned int W, u, v, np, cost, up, vp;
  s = 0;

  while(scanf("%u %u", &n, &W) > 0 && n != 0 && W != 0){
    np = n;
    n = 2*n -1;
    std::vector<std::vector<unsigned int>> graph(n);
    std::vector<std::vector<unsigned int>> f(n, std::vector<unsigned int> (n, 0));
    std::vector<std::vector<unsigned int>> b(n, std::vector<unsigned int> (n, 0));
    count = 0;
    t = np-1;

    for (unsigned int i = 0; i < np-2; i++){
      scanf("%u %u", &u, &cost);
      u--;
      b[u][u+np] += cost;
      graph[u].push_back(u+np);
    }
    for (unsigned int i = 0; i < W; i++){
      scanf("%u %u %u", &u, &v, &cost);
      u--; v--;
      if (u != 0 && u != t)
	up = u + np;
      else
	up = u;
      
      if (v != 0 && v != t)
	vp = v + np;
      else
	vp = v;      
      graph[up].push_back(v);
      graph[vp].push_back(u);	
      b[up][v] += cost;
      b[vp][u] += cost;
    }
    std::vector<unsigned int> path;
    while(bfs(graph, b, path)){
	adjust(graph, b, path);
	path.clear();
    }
    printf("%u\n", count);
  }
  
  return 0;
}
