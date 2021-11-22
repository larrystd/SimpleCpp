int* pack(int* A) {
    int len = 1;    // number of different elements in A
    int prev = *A;
    int* p = A;
    while (*p != 0) {
        if (*p != prev) {
            len++;  
            num = *p;
        }
        p++;
    }
    int size = len*2+1; // size of the pack array
    int* result = (int*)malloc(size*sizeof(int));
    prev = 0;
    int num = 0;    // Number of consecutive elements
    int* head = result;
    while (*p != 0) {
        if (*p != prev) {
            *result = prev;
            result++;
            *result = num;
            num = 0;    // reset
            prev = *p;
            result++;
        }
        num++;
        p++;
    }
    *result = 0;
    return head;
}

