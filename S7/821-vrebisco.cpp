#include <cstdio>
#include <vector>

int min(int a, int b){
  if (a >= b)
    return b;
  else
    return a;
}

int paths[100][100];

int main(void){ /* Let's do Floyd-Warshall algorithm */
  int N, u, v, i, j, k, test_cases = 1, n;
  double avg;

  while(1){
    scanf("%d %d", &u, &v);
    if (u == 0 && v == 0)
      break;

    for (i = 0; i < 100; i++)
      for (j = 0; j < 100; j++)
	(i == j) ? paths[i][j] = 0: paths[i][j] = 200; /* 200 stands for +infinity in our case, because there can not be a path than more than 99 edges (wt cycles) */    

    N = 0;
    
    do{
      if (u > N)
	N = u;
      if (v > N)
	N = v;
      
      paths[--u][--v] = 1;
      scanf("%d %d", &u, &v);
    } while (!(u == 0 && v ==0));    

    for (k = 0; k < N; k++){
      for (i = 0; i < N; i++){
	for (j = 0; j < N; j++){
	  paths[i][j] = min(paths[i][j], paths[i][k] + paths[k][j]);
	}
      }
    }

    avg = 0; n = N*N;
    for (i = 0; i < N; i++)
      for (j = 0; j < N; j++)
	(paths[i][j] == 200 || i == j) ? n--: avg += (double)paths[i][j];


    printf("Case %d: average length between pages = %.3f clicks\n", test_cases++, avg/(double)(n));
  }

  
  return 0;
}
