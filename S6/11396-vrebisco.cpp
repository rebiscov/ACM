#include <cstdio>
#include <vector>

enum colors{
  WHITE,
  GREY,
  BLACK
};

enum colors_aux{
  BLANK,
  BLUE,
  RED
};

std::vector<unsigned int> graph[300];
colors colors[300];
int colors_aux[300];

int oppose(int colors){
  if (colors == BLUE)
    return RED;
  else if (colors == RED)
    return BLUE;
  else
    return BLANK;
}

int dfs(unsigned int n, unsigned int m, unsigned int u, int color){
  unsigned int i, v;
  int color_opp = oppose(color);
  
  colors[u] = GREY;
  for (i = 0; i < graph[u].size(); i++){
    v = graph[u][i];
    if (colors_aux[v] == color)
      return 1;
    else
      colors_aux[v] = color_opp;
    if (colors[v] == WHITE){
      dfs(n, m, v, oppose(color));
    }
  }

  return 0;
}

int main(void){
  unsigned int n, m, i, u, v, ret;


  while(true){
    scanf("%u %u", &n, &m);
    if (n == 0 && m == 0)
      break;

    for (i = 0; i < 100; i++){
      graph[i].clear();
      colors[i] = WHITE;
      colors_aux[i] = BLANK;
    }

    for (i = 0; i < m; i++){
      scanf("%u %u", &u, &v);
      u--; v--;
      graph[u].push_back(v);
    }

    dfs(n, m, 0, RED);    
    for (i = 1; i < n; i++){
      if (colors[i] == WHITE){
	ret = dfs(n, m, i, oppose(colors[graph[i][0]]));
	if (ret == 1){
	  break;
	}
      }
    }
    if (ret == 1)
      printf("NO\n");
    else
      printf("YES\n");


  }

  return 0;
}
