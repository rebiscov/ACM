#include <cstdio>
#include <cstdlib>
#include <vector>
#include <algorithm>

struct point {
  int x, y;
};

bool cmp(struct point p1, struct point p2) {
  return (p2.x == p1.x) ? (p2.y < p1.y) : (p2.x < p1.x);
}
 
int eq_line(point c, point a, point b) {
  return (a.x - c.x) * (b.y - c.y) - (a.y - c.y) * (b.x - c.x);
}
 
std::vector<point> convex_hull(std::vector<point> & kingdom) {
  sort(kingdom.begin(), kingdom.end(), cmp);
  point CH[100];
  int m = 0;
  for (int i = 0; i < kingdom.size(); i++) {
    while (m >= 2 && eq_line(CH[m - 2], CH[m - 1], kingdom[i]) <= 0) {
      m--;
    }
    CH[m++] = kingdom[i];
  }
  for (int i = kingdom.size() - 2, t = m + 1; i >= 0; i--) {
    while (m >= t && eq_line(CH[m - 2], CH[m - 1], kingdom[i]) <= 0) {
      m--;
    }
    CH[m++] = kingdom[i];
  }
  return std::vector<point>(CH, CH + m);
}
 
int area(std::vector<point> & kingdom) {
  int sum = 0;
  for(int i = 1; i < kingdom.size(); i++) {
    sum += (kingdom[i - 1].x * kingdom[i].y) - (kingdom[i].x * kingdom[i - 1].y);
  }
  return sum;
}
 
bool in(point p, std::vector<point> & kingdom) {
  int sum = area(kingdom);
  for (int i = 1; i < kingdom.size() && sum >= 0; i++) {
    std::vector<point> temp;
    temp.push_back(p);
    temp.push_back(kingdom[i-1]);
    temp.push_back(kingdom[i]);
    temp.push_back(p);
    int temp_sum = area(temp);
    if (temp_sum < 0) {
      return false;
    }
    sum -= temp_sum;
  }
  return sum == 0;
}
 
int main(void) {
  std::vector<std::vector<point>> kingdoms;
  int n, x, y;
  
  while (scanf("%d", &n) && n != -1) {
    std::vector<point> k;
    for (int i = 0; i < n; i++) {
      scanf("%d %d", &x, &y);
      k.push_back((point){x, y});
    }
    kingdoms.push_back(convex_hull(k));
  }
  std::vector<bool> seen(kingdoms.size(), false);
  while (scanf("%d %d", &x, &y) == 2) {
    for (int i = 0; i < kingdoms.size(); i++) {
      if (!seen[i]) {
        seen[i] = in((point){x, y}, kingdoms[i]);
      }
    }
  }
  int ans = 0;
  for (int i = 0; i < kingdoms.size(); i++) {
    if (seen[i]) {
      ans += area(kingdoms[i]);
    }
  }
  printf("%.2lf\n", ans * 0.5);
  return 0;
}
