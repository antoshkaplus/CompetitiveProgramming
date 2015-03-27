

#include <iostream>
#include <string>
#include <cmath>
#include <cstdio>

using namespace std;

int main(int argc, char **argv) {
    
    int T;
    cin >> T;
    for (int t = 0; t < T; ++t) {
        int wx, wy, wz, xy, xz, yz;
        cin >> wx >> wy >> wz >> xy >> xz >> yz;
        int tr[4][3] = {{wx, wy, xy},
            {wx, wz, xz},
            {wy, wz, yz},
            {xy, xz, yz}};
        double S = 0;
        for (int i = 0; i < 4; ++i) {
            double p = (tr[i][0]+tr[i][1]+tr[i][2])/2.;
            S += sqrt(p*(p-tr[i][0])*(p-tr[i][1])*(p-tr[i][2]));
        }
        
        double 
        U = wx, 
        V = wy, 
        W = xy, 
        u = yz, 
        v = xz, 
        w = wz;
        double
        X = (w - U + v)*(U + v + w),
        x = (U - v + w)*(v - w + U),
        Y = (u - V + w)*(V + w + u),
        y = (V - w + u)*(w - u + V),
        Z = (v - W + u)*(W + u + v),
        z = (W - u + v)*(u - v + W),
        a = sqrt(x*Y*Z),
        b = sqrt(y*Z*X),
        c = sqrt(z*X*Y),
        d = sqrt(x*y*z);
        double Vol = sqrt((-a + b + c + d)
                          *(a - b + c + d)
                          *(a + b - c + d)
                          *(a + b + c - d))/(192.*u*v*w);
        
        double r = 3.*Vol/(S);
        printf("%.4lf\n", r);
    } 
    
    
}