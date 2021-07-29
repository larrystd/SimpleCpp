#include <iostream>
#include "skip_list.h"

int main() {
    SkipList skiplist;
	for (int i = 1; i < 19; i++) {
		//skiplist.skipList_insert(i, 2 * i);
		skiplist.skipListInsert(i, i * 2);
	}

	std::cout << std::endl;

	skiplist.printSkipList();

	std::cout << skiplist.skipListSearch(6) << std::endl;

	return 0;
}