#include <cstdio>

void inter(const long eq1[3], const long eq2[3]){
  double res[2], det = eq1[0]*eq2[1] - eq1[1]*eq2[0];;

  res[0] = (1/det) * (eq1[2]*eq2[1] - eq2[2]*eq1[1]);
  res[1] = (1/det) * (eq2[2]*eq1[0] - eq1[2]*eq2[0]);

  printf("POINT %.2f %.2f\n", res[0], res[1]);
}

bool par(const long equation1[3], const long equation2[3]){
  return equation1[0]*equation2[1] == equation1[1]*equation2[0];
}

bool share (const long eq1[3], const long eq2[3], long point[2][2]){
  if ((eq1[0] * point[0][0] + eq1[1] * point[0][1] == eq1[2]) && (eq2[0] * point[0][0] + eq2[1] * point[0][1] == eq2[2]))
    printf("LINE\n");
  else
    printf("NONE\n");
}

void compute_equation(const long points[2][2], long equation[3]){ /* The equation of a line is ax + by = c */
  equation[0] = points[0][1] - points[1][1];
  equation[1] = points[1][0] - points[0][0];
  equation[2] = equation[0]*points[0][0] + equation[1]*points[0][1];
}

int main(void){
  long points1[2][2], points2[2][2], equation1[3], equation2[3];
  unsigned int N;

  printf("INTERSECTING LINES OUTPUT\n");

  scanf("%u", &N);

  for (unsigned int i = 0; i < N; i++){
    scanf("%ld %ld %ld %ld %ld %ld %ld %ld", &points1[0][0], &points1[0][1], &points1[1][0], &points1[1][1], &points2[0][0], &points2[0][1], &points2[1][0], &points2[1][1]);
    compute_equation(points1, equation1);
    compute_equation(points2, equation2);
    if (par(equation1, equation2)){
      share(equation1, equation2, points1);
    }
    else
      inter(equation1, equation2);

  }
  printf("END OF OUTPUT\n");
  
  return 0;
}
