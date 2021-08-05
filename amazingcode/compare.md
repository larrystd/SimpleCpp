用lambda表达式写sort
        sort(lhs.begin(), lhs.end(), [](const vector<int> &a, const vector<int> &b) {
            if (a[1] != b[1])
                return a[1] < b[1];
            return a[0] < b[0];
         });