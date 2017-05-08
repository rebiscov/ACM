#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <queue>

unsigned int s = 0, t = 37, graph[38][38], count = 0; /*Le sommet 0 est la source, de 1 à 26 cela représente les applications A à Z, de 27 à 36 les ordinateurs et 37 est t */

unsigned int char_to_int(char c){
  return c - 'A' + 1;
}

char int_to_char(unsigned int i){
  return i + 'A' - 1;
}

unsigned c_to_int(char c){
  return c - '0';
}

void init(void){
  unsigned int i, j;
  for (i = 0; i < 38; i++)
    for (j = 0; j < 38; j++)
      graph[i][j] = 0;
  
  for (i = 1; i <= 26; i++)
    graph[0][i] = 1;
  for (i = 27; i < 37; i++)
    graph[i][37] = 1;
}

void adjust(std::vector<unsigned int> &path){
  unsigned int min = graph[path[1]][path[0]];
  
  for(unsigned int i = 0; i < path.size() - 1; i++){
    if (graph[path[i+1]][path[i]] < min)
      min = graph[path[i+1]][path[i]];
  }
  for(unsigned int i = 0; i < path.size() - 1; i++){
    graph[path[i+1]][path[i]] -= min;
    graph[path[i]][path[i+1]] += min;
  }
  count += min;
}

bool bfs(){
  unsigned int u;
  std::queue<unsigned int> q;
  std::vector<bool> seen(38, false);
  std::vector<int> pred(38, -1);
  std::vector<unsigned int> path;

  q.push(0); seen[0] = true;
  pred[0] = 0;

  while(!q.empty()){
    u = q.front();
    q.pop();
    for (unsigned int i = 0; i < 38; i++){
      if (!seen[i] && graph[u][i] > 0){
	seen[i] = true;
	q.push(i);
	pred[i] = u;
      }
    }
  }

  if (!seen[37])
    return false;

 u = 37;
  while(pred[u] != u){
    path.push_back(u);
    u = pred[u];
  }
  path.push_back(0);
  adjust(path);

  return true;
}

void print_answer(void){
  unsigned int i, j;
  for (i = 27; i < 37; i++){
    for (j = 1; j < 27; j++){
      if (graph[i][j] == 1){
	printf("%c", int_to_char(j));
	break;
      }
    }
    if (j == 27)
      printf("_");
  }
  printf("\n");
}

int main(void){
  char *input = NULL;
  unsigned int n, task, nb_tasks, j, comp, tot;
  size_t len;

  input = (char*)malloc(sizeof(char)*100);
  init();
  getline(&input, &len, stdin);    


  do{
    count = 0; tot = 0;
    do{
      task = char_to_int(input[0]);
      nb_tasks = c_to_int(input[1]);
      tot += nb_tasks;
      graph[0][task] = nb_tasks;
      j = 3;
      while (input[j] != ';'){
	comp = c_to_int(input[j]) + 27;
	graph[task][comp] = 1;
	j++;
      }
      
    }while (getline(&input, &len, stdin) > 0 && input[0] != '\n');

    while(bfs());
    if (tot != count){
      printf("!\n");
    }
    else{
      print_answer();
    }
    
    init();
  } while (getline(&input, &len, stdin) > 0);

  return 0;
}
