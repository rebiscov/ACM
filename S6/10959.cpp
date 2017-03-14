#include <cstdio>
#include <queue>
#include <vector>

enum colors{
  WHITE,
  GREY,
  BLACK
};

int main(void){
  int nb_test_cases, P, D, i, j, k, u, v;
  std::vector<int> Persons[1000];
  colors colors[1000];
  std::queue<int> queue;

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
    while (!queue.empty()){
      u = queue.front();
      queue.pop();
      
      for (k = 0; k < Persons[u].size(); k++){
	if (colors[Persons[u][k]] == WHITE){
	  colors[Persons[u][k]] = GREY;
	  queue.push(Persons[u][k]);
	}
      }

      colors[u] = BLACK;
    }
    
  }
  

  return 0;
}
