#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print(char c, unsigned int n){
  for (unsigned int i = 0; i < n; i++)
    printf("%c", c);
}

int main(void){
  char seq_com[100], c, buf[5];
  unsigned int n;

  scanf("%u", &n);

  for (unsigned int i = 0; i < n; i++){
    printf("Case %u: ", i+1);
    scanf("%s", seq_com);
    unsigned int j = 0;
    
    while (seq_com[j] != '\0'){
      unsigned int k = j + 1;
      c = seq_com[j];
      
      while (seq_com[k] != 'A' && seq_com[k] != 'G' && seq_com[k] != 'T' && seq_com[k] != 'C' && seq_com[k] != '\0' && seq_com[k] !=  '\n')
	k++;

      
      unsigned int l;
      for (l = j+1; l < k; l++){
	buf[l-j-1] = seq_com[l];
      }

      buf[l-j-1] = '\0';

      print(c, atoi(buf));
      j = k;
    }
    printf("\n");
  }
  

  return 0;
}
