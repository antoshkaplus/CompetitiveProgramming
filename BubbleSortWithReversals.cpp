#include <algorithm>
#include <stack>
#include <queue>
#include <vector>
#include <iostream>
#include <string>

using namespace std;

struct BubbleSortWithReversals {
    
    static const int maxN = 50; 
    
    int elem_win[maxN][maxN]; // element, after index 
    int all_win[maxN][maxN+1]; // from, how many elements
    
    // from element, how many K left
    int table[maxN+1][maxN+1]; // zero it pls
    
    void go(int cur, int K, int N) {
        if (K == 0 || cur == N) {
            table[cur][K] = 0;
            return;
        }
        
        int w_best = 0;
        for (int i = cur; i < N; ++i) {
            for (int p = 1; p <= N-i; ++p) {
                int w = all_win[i][p];
                if (table[i + p][K-1] == -1) {
                    go(i + p, K-1, N);
                }
                w += table[i + p][K-1];
                if (w > w_best) {
                    w_best = w;
                }
            }
        }
        table[cur][K] = w_best;
    }
    
    int getMinSwaps(vector<int> A, int K) {
        
        int N = A.size();
        
        //fill_n(*elem_win, maxN*maxN, 0);
        for (int i = 0; i < N; ++i) {
            // only post used
            int w = 0;
            for (int j = i; j < N; ++j) {
                // wrong ordering is + 
                if (A[j] < A[i]) ++w;
                else if (A[j] > A[i]) --w; 
                elem_win[i][j] = w;
            }
        }
        
        
        for (int i = 0; i < N; ++i) {
            for (int j = 1; j <= N-i; ++j) {
                int& w = all_win[i][j] = 0;
                for (int p = i; p < i+j; ++p) {
                    w += elem_win[p][i+j-1];
                }
            }
        }
        
        int s = 0;
        for (int i = 0; i < N; ++i) {
            for (int j = i+1; j < N; ++j) {
                if (A[j] < A[i]) ++s;
            }
        }
        
        cout << endl << s << endl;
        
        fill_n(*table, (maxN+1)*(maxN+1), -1);
        go(0, K, N);
            
        cout << endl << "elem_win: " << endl;
        for (int i = 0; i < N; ++i) {
            for (int j = 1; j <= N-i; ++j) {
                cout << elem_win[i][i+j-1] << " ";
            }
            cout << endl;
        }
        
        cout << endl << "all_win: " << endl;
        for (int i = 0; i < N; ++i) {
            for (int j = 1; j <= N-i; ++j) {
                cout << all_win[i][i+j-1] << " ";
            }
            cout << endl;
        }
        
        cout << endl << "table: " << endl;
        for (int i = 0; i < N; ++i) {
            for (int j = 1; j <= K; ++j) {
                cout << table[i][j] << " ";
            }
            cout << endl;
        }
        
        return s - table[0][K];
    }
};
