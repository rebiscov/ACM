#include <cstdio>
#include <vector>
#include <cstring>
#include <cmath>

/* ATTENTION: je ne savais pas qu'il fallait implémenter un arbre de Fenwick, j'ai donc ``inventé'' une structure de donné (un arbre) qui fait le job */
/* En effet, celle-ci réalise les opérations en O(log(n)) */

/* On va faire un arbre dont les feuilles sont les sommes partielles Si = R1+...+Ri */
/* Les noeuds correspondront à des corrections que l'on effectuera lorque que l'on modifiera la valeur d'une variable */
/* Ainsi, toutes les opérations se feront en O(log(n)), on atteindra une complexité en O(nlog(n)) plutôt que O(n^2) avec la méthode naïve */
/* Elle est pas belle la vie ? */

int reverse_bit(int x); /* Fonction qui prend un entier binaire, par exemple 1101 et renvoie cette entier retourné, ici 1011 */

int get_x(int x, std::vector<long int>const & tree){ /* Cette fonction va chercher la valeur de Sx dans l'arbre */
  int prof = (int)log2(tree.size()) - 1, Sx = 0, vertice = pow(2, prof) - 1 + x;

  if (x == 0)
    return 0;
  
  for (int i = 0; i < prof; i ++){
    Sx += tree[vertice];
    vertice /= 2;
  }

  return Sx;
}

int measure(int x, int y, std::vector<long int>const & tree){ /* x et y sont les résistances */
  int Sx, Sy; /* Sx contiendra la somme partielle jusqu'à x-1 et Sy la somme partielle jusqu'à y */

  Sx = get_x(x-1, tree);
  Sy = get_x(y, tree);
  
  return Sy - Sx;
}

void set(int x, int r, std::vector<long int>& tree){
  int prof = (int)log2(tree.size()) - 1, vertice = 1, correction;

  correction = r - measure(x, x, tree);

  x = pow(2, prof) + x - 1;
  x = (reverse_bit(x) >> 1);
  for (int i = 0; i < prof; i++){

    if (x & 1 == 1)
      vertice = 2*vertice + 1;
    else{
      vertice = 2*vertice;
      tree[vertice+1] += correction;
    }
    x = x >> 1;
  }
  tree[vertice] += correction;
}

int main(void){
  int N, a, b, start, S, temp, count = 0;
  char entree[5];

  while(scanf("%d", &N)){
    if (N == 0) 
      break;
    if (count > 0)
      printf("\n");    

    printf("Case %d:\n", ++count);
    std::vector<long int>tree(2*pow(2,ceil(log2(N))), 0); /* La case 0 ne sera pas utilisé */
    start = pow(2, ceil(log2(N)));

    S = 0;
    for(int i = 0; i < N; i++){
      scanf("%d", &temp);
      S += temp;
      tree[start + i] = S;
    }

    scanf("%s", entree);
    while (strcmp(entree, "END") != 0 ) {
      scanf(" %d %d", &a, &b);
      
      if (strcmp(entree, "S") == 0){
	set(a, b, tree);
      }
      else if (strcmp(entree, "M") == 0)
	printf("%d\n", measure(a, b, tree));
       else
 	printf("ERREUR ENTREE\n"); /* Normalement, vous ne verrez pas ce "else", ça me sert juste à debugger, mais il se peut que j'ai oublié de le retirer... */
       scanf("%s", entree);
    }
  }

  return 0;
}

int reverse_bit(int x){
  int y = 0;
  while (x != 0){
    y += (x & 1);
    x = x >> 1;
    y = y << 1;
  }
  return (y >> 1);
}
