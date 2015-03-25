
#include <stdio.h>

#define N_MAX 255
#define CLEAR '$'

typedef struct{
  char *ptr[2];
  int min_rank; /* 1:'-','+'; 2:'*','/'; 3:'n' */
  char op[2];
} Piece;


int is_op(char c){
  return c == '-' || c == '+' || c == '*' || c == '/';
}


int main(){
  Piece arr[N_MAX/2];
  Piece w_p, *arr_p;
  char str[N_MAX];
  char c, c0, c1, *str_p, *str_p_cur;
  int test, T, arr_n, mr;
  int unneeded;
  
  scanf("%d",&T);
  for(test = 0; test < T; test++){
    arr_p = arr;
    arr_n = 0;
    scanf("%s",str);
    for(str_p = str; *str_p != '\0'; ++str_p){
      switch(*str_p){
        case '(':
          if(arr_n != 0) ++arr_p;
          ++arr_n;
          
          if(str_p != str){
            c = *(str_p-1);
            arr_p->op[0] = is_op(c) ? c : 'n';
          }else{
            arr_p->op[0] = 'n';
          }
          arr_p->ptr[0] = str_p;
          arr_p->min_rank = 3;
          break;
        
        case ')':
          arr_p->ptr[1] = str_p;
          c = *(str_p+1);
          arr_p->op[1] = is_op(c) ? c : 'n';
          if(arr_p != arr){
            --arr_p;
          }
          break;
          
        case '+':
        case '-':
          if(arr_p->min_rank > 1) arr_p->min_rank = 1;
          break;
        
        case '*':
        case '/':
          if(arr_p->min_rank > 2) arr_p->min_rank = 2;
          break;
      } 
    }
  
    for(arr_p = arr; arr_p < arr+arr_n; ++arr_p){
      unneeded = 1;
      mr = arr_p->min_rank;
      c0 = arr_p->op[0];
      c1 = arr_p->op[1];
      if((c0 == '-' || c0 == '*') && mr == 1  || 
          c0 == '/' && mr != 3 || 
         (c1 == '*' || c1 == '/') && mr == 1) unneeded = 0;
      if(unneeded){
        *(arr_p->ptr[0]) = CLEAR;
        *(arr_p->ptr[1]) = CLEAR;
      }
    }
    
    str_p = str_p_cur = str;
    while(*str_p != '\0'){
      if(*str_p != CLEAR){
        *str_p_cur++ = *str_p; 
      }
      str_p++;
    }
    *str_p_cur = '\0'; 
    printf("%s\n",str);
    
  }
  return 0;
}