// Merge two adjecent sub arrays
void merge_c(int a[], int start, int end, int aux[]) {
    int mid = (start + end) / 2;  // midpoint
    int pointer_left = start;  // points to the beginning of the left sub-array
    int pointer_right = mid + 1; // points to the beginning of the right sub-array
    int i;  // k is the loop counter

    // we loop from i to j to fill each element of the final merged array
    for (i = start; i <= end; i++) {
        if (pointer_left == mid + 1) {
            //  left pointer has reached the limit
            aux[i] = a[pointer_right];
            pointer_right++;
        } else if (pointer_right == end + 1) {
            // right pointer has reached the limit
            aux[i] = a[pointer_left];
            pointer_left++;
        } else if (a[pointer_left] < a[pointer_right]) {
            // pointer left points to smaller element
            aux[i] = a[pointer_left];
            pointer_left++;
        } else {
            // pointer right points to smaller element
            aux[i] = a[pointer_right];
            pointer_right++;
        }
    }

    // copy the elements from aux[] to a[]
    for (i = start; i <= end; i++)   
        a[i] = aux[i];
}

 
// Sort the subsection a[i .. j] of the array a[]
void merge_sort_c(int a[], int start, int end, int aux[]) {
    if (end <= start)  // the subsection is empty or a single element
        return;
    int mid = (start + end) / 2;

    // left sub-array is a[start .. mid]
    // right sub-array is a[mid + 1 .. end]

    // sort the left sub-array recursively
    merge_sort_c(a, start, mid, aux);
    // sort the right sub-array recursively
    merge_sort_c(a, mid + 1, end, aux);

    // merge the left and right sides
    merge_c(a, start, end, aux);
}
