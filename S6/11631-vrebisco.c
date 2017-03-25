#include <stdlib.h>
#include <stdio.h>

typedef struct element element;
struct element{ /* This structure will be convinient for the union find */
  int x;
  int nb;
};

typedef struct edge edge;
struct edge{
  int u; /* u and v are vertices, w is the weight of the edge */
  int v;
  int w;
};

int cmp(const void *e1, const void *e2){
  return (*(edge*)e1).w - (*(edge*)e2).w;
}

int find(int x, element *P){ /* We find, and compress the structure */
  int y;
  
  if (P[x].x == x)
    return x;
  else{
    y = find(P[x].x, P);
    P[x].x = y;
    
    return y;
  }
}

void unify(int a, int b, element *P){ /* We unify (a & b must be representants of their partitions) */
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

int main(void){
  edge *E = NULL, e; /* P stands for partition, we're gonna do some union-find */
  element *P = NULL, p;
  int n, m, i, u, v, w, total, tree, a, b;

  while(scanf("%d %d", &m, &n)){
    if (n == 0 && m == 0)
      break;
    
    E = malloc(sizeof(edge)*n);
    P = malloc(sizeof(element)*m);
    total = 0;
    
    for (i = 0; i < n; i++){
      scanf("%d %d %d", &u, &v, &w);
      e.u = u; e.v = v; e.w = w; total += e.w;
      E[i] = e; /* E is the set of edges */
    }
    qsort(E, n, sizeof(edge), cmp); /* Gonna do the Kruskal algorithm, so we need to sort the edges */

    for (i = 0; i < m; i++){
      p.x = i; /* Here we store the father of the vertice i (union find structure) */
      p.nb = 1; /* Here we store the number of element in the partion, for now 1 */
      P[i] = p;
    }

    tree = 0;
    for (i = 0; i < n; i++){ /* The core of the algorithm */
      a = find(E[i].u, P); b = find(E[i].v, P); 
      if (a != b){ /* If u and v are not in the same partition, we unify the two partitions */
	tree += E[i].w;
	unify(a, b, P);
      }
    }

    printf("%d\n", total-tree);
    
    free(E);
    free(P);
  }

  return 0;
}
