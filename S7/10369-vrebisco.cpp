#include <cstdio>
#include <cstdlib>
#include <vector>
#include <cmath>
#include <algorithm>

#define NB_VERTICES 500

typedef struct element element;
struct element{ /* This structure will be convinient for the union find */
  int x;
  int nb;
};

typedef struct coor {
  int x;
  int y;
} coor;

typedef struct edge {
  unsigned int u;
  unsigned int v;

  unsigned long int d; /*Distance between u and v. Well... Almost! */
} edge;


int cmp_edge(const void *a, const void *b){
  return ((edge*)a)->d - ((edge*)b)->d;
}

bool cmp_edge2(edge a, edge b){
  return a.d < b.d;
}

int find(int x, std::vector<element> &P){ /* We find, and compress the structure */
  int y;
  
  if (P[x].x == x)
    return x;
  else{
    y = find(P[x].x, P);
    P[x].x = y;
    
    return y;
  }
}

void unify(int a, int b, std::vector<element> &P){ /* We unify (a & b must be representants of their partitions */
  if (a == b)
    printf("x and y are already in the same partition\n");
  else if (P[a].nb > P[b].nb){
    P[b].x = a;
    P[a].nb += P[b].nb;
  }
  else{
    P[a].x = b;
    P[b].nb += P[a].nb;
  }
}

coor vertices[NB_VERTICES];
std::vector<edge> edges;
std::vector<element> Part;
std::vector<edge> tree;

int main(void){ /* Kruskal algorithm... again */
  long int N, S, P, a, b, i, j, k;
  edge e;
  element p;

  scanf("%d", &N);

  for (i = 0; i < N; i++){
    edges.clear();
    Part.clear();
    
    scanf("%d %d", &S, &P);
    
    for (j = 0; j < P; j++)
      scanf("%d %d", &vertices[j].x, &vertices[j].y);

    for (j = 0; j < P; j++){
      for (k = 0; k < j; k++){
	e.u = j; e.v = k; e.d = (vertices[j].x - vertices[k].x)*(vertices[j].x - vertices[k].x) + (vertices[j].y - vertices[k].y)*(vertices[j].y - vertices[k].y);
	edges.push_back(e);
      }
    }

    std::sort(edges.begin(), edges.end(), cmp_edge2);

    for (j = 0; j < edges.size(); j++){
      p.x = j; p.nb = 1;
      Part.push_back(p);
    }
    tree.clear();

    for (j = 0; j < edges.size(); j++){ /* Kruskal algorithm */
      a = find(edges[j].u, Part); b = find(edges[j].v, Part);
      if (a != b){
	tree.push_back(edges[j]);
	unify(a, b, Part);
      }
    }

    if (S > tree.size())
      printf("%.2f\n", 0.0);
    else if (S == 0) /* This case should never happen */
      printf("%.2f\n", sqrt((double)tree[tree.size()-1].d));
    else
      printf("%.2f\n", sqrt((double)tree[tree.size()-S].d));
  }
  
  return 0;
}
