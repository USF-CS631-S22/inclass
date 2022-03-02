#include <stdio.h>


/* Merge two adjecent sub arrays */
void merge_c(int a[], int i, int j, int aux[]) {
    int mid = (i + j) / 2;
    /* pointer_left points to the beginning of the left sub-array */ 
    int pointer_left = i; 
    /* pointer_right points to the beginning of the right sub-array */
    int pointer_right = mid + 1;
    /* k is the loop counter */
    int k;      // k is the loop counter

    /* we loop from i to j to fill each element of the final merged array */
    for (k = i; k <= j; k++) {
        if (pointer_left == mid + 1) {
            /*  left pointer has reached the limit */
            aux[k] = a[pointer_right];
            pointer_right++;
        } else if (pointer_right == j + 1) {
            /* right pointer has reached the limit */
            aux[k] = a[pointer_left];
            pointer_left++;
        } else if (a[pointer_left] < a[pointer_right]) {
            /* pointer left points to smaller element */
            aux[k] = a[pointer_left];
            pointer_left++;
        } else {
            /*  pointer right points to smaller element */
            aux[k] = a[pointer_right];
            pointer_right++;
        }
    }

    /* copy the elements from aux[] to a[] */
    for (k = i; k <= j; k++) {      
        a[k] = aux[k];
    }    
}
 
/* Sort the subsection a[i .. j] of the array a[] */
void merge_sort_c(int a[], int i, int j, int aux[]) {
    if (j <= i) {
        /* the subsection is empty or a single element */
        return;
    }
    int mid = (i + j) / 2;

    /* left sub-array is a[i .. mid] */
    /* right sub-array is a[mid + 1 .. j] */

    /* sort the left sub-array recursively */
    merge_sort_c(a, i, mid, aux);
    /* sort the right sub-array recursively */
    merge_sort_c(a, mid + 1, j, aux);

    /* merge the left and right sides */
    merge_c(a, i, j, aux);
}
