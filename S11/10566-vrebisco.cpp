#include <cstdio>
#include <cmath>

double min(double a, double b){
  double res = a >= b ? b: a;
  return res;
}

int main(void){
  double x, y, c, low, high, est, c_p;


  while(scanf("%lf %lf %lf", &x, &y, &c) > 0){
    high = min(x, y);
    low = 0;
    do{
      est = (high + low) / 2;
      c_p = (sqrt(x*x-est*est) * sqrt(y*y-est*est)) / (sqrt(x*x-est*est) + sqrt(y*y-est*est));
      if (c_p < c)
	high = est;
      else
	low = est;
    }while (fabs(c_p - c) > 1e-10);
    
    printf("%.3lf\n", est);
    
  }

  return 0;
}
