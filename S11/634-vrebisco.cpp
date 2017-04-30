#include <cstdio>
#include <vector>

struct point{
  int x;
  int y;
};

bool in_polygon(std::vector<struct point> &polygon, struct point P){
  unsigned int count, i, j;
  for (j = polygon.size() - 1, i = 0; i < polygon.size(); j = i++){
    if ((P.y - polygon[i].y)*(P.y - polygon[j].y) <= 0 && P.x <= polygon[i].x && P.x <= polygon[j].x)
      count++;
  }
  return count & 1;
}

int main(void){ /* Let's try the ray casting algorithm */
  unsigned int N;
  struct point P;

  while (scanf("%u", &N) > 0 && N){
    std::vector<point> polygon;
    for (unsigned int i = 0; i < N; i++){
      scanf("%d %d", &P.x, &P.y);
      polygon.push_back(P);
    }
    scanf("%d %d", &P.x, &P.y);
    in_polygon(polygon, P) ? printf("T\n"): printf("F\n");
  }

  return 0;
}
