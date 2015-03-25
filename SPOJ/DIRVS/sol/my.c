
#include <stdio.h>
#include <math.h>
#include <time.h>

#define DEBUG
#undef DEBUG

typedef struct{
  int r, c;
} Pair;


/* 3D line structure */
typedef struct{
  Pair p1, p2;
  double z1, z2;
} Line;


/* global variables */

#define sz_max 200

int Z[sz_max][sz_max]; /* heights of field */
int W[sz_max][sz_max]; /* matrix for maze problem solving algorithm */

Pair sz; /* size of field */
Pair bts[2];
Line ln; /* line which connect bts and technician */

/* pair functions */

Pair p_sum(Pair* p1, Pair* p2){
  Pair p = {p1->r + p2->r, p1->c + p2->c};
  return p;
}

Pair p_new(int r, int c){
  Pair p = {r, c};
  return p;
}

int p_in(Pair* p){
  return 0 <= p->r && p->r < sz.r && 0 <= p->c && p->c < sz.c; 
}

int p_get(int m[][sz_max], Pair* p){
  return m[p->r][p->c];
}

void p_set(int m[][sz_max], Pair* p, int val){
  m[p->r][p->c] = val;
}

int p_eq(Pair* p1, Pair* p2){
  return p1->r==p2->r && p1->c==p2->c; 
}

int p_mhtn_norm(Pair* p1, Pair* p2){
  return abs(p1->r-p2->r) + abs(p1->c-p2->c);
}

/* line functions */

void ln_init(Pair* p1, double z1, Pair* p2, double z2){
  ln.p1 = *p1; 
  ln.p2 = *p2;
  ln.z1 = z1;
  ln.z2 = z2;
}

double ln_z_by_r(double r){
  return (r-(ln.p1.r+0.5))*(ln.z2-ln.z1)/(double)(ln.p2.r-ln.p1.r) + ln.z1;
}

double ln_z_by_c(double c){
  return (c-(ln.p1.c+0.5))*(ln.z2-ln.z1)/(double)(ln.p2.c-ln.p1.c) + ln.z1;
}

double ln_rc_val(Pair* p){
  return (p->r-(ln.p1.r+0.5))*(ln.p2.c-ln.p1.c)-(p->c-(ln.p1.c+0.5))*(ln.p2.r-ln.p1.r);
}

int ln_rc_on_same_side(Pair *p1, Pair *p2){
  return ln_rc_val(p1)*ln_rc_val(p2) > 0;
}


/* queue for lee algorithm (push in front, pop from back) */
/* before using queue call q_clear function !!! */ 

#define q_sz_max 4*sz_max
Pair Q[q_sz_max]; /* queue memory */
int q_front, q_back, q_sz; /* q_back - index of last element */

int q_empty(){
  return !q_sz;
}

/* pushes before front */
void q_push(const Pair* p){
  Q[q_front--] = *p;
  ++q_sz;
  if(q_front < 0) q_front = q_sz_max-1;
}

void q_push_back(const Pair* p){
  q_back = q_back==q_sz_max-1 ? 0 : q_back+1;
  Q[q_back] = *p;
  ++q_sz;
}

void q_push_front(const Pair*p){
  q_push(p);
}

Pair q_pop(){
  Pair p = Q[q_back--];
  --q_sz;
  if(q_back < 0) q_back = q_sz_max-1; 
  return p;
}

void q_clear(){
  q_front = 0, q_back = 0, q_sz = 0; 
}

/* lee algorithm funcitons */ 

int can_go(Pair* p);

/* Pair : row,column */
int lee_algo(Pair* source, Pair* target){
  int i, j, v1, v2;
  Pair p, v, step[4] = {{1,0},{0,1},{-1,0},{0,-1}};
  /* initialize all cells like unvisited */
  for(i=0; i<sz.r; ++i){
    for(j=0; j<sz.c; ++j){
      W[i][j] = -1;
    }
  }
  q_clear();
  p_set(W,source,0);
  q_push(source);
  while(!q_empty()){
    p = q_pop();
    for(i=0; i<4; ++i){
      v = p_sum(step+i,&p);
      v1 = p_get(Z,&p); 
      v2 = p_get(Z,&v);
      #ifdef DEBUG
      printf("try: %d,%d\n",v.r,v.c);
      #endif
      if(p_in(&v) && p_get(W,&v)==-1 && (v1-v2 <= 3) && (v1-v2 >= -1) && can_go(&v)){
        
        #ifdef DEBUG
        printf("from: %d,%d go: %d,%d\n",p.r,p.c,v.r,v.c);
        #endif
        
        p_set(W,&v,p_get(W,&p)+1);
        q_push(&v);
        if(p_eq(&v,target)) break;
      }
    }
    if(p_eq(&v,target)) break;
  }
  #ifdef DEBUG
  printf("q: %d\n",q_empty());
  #endif
  return p_get(W,target);
}

int hadlock_algo(Pair* source, Pair* target){
  int i, j, v1, v2, res;
  Pair p, v, step[4] = {{1,0},{0,1},{-1,0},{0,-1}};
  /* initialize all cells like unvisited */
  for(i=0; i<sz.r; ++i){
    for(j=0; j<sz.c; ++j){
      W[i][j] = -1;
    }
  }
  q_clear();
  p_set(W,source,0);
  q_push(source);
  while(!q_empty()){
    p = q_pop();
    for(i=0; i<4; ++i){
      v = p_sum(step+i,&p);
      v1 = p_get(Z,&p); 
      v2 = p_get(Z,&v);
      if(p_in(&v) && (p_get(W,&v)==-1 || (p_get(W,&v)>p_get(W,&p))) && (v1-v2 <= 3) && (v1-v2 >= -1) && can_go(&v)){
        if(p_mhtn_norm(&v,target) < p_mhtn_norm(&p,target)){
          p_set(W,&v,p_get(W,&p));
          q_push_back(&v);
        }else{ /* > */
          /*if(!(p_get(W,&v)!=-1 || (p_get(W,&v)==p_get(W,&p)+1))){ */
          p_set(W,&v,p_get(W,&p)+1);
          q_push_front(&v);  
        }
        if(p_eq(&v,target)){
          break;
        }
      }
    }
    if(p_eq(&v,target)) break;
  }
  res = p_get(W,target);
  if(res != -1) res = 2*res+p_mhtn_norm(source,target); 
  return res;
}


/* can_go function */

int can_go(Pair* p){
  Pair *b = bts;
  Pair s, t, md, mv, mh, next, buf1, buf2, buf3;
  int v, h, ver, hor; /* coordinate steps */
  double val;
  int vis;
  
  while(b != bts+2){
    ln_init(b,p_get(Z,b)+0.5,p,p_get(Z,p)+0.5);
    /* go from the bottom up */
    if(p_get(Z,p) < p_get(Z,b)){
      s = *p;
      t = *b;
    }else{
      s = *b;
      t = *p;
    }
    
    hor = (s.c > t.c) ? -1 : 1;
    ver = (s.r > t.r) ? -1 : 1;
    
    #ifdef DEBUG
    printf("v: %d, h: %d\n",ver,hor);
    #endif
    
    h = (hor>0) ? 0 : 1;
    v = (ver>0) ? 0 : 1;
    
    vis = 1;
    while(!p_eq(&s,&t)){
      md = p_new(ver,hor);
      md = p_sum(&s,&md);
      buf1 = p_new(md.r+v,md.c+h);
      if(ln_rc_val(&buf1)==0){
        val = ln_z_by_r(buf1.r);
        next = md;  
      }else{
        mv = p_new(ver,0);
        mv = p_sum(&s,&mv);
        buf2 = p_new(mv.r+v,mv.c+h);
        if(!ln_rc_on_same_side(&buf1,&buf2)){
          val = ln_z_by_r(buf2.r);
          next = mv;    
        }else{
          mh = p_new(0,hor);
          mh = p_sum(&s,&mh);
          buf3 = p_new(mh.r+v,mh.c+h);
          val = ln_z_by_c(buf3.c);
          next = mh;
        }
      }
      #ifdef DEBUG
      printf("next %d,%d\n",next.r,next.c);
      #endif
      if(p_get(Z,&next) > val){
        
        #ifdef DEBUG
        printf("bad p: %d,%d val: %f\n",next.r,next.c,val);
        #endif
        
        vis = 0;
        break;
      }
      s = next;
    }
    if(vis) break;
    ++b; /* take next bts */
  }
  return vis;
}


int main(){
  int i, j, t, T, r;
  scanf("%d",&T);
  for(t=0; t<T; ++t){
    scanf("%d%d",&sz.r,&sz.c);
    for(i=0; i<sz.r; ++i){
      for(j=0; j<sz.c; ++j){
        scanf("%d",&Z[i][j]);
      }
    }
    scanf("%d%d%d%d",&bts[0].r,&bts[0].c,&bts[1].r,&bts[1].c);
    --bts[0].r;--bts[0].c;--bts[1].r;--bts[1].c;
    r = hadlock_algo(bts,bts+1);
    /*
    if(t==26){
      r = hadlock_algo(bts,bts+1);
      for(i=0; i<sz.r; ++i){
        for(j=0; j<sz.c; ++j){
          printf("%3d",W[i][j]);
        }
        printf("\n");
      }
      printf("\n");
    }
    else continue;
    */
    if(r!=-1){
      printf("The shortest path is %d steps long.\n",r);
    }else{
      printf("Mission impossible!\n");
    }
  }
  /*printf("clock: %d",clock());*/

  return 0;  
}

