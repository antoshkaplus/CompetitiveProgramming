
int main(){
  char (*t)[2];
  char y[2];
  t = &y;
  (*t)[0];
  return 0;
}