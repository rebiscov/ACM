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

colors_aux oppose(colors_aux color){
  if (color == RED)
    return BLUE;
  else if (color == BLUE)
    return RED;
  else
    return BLANK;
}

std::vector<unsigned int> graph[300];
colors colors[300];
colors_aux colors_aux[300];

int dfs(unsigned int n, unsigned int u){ /* dfs */
  unsigned int i, v, ret = 0;

  colors[u] = GREY;
  for (i = 0; i < graph[u].size(); i++){
    v = graph[u][i];
    if (colors_aux[v] == colors_aux[u]){
      return 1;
    }
    else
      colors_aux[v] = oppose(colors_aux[u]);
    if (colors[v] == WHITE){
      ret = dfs(n, v) | ret;
      if (ret == 1)
	return 1;
    }
  }
  return ret;
}

int main(void){
  unsigned int n, i, u, v, ret;


  while(true){
    scanf("%u", &n);
    if (n == 0)
      break;
    ret = 0;

    for (i = 0; i < n; i++){
      graph[i].clear();
      colors[i] = WHITE;
      colors_aux[i] = BLANK;
    }

    scanf("%u %u", &u, &v);
    do{
      u--; v--;
      graph[u].push_back(v);
      graph[v].push_back(u);
      scanf("%u %u", &u, &v);
    }while (u != 0 && v != 0);
    
    for (i = 0; i < n; i++){ /* We try to do a two coloration of our graph */
      if (colors[i] == WHITE){
	colors_aux[i] = RED;
	ret = dfs(n, i);
	if (ret == 1)
	  break;
      }
    }
    if (ret == 1)
      printf("NO\n");
    else
      printf("YES\n");
  }

  return 0;
}
