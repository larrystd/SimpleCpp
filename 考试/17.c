int dum_tree_data(tree_t* t, data_t A[]) {  // inorder, means left->root->right
    A = (data_t* )malloc(num_node*sizeof(data_t));  // malloc space
    int num_element = 0;
    inorder(t, &A, &num_element);  // copy tree to array A

    return num_element-1;
}


void inorder(tree_t* t,data_t** A, int* index){  // inorder to copy t to A
    if (root == nullptr) return;
    inorder(t->left,arr);
    *A[(*index)++] = root->data;   // copy
    inorder(root->rght,arr);
}