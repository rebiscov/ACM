#include <cstdio>
#include <cstring>

bool test_fact(char s[], unsigned int len, unsigned int n){
  for (unsigned int i = 1; i < n/len; i++){
    for (unsigned int j = 0; j < len; j++){
      if (s[j] != s[j+i*len])
	return false;
    }
  }
  return true;
}

int main(void){
  char s[1000001];
  unsigned int n, ans;

  while (scanf("%s", s) > 0 && strcmp(s, ".") != 0){
    n = strlen(s);
    for (unsigned int i = 1; i < 1000001; i++){
      if (n%i == 0){
	if (test_fact(s, i, n)){
	  printf("%u\n", n/i);
	  break;
	}
      }
    }
  }

  return 0;
}
