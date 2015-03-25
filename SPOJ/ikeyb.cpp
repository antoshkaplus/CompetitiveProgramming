

#include <iostream>
#include <string>

using namespace std;

const int kKeyMaxCount = 90;
const int kLetterMaxCount = 90;

// get score from letter to letter for key
int score[kLetterMaxCount][kLetterMaxCount];
// best score for number of letters on k first letters
int table[kKeyMaxCount][kLetterMaxCount];
// index of first letter in last key 
// should be able to track result back with it 
int index[kKeyMaxCount][kLetterMaxCount];

int frequency[kLetterMaxCount];
int result[kKeyMaxCount];

// by statement each key should have at least letter

int main(int argc, char **argv) {
    
    int T;
    cin >> T;
    for (int t = 0; t < T; ++t) {
        int key_count, letter_count;
        cin >> key_count >> letter_count;
        string keys;
        string letters;
        cin >> keys;
        cin >> letters;
        for (int i = 0; i < letters.size(); ++i) {
            cin >> frequency[i];
        }
        
        // from i to j including
        for (int i = 0; i < kLetterMaxCount; ++i) {
            score[i][i] = frequency[i];
            for (int j = i+1; j < kLetterMaxCount; ++j) {
                score[i][j] = score[i][j-1] + (j-i+1)*frequency[j];
            }
        }
        
        for (int p = 0; p < letter_count; ++p) {
            table[0][p] = score[0][p];
            index[0][p] = 0;
        }
        // key that's now available
        for (int k = 1; k < key_count; ++k) {
            // index of last letter
            for (int p = k; p < letter_count; ++p) {
                // one letter for key
                table[k][p] = table[k-1][k-1] + score[k][p];
                index[k][p] = k;
                // where to start new key letters?
                // p is already in, so no need in investigation
                for (int p_m = k; p_m+1 <= p; ++p_m) {
                    int s = table[k-1][p_m] + score[p_m+1][p];
                    if (s < table[k][p]) {
                        table[k][p] = s;
                        index[k][p] = p_m+1;
                    }
                }
            }
        }
        
        result[key_count-1] = index[key_count-1][letter_count-1];
        for (int k = key_count-2; k >= 0; --k) {
            result[k] = index[k][result[k+1]-1];
        }
        
        cout << "Keypad #" << t+1 << ":" << endl;
        for (int k = 0; k < key_count; ++k) {
            cout << keys[k] << ": ";
            int last = k == key_count-1 ? letter_count : result[k+1];
            for (int i = result[k]; i < last; ++i) {
                cout << letters[i];
            }
            // last blank line included
            cout << endl;
        }
    } 
    
    
}