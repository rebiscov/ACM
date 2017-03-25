#include <cstdio>
#include <queue>
#include <vector>

enum colors{
  WHITE,
  GREY,
  BLACK
};

int main(void){
  int nb_test_cases, P, D, i, j, k, u, v, d[1000];
  std::vector<int> Persons[1000];
  colors colors[1000];
  std::queue<int> queue;

  d[0] = 0;

  scanf("%d", &nb_test_cases);

  for (i = 0; i < nb_test_cases; i++){
    for (j = 0; j < 1000; j++){
      Persons[j].clear();
      colors[j] = WHITE;
    }
    
    scanf("%d %d", &P, &D);
    for (j = 0; j < D; j++){ /* We store our graph */
      scanf("%d %d", &u, &v);
      Persons[u].push_back(v);
      Persons[v].push_back(u);
    }

    queue.push(0);
    while (!queue.empty()){ /* BFS */
      u = queue.front();
      queue.pop();
      
      for (k = 0; k < Persons[u].size(); k++){
	v = Persons[u][k];
	if (colors[v] == WHITE){
	  colors[v] = GREY;
	  queue.push(v);
	  d[v] = d[u] + 1;
	}
      }

      colors[u] = BLACK;
    }

    for (j = 1; j < P; j++){
      printf("%d\n", d[j]);
    }
    if (i < nb_test_cases -1)
      printf("\n");
  }
  

  return 0;
}
