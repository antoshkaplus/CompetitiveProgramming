#include <iostream>
#include <stdio.h>
#include <string.h>
#include <string>
#include <algorithm>
#include <stdlib.h>

using namespace std;

const int maxn=260, maxm=210;

struct Point
{
  int x,y,z;
  void init(){
    scanf("%d%d%d",&x,&y,&z);
  }

}a[maxn][maxm];

int aa[maxn],f[maxn];
int n;

void iin()
{
  int i,j,k,t;
  scanf("%d",&t);

  n=0;

  // read only Oxy faces
  for (;t--;){
    scanf("%d",aa+n);
    for (j=0;j<aa[n];j++) a[n][j].init();
  
    for (j=1;j<aa[n];j++) 
      if (a[n][j].z!=a[n][0].z) break;
  
    a[n][aa[n]]=a[n][0]; // end equal begin
    if (j==aa[n]) n++;
  }

  // sort Oxy faces by ascending
  for (i=0;i+1<n;i++){
    t=i;
    for (j=i+1;j<n;j++) if (a[t][0].z>a[j][0].z) t=j;
    
    if (t!=i){
      for (j=0;j<=aa[i]||j<=aa[t];j++) swap(a[i][j],a[t][j]); 
      swap(aa[i],aa[t]);
    }
  }
}

// area of face
int area(int i)
{
  int j, s=0;
  for(j=0;j<aa[i];j++) s+=a[i][j].x*a[i][j+1].y-a[i][j].y*a[i][j+1].x; // strange area....
  if(s>0) return s/2; 
  else return -s/2;
}

// work
void work()
{
  int v,s,h;
  int i,j,k;
  v=s=h=0;

  // go by faces
  for(i=0;i<n;i++)
  {
    // take POINT most near to Oy.. or near to Ox
    int t=0;
    for (j=1;j<aa[i];j++) 
      if ((a[i][j].y<a[i][t].y)||(a[i][j].y==a[i][t].y&&a[i][j].x<a[i][t].x)) 
        t=j;
    // init this POINT (x,y)
    int x=a[i][t].x,y=a[i][t].y;
    
    // negative sor positive area ????
    f[i]=1;
    
    // go by faces, that was before
    // define f[i] : positive or negative ...
    for (j=i-1;j>=0;j--) 
      if (a[j][0].z<a[i][0].z){ // if face was !!!lower!!! 
        int tot=0;
        for(k=0;k<aa[j];k++) // go by points of face 
          if(a[j][k].x==a[j][k+1].x) // if some points have equal x... segment (in fact)
            if(a[j][k].x>x)
              if((a[j][k].y>a[j][k+1].y&&a[j][k].y>y&&y>=a[j][k+1].y)|| // y between k and k+1  
                 (a[j][k+1].y>a[j][k].y&&a[j][k+1].y>y&&y>=a[j][k].y))
				// so i count number of segments , which have same x coord and it better than init one
				//        and y init coord between them.
                tot++;
        // if has remainder....
		if(tot%2){
          f[i]=-f[j];
          break;
        }
      }
    
    int dh=a[i][0].z-h;
    v+=s*dh; // s - past
    s+=f[i]*area(i);
    h=a[i][0].z;
    // don't use last area
  }

  printf("The bulk is composed of %d units.\n",v);
}

int main(){

  int cass;

  for (scanf("%d",&cass);cass--;){
    iin();
    work();
  }
  return 0;
}