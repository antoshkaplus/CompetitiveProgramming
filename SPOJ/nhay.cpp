
#include <vector>
#include <iterator>   

namespace ant {
    
    
    enum struct Enabler {}; 
    constexpr Enabler enabler = {};
        
    template<typename Condition>
    using EnableIf = typename std::enable_if<Condition::value, Enabler>::type;
    
    
    
    template <typename patIter>
    class KnuthMorrisPratt {
        typedef typename std::iterator_traits<patIter>::difference_type difference_type;
        
    public:
        KnuthMorrisPratt (patIter first, patIter last) 
        :   pat_first(first), 
        pat_last(last), 
        k_pattern_length(std::distance(pat_first, pat_last)),
        skip_(k_pattern_length + 1) {
            
            PreKmp(pat_first, pat_last);
        }
        
        /// \fn operator(corpusIter corpus_first, corpusIter corpus_last, Pred p)
        /// \brief Searches the corpus for the pattern that was passed into the constructor
        /// 
        /// \param corpus_first The start of the data to search (Random Access Iterator)
        /// \param corpus_last  One past the end of the data to search
        /// \param p            A predicate used for the search comparisons.
        ///
        template <typename corpusIter, EnableIf<
        std::is_same<typename std::iterator_traits<patIter>::value_type, 
        typename std::iterator_traits<corpusIter>::value_type> > = enabler >
        
        corpusIter operator()(corpusIter corpus_first, corpusIter corpus_last) const {
            
            if (corpus_first == corpus_last) return corpus_last;  // if nothing to search, we didn't find it!
            if (pat_first == pat_last) return corpus_first; // empty pattern matches at start
            
            const difference_type k_corpus_length = std::distance(corpus_first, corpus_last);
            //  If the pattern is larger than the corpus, we can't find it!
            if (k_corpus_length < k_pattern_length) { 
                return corpus_last;
            }
            
            return Search(corpus_first, corpus_last, k_corpus_length);
        }
        
        
    private:
        
        /// \cond DOXYGEN_HIDE
        patIter pat_first, pat_last;
        const difference_type k_pattern_length;
        std::vector <difference_type> skip_;
        
        /// \fn operator ( corpusIter corpus_first, corpusIter corpus_last, Pred p )
        /// \brief Searches the corpus for the pattern that was passed into the constructor
        /// 
        /// \param corpus_first The start of the data to search (Random Access Iterator)
        /// \param corpus_last  One past the end of the data to search
        /// \param p            A predicate used for the search comparisons.
        ///
        template <typename corpusIter>
        corpusIter Search(corpusIter corpus_first, corpusIter corpus_last, 
                          difference_type k_corpus_length) const {
            difference_type match_start = 0;  // position in the corpus that we're matching
            int patternIdx = 0;
            while (match_start < k_corpus_length) {
                while (patternIdx > -1 && pat_first[patternIdx] != corpus_first[match_start]) {
                    patternIdx = skip_[patternIdx]; //<--- Shifting the pattern on mismatch
                }
                patternIdx++;
                match_start++; //<--- corpus is always increased by 1
                
                if (patternIdx >= (int)k_pattern_length) {
                    return corpus_first + match_start - patternIdx;
                }
            }
            return corpus_last;
        }
        
        // initializing table
        void PreKmp(patIter first, patIter last) {
            const int count = std::distance(first, last);
            
            int i, j;
            
            i = 0;
            j = skip_[0] = -1;
            while (i < count) {
                while (j > -1 && first[i] != first[j]) {
                    j = skip_[j];
                }
                i++;
                j++;
                skip_[i] = first[i] == first[j] ? skip_[j] : j;
            }
        }
    };
}



#include <iostream>

using namespace std;
using namespace ant;

int main(int argc, char **argv) {
    int n;
    string pat;
    string text;
    while (cin >> n) {
        cin >> pat >> text;
        KnuthMorrisPratt<string::iterator> kmp(pat.begin(), pat.end());
        auto next = text.begin();
        while ((next = kmp(next, text.end())) != text.end()) {
            cout << next-text.begin() << endl;
            ++next;
        }
        cout << endl;
    }
}