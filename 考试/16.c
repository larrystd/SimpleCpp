int same_shape(tree_t* t1, tree_t t2) {   // judge same shape with recursion
    if (t1 == NULL && t2 == NULL) {   // all null, ok
        return 1;
    } else if (t1 == NULL || t2 == NULL) { // one is null, the other is not, false
        return 0;
    } else {
        return same_shape(t1->left, t2->left) && same_shape(t1->right, t2->right);  // judge their subnode
    }
}