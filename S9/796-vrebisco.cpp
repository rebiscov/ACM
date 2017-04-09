#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <set>

using namespace std;

vector<vector<int>> adj;
vector<int> visited, low, parents;
set<pair<int,int> > ans;
int num, N;

void dfs(int u){
  visited[u] = low[u] = num++;
  for(int i =0; i < adj[u].size(); i++){
    int v = adj[u][i];
    if(visited[v] == -1){
      parents[v] = u;
      dfs(v);
      low[u] = min(low[v], low[u]);
      if(low[v] > visited[u]){
	int s = u, t = v;
	if(s > t){
	  int temp = s;
	  s = t;
	  t = temp;
	}
	ans.insert(make_pair(s,t));
      }
    } else if(parents[u] != v){
      low[u] = min(visited[v], low[u]);
    }
  }
}

int main(void){
  while(scanf("%d", &N) != EOF){
    num = 0;
    ans.clear();
    adj = vector<vector<int>>(N);
    for(int i = 0; i < N; i++){
      int u, p;
      scanf("%d (%d)", &u, &p);
      for(int j = 0; j < p; j++){
	int v;
	scanf(" %d", &v);
	adj[u].push_back(v);
	adj[v].push_back(u);
      }
    }
    visited.clear();
    low.clear();
    parents.clear();
    for(int i = 0; i < N; i++){
      visited[i] = -1;
      low[i] = -1;
      parents[i] = -1;
    }
    for(int i=0; i < N; i++){
      if(visited[i] == -1){
	dfs(i);
      }
    }
    int nb = ans.size();
    set<pair<int, int>>::iterator it;
    printf("%d critical links\n", nb);
    for(it = ans.begin(); it != ans.end(); it++){
      printf("%d - %d\n", it->first, it->second);
    }
    printf("\n");
  }
  return 0;
}
