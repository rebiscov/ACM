#include <cstdio>
#include <vector>
#include <stack>
#include <utility>

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
	s.push(j);
	
	while (!s.empty()){
	  unsigned int c_u = s.top();
	  
	  if (seen[c_u]){
	    s.pop();
	    continue;
	  }
	  seen[c_u] = true;
	  
	  for (unsigned int k = 0; k < graph[c_u].size(); k++){
	    printf("  k = %u\n", k);
	    if(!seen[graph[c_u][k]])
	      s.push(graph[c_u][k]);
	    
	    else if (!((graph[c_u][k] == last_e.first && c_u == last_e.second) || (graph[c_u][k] == last_e.second && last_e.first == c_u))){
	      std::stack<unsigned int> t;
	      unsigned int vert = graph[c_u][k];
	      while (s.top() != graph[c_u][k]){
		printf("    +1\n");
		t.push(s.top());
		edges[s.top()][vert] = true;
		edges[vert][s.top()] = true;
		printf("    btop\n");
		vert = s.top();
		printf("    etop\n");
		s.pop();
	      }
	      while (!t.empty()){
		printf("    -1\n");
		s.push(t.top());
		t.pop();
	      }
	    }
	  }
	  unsigned int a = s.top();
	  s.pop();
	  if (!s.empty() && !edges[a][s.top()])
	    e.push_back(std::make_pair (a, s.top()));
	  
	}
      }
    }

    scanf("%u", &n);
  }

  return 0;
}
