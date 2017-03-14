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

int dfs(unsigned int n, unsigned int u, int color){
  unsigned int i, v;
  int color_opp = oppose(color);
  printf("pere %u\n", u);
  
  colors[u] = GREY;
  for (i = 0; i < graph[u].size(); i++){
    printf("fils %d\n", i);
    v = graph[u][i];
    if (colors_aux[v] == color)
      return 1;
    else
      colors_aux[v] = color_opp;
    if (colors[v] == WHITE){
      dfs(n, v, oppose(color));
    }
  }

  return 0;
}

int main(void){
  unsigned int n, i, j, u, v, ret;


  while(true){
    scanf("%u", &n);
    if (n == 0)
      break;

    for (i = 0; i < 100; i++){
      graph[i].clear();
      colors[i] = WHITE;
      colors_aux[i] = BLANK;
    }

    do{
      scanf("%u %u", &u, &v);
      u--; v--;
      graph[u].push_back(v);
      graph[v].push_back(u);
    } while (u != 0 && v != 0);

    dfs(n, 0, RED);    
    for (i = 1; i < n; i++){
      printf("i = %d\n", i);
      if (colors[i] == WHITE){
	colors_aux[i] = RED;
	for (j = 0; j < graph[i].size(); j++){
	  v = graph[i][j];
	  if (colors_aux[v] != BLANK){
	    colors_aux[i] = oppose(colors_aux[v]);
	    break;
	  }
	}
	ret = dfs(n, u, colors_aux[i]);
	
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
