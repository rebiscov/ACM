 #include <cstdio>
#include <cstdlib>
#include <cstring>

char alph[27];
char dico[101][21];
char *text = NULL;
char trad[500];

void init(void){
  alph[0] = ' ';
  for (unsigned int i = 1; i < 27; i++)
    alph[i] = 'A'+i-1;
}

void traduction(int K){
  unsigned int k, len = strlen(text);
  strcpy(trad, text);
  for (unsigned int i = 0; i < len; i++){
    for (k = 0; k < 27 && text[i] != alph[k]; k++);
    trad[i] = alph[(k+K)%27];
  }
}

int count(unsigned int i){
  int n = 0;
  int len = 0;
  char buf[500];
  
  while (sscanf(trad+len, "%s", buf) > 0){
    len += strlen(buf)+1;
    for (unsigned int j = 0; j < i; j++){
      if (strcmp(dico[j], buf) == 0)
	n++;
    }
  }
  return n;
}

void print(void){
  int l = 0, c = 0;
  int len = strlen(trad);
  
  for (unsigned k = 0; k < len; k++){
    if (trad[k] == ' ')
      l = k;
    
    if (c == 60){
      c = 0;
      trad[l] = '\n';
      k = l;
    }
    c++;
  }
  printf("%s\n", trad);
}

int main(void){
  unsigned int i = 0, j = 0, max = 0;
  int K;
  size_t len;

  init();
  text = (char*)calloc(500, sizeof(char));


  while (getline(&text, &len, stdin) > 0 && strcmp(text, "#\n") != 0){
    text[strlen(text)-1] = '\0';
    strcpy(dico[i], text);
    i++;
  }

  getline(&text, &len, stdin);
  int l = strlen(text);
  
  if (text[l-1] == '\n')
    text[l-1] = '\0';

  for (int k = 0; k < 27; k++){
    traduction(k);
    int m = count(i);
    if (m > max){
      K = k;
      max = m;
    }
  }

  traduction(K);
  l = strlen(trad);
  if (trad[l-1] == ' ')
    trad[l-1] = '\0';

  print();
  
  return 0;
}
