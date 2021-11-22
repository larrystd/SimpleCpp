void remove_borrower(boot_t B[], int nbooks, int b_num) {
    for (int i = 0; i < nbooks; i++) {
        
        int j = 0;
        while (j < MAXBORROWS) {
            if (B[i].borrowers[j] ==  b_num) {  // delete b_num in B[i].borrowers
                for (int k = j+1; k < MAXBORROWS; k++) {
                    B[i].borrowers[k-1] = B[i].borrowers[k];    // overwrite the latter is equivalent to deleting borrowers[j]
                }
            }else{
                j++;
            }

        }
    }
}