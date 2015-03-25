

#include <iostream>
#include <string>
#include <cmath>
#include <cstdio>
#include <set>
#include <limits>
#include <vector>
#include <queue>
#include <map>


using namespace std;

int main(int argc, char **argv) {
    int T;
    cin >> T;
    for (int t = 0; t < T; ++t) {
        double a, m_h_a, m_h_b, m_h_c;
        cin >> a >> m_h_a >> m_h_b >> m_h_c;
        double 
        h_a = 3*m_h_a,
        h_b = 3*m_h_b,
        h_c = 3*m_h_c,
        b = a*h_a/h_b,
        c = a*h_a/h_c,
        S = a*h_a/2.;
        double d = 9.*b*b*c*c/(4.*h_a*h_a) - (a*a + b*b + c*c);
        double D = (d < 1e-10) ? 0 : 2./3*sqrt(d);
        
        printf("%.3lf %.3lf\n", S, D);
    } 
}