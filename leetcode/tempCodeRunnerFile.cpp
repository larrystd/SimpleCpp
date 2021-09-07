

        for (int j = 0; j < prefix_nums[j].size(); j++) {
            if (! use_map.count(prefix_nums)) {
                use_map[prefix_nums[j]] = j;
            }else {
                if (j - u