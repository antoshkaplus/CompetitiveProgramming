

/* GLOBAL VARIABLES */
int T; /* number of test cases ~500 */
int P, Q; /* number of rows and columns in grid (1,200) */
const int SZ_MAX = 200;
int Z[SZ_MAX][SZ_MAX]; /* height grid */
int P[SZ_MAX][SZ_MAX]; /* path length in search */


/* possible directions */
const int DOWN
const int UP
const int RIGHT
const int LEFT

int can_go(PI p, int dir){
  
}


/*
  left -> right : Ox
  top -> bottom : Oy
  like matrix
*/

struct PI{
  int x, y;
};

struct PD{
  double x, y;
};

struct PD pi_to_pd(struct PI pi){
  struct PD pd;
  pd.x = pi.x;
  pd.y = pi.y; 
  return pd;
}

struct PD pd_to_pi(struct PD pd){
  struct PI pi;
  pi.x = pd.x;
  pi.y = pd.y;
  return pd
}

int height(struct PI p){
  return Z[p.y][p.x];
}

struct Line{
  struct PD p1, p2;
  double z1, z2;
};

void line_init(Line *ln, PD p1, double z1, PD p2, double z2){
  ln->p1 = p1;
  ln->p2 = p2;
  ln->z1 = z1;
  ln->z2 = z2;
}

double line_z_by_x(Line ln, double x){
  return (x-ln.p1.x)(ln.z2-ln.z1)/double(ln.p2.x-ln.p1.x) + ln.z1;
}

double line_z_by_y(Line ln, double y){
  return (x-ln.p1.x)(ln.z2-ln.z1)/double(ln.p2.x-ln.p1.x) + ln.z1;
}

double line_xy_val(Line ln, struct PD){
  return (PI.x-ln.p1.x)*(ln.p2.y-ln.p1.y)-(PI.y-ln.p1.y)*(ln.p2.x-ln.p1.x);
}

int line_xy_inc(Line ln){
  return (ln.p1.y-ln.p2.y)/(ln.p1.x-ln.p2.x) > 0;
}

int line_xy_on_same_side(Line ln, struct PD p1, struct PD p2){
  return line_xy_val(ln,p1)*line_xy_val(ln,p2) > 0;
}


/* visibility function and service */

struct PD get_right(struct PD pd){
  ++pd.x;
  return pd;
} 

struct PD get_top(struct PD pd){
  --pd.y;
  return pd;
}

struct PD get_bot(struct PD pd){
  ++pd.y;
  return pd;
}

struct PD get_topright(struct PD pd){
  --pd.y;
  ++pd.x;
  return pd;
}

struct PD get_botright(struct PD pd){
  ++pd.y;
  ++pd.x;
  return pd;
}

int visibility(PI pi1, PI pi2){
  Line ln;
  PD pd1, pd2;
  PD cur, next, end; /* PI better */   
  PD rt, lt, md; /*  */ 
  struct PD (*get_rt)(struct PD);
  struct PD (*get_lt)(struct PD);
  struct PD (*get_md)(struct PD);
  int vis;
  
  
  pi_to_pd(&pd1,pi1);
  pi_to_pd(&pd2,pi2);
  
  /* pd1 and pd2 must be centers of correspond cells for line initialization */
  init_line(&ln,pd1,Z[pi1.y][pi1.x]+0.5,pd2,Z[pi2.y][pi2.x]+0.5); 
  
  
  if(line_xy_inc(ln)){
    /*
      s..
      ...  
      ..f   
    */
    if(pd1.x >= pd2.x && pd1.y >= pd2.y){
      cur = pd1;
      end = pd2;
    }else{
      cur = pd2;
      end = pd1;
    }
    
    get_rt = &get_right;
    get_lt = &get_bot;
    get_md = &get_botright;
  else{
    /*
      ..f
      ...
      s..
    */
    if(pd1.x <= pd2.x && pd1.y >= pd2.y){
      cur = pd1;
      end = pd2;
    }else{
      cur = pd2;
      end = pd1;
    }
    
    get_rt = &get_right;
    get_lt = &get_top;
    get_md = &get_topright;
  }  
    
  vis = 1;  
  do{
    md = (*get_md)(cur);
    if(line_xy_val(ln,md) == 0){
      next = md;
      val = line_z_by_x(ln,md.x);
    }else{
      rt = (*get_rt)(cur);
      if(!line_xy_on_same_side(ln,rt,md)){
        next = rt;
        val = line_z_by_x(ln,rt.x);
      }else{
        lt = (*get_lt)(cur);
        next = lt;
        val = line_z_by_y(ln,lt.y);
      }        
    }
    if(height(cur) > val || height(next) > val){
      vis = 0;
      break;
    }
    cur = next;
  }while(strcmp(&cur,&end,sizeof(PD))); 

  return vis;  
}


int search(PI p1, PI p2){
  

}



int main(){
  
 
}





