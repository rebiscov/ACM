#include <cstdio>
#include <vector>
#include <stack>
#include <utility>

void print_stack(std::stack<unsigned int> s){
  printf("Stack: ");
  while (!s.empty()){
    printf("%u ", s.top());
    s.pop();
  }
  printf("\n");
}

int main(void){
  unsigned int n, nb_n, u, v;

  scanf("%u", &n);
  while (n != 0){
    std::vector<std::vector<unsigned int>> graph(n);
    std::vector<bool> seen(n, false);
    std::vector<std::vector<bool>> edges(v, std::vector<bool>(n,false));
    for (unsigned int i = 0; i < n; i++){
      scanf("%u (%u)", &u, &nb_n);

      for (unsigned int j = 0; j < nb_n; j++){
	scanf("%u", &v);
	graph[u].push_back(v);
      }
    }
    printf("Fin entrée\n");

    std::stack<unsigned int> s;
    std::vector<std::pair<int,int>> e;
    std::pair<unsigned int, unsigned int> last_e;
    last_e.first = 0; last_e.second = 0;

    for(unsigned int j = 0; j < n; j++){
      printf("j = %u\n", j);
      if (!seen[j]){
	printf("push %u\n", j);
	s.push(j);
	
	while (!s.empty()){
	  unsigned int c_u = s.top();
	  s.pop();
	  
	  if (seen[c_u]){
	    s.pop();
	    continue;
	  }
	  seen[c_u] = true;
	  
	  for (unsigned int k = 0; k < graph[c_u].size(); k++){
	    print_stack(s);
	    printf("  k = %u\n", k);
	    printf("  c_u = %u\n", c_u);
	    if(!seen[graph[c_u][k]]){
	      printf("push parcours %u\n", graph[c_u][k]);
	      s.push(graph[c_u][k]);
	    }
	    
	    else if (!((graph[c_u][k] == last_e.first && c_u == last_e.second) || (graph[c_u][k] == last_e.second && last_e.first == c_u))){
	      std::stack<unsigned int> t;
	      unsigned int vert = graph[c_u][k];
	      printf("search for %u\n", graph[c_u][k]);
	      while (s.top() != graph[c_u][k]){
		printf("    +1\n");
		t.push(s.top());
		edges[s.top()][vert] = true;
		edges[vert][s.top()] = true;
		printf("    btop\n");
		vert = s.top();
		printf("    etop\n");
		s.pop();
		printf("    end\n");
		if (s.empty())
		  printf("! EMPTY !\n");
	      }
	      printf("yo\n");
	      while (!t.empty()){
		printf("    -1\n");
		s.push(t.top());
		t.pop();
	      }
	    }
	  }
	  if (!s.empty() && !edges[c_u][s.top()])
	    e.push_back(std::make_pair (c_u, s.top()));
	  last_e.first = c_u; last_e.second = s.top();
	  
	}
      }
    }

    scanf("%u", &n);
  }

  return 0;
}
