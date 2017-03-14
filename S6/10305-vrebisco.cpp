#include <cstdio>
#include <vector>
#include <stack>

enum colors{
  WHITE,
  GREY,
  BLACK
};

std::vector<unsigned int> tasks[100];
std::stack<unsigned int> stack;
colors colors[100];

void dfs(unsigned int n, unsigned int m, unsigned int u){
  unsigned int i, v;
  colors[u] = GREY;
  for (i = 0; i < tasks[u].size(); i++){
    v = tasks[u][i];
    if (colors[v] == WHITE){
      dfs(n, m, v);
    }
  }
  stack.push(u);
}

int main(void){
  unsigned int n, m, i, j, k, u, v;


  while(true){
    scanf("%u %u", &n, &m);
    if (n == 0 && m == 0)
      break;

    for (i = 0; i < 100; i++){
      tasks[i].clear();
      colors[i] = WHITE;
    }

    for (i = 0; i < m; i++){
      scanf("%u %u", &u, &v);
      u--; v--;
      tasks[u].push_back(v);
    }
    
    for (i = 0; i < n; i++){
      if (colors[i] == WHITE)
	dfs(n, m, i);
    }

    printf("%d", stack.top()+1);
    stack.pop();
    while(!stack.empty()){
      printf(" %d", stack.top()+1);
      stack.pop();
    }
    printf("\n");
  }

  return 0;
}
