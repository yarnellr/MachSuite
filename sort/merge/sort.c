#include "sort.h"

void merge(TYPE a[SIZE], int start, int m, int stop){
    TYPE temp[SIZE];
    int i, j, k;

    merge_label1 : for(i=start; i<=m; i++){
        #pragma HLS loop_tripcount min=SIZE/2 max=SIZE/2
        temp[i] = a[i];
    }

    merge_label2 : for(j=m+1; j<=stop; j++){
        #pragma HLS loop_tripcount min=SIZE/2 max=SIZE/2
        temp[m+1+stop-j] = a[j];
    }

    i = start;
    j = stop;

    merge_label3 : for(k=start; k<=stop; k++){
        #pragma HLS loop_tripcount min=SIZE/2 max=SIZE/2
        TYPE tmp_j = temp[j];
        TYPE tmp_i = temp[i];
        if(tmp_j < tmp_i) {
            a[k] = tmp_j;
            j--;
        } else {
            a[k] = tmp_i;
            i++;
        }
    }
}

void ms_mergesort(TYPE a[SIZE]) {
    int i, m, from, mid, to;

    mergesort_label1 : for(m=1; m<SIZE; m+=m) {
        #pragma HLS loop_tripcount min=SIZE max=SIZE
        mergesort_label2 : for(i=0; i<SIZE; i+=m+m) {
            #pragma HLS loop_tripcount min=SIZE/2 max=SIZE/2
            from = i;
            mid = i+m-1;
            to = i+m+m-1;
            if(to < SIZE){
                merge(a, from, mid, to);
            }
            else{
                merge(a, from, mid, SIZE);
            }
        }
    }
}
