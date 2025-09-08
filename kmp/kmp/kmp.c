/*
Implementation based on http://www-igm.univ-mlv.fr/~lecroq/string/node8.html
*/

#include "kmp.h"

int kmp(char pattern[PATTERN_SIZE], char input[STRING_SIZE], int32_t kmpNext[PATTERN_SIZE], int32_t n_matches[1]) {
    int32_t i, k, q;
    k = 0;
    n_matches[0] = 0;
    kmpNext[0] = 0;

    c1 : for(q = 1; q < PATTERN_SIZE; q++){
        c2 : for (int i = 0; i < PATTERN_SIZE; i++) {
            #pragma HLS loop_tripcount min=PATTERN_SIZE max=PATTERN_SIZE
            if (!(k > 0 && pattern[k] != pattern[q])) break;
            k = kmpNext[k];
        }
        if(pattern[k] == pattern[q]){
            k++;
        }
        kmpNext[q] = k;
    }

    q = 0;
    k1 : for(i = 0; i < STRING_SIZE; i++){
        k2 : for (int j = 0; j < PATTERN_SIZE; j++) {
            #pragma HLS loop_tripcount min=PATTERN_SIZE max=PATTERN_SIZE
            if (!(q > 0 && pattern[q] != input[i])) break;
            q = kmpNext[q];
        }
        if (pattern[q] == input[i]){
            q++;
        }
        if (q >= PATTERN_SIZE){
            n_matches[0]++;
            q = kmpNext[q - 1];
        }
    }
    return 0;
}
