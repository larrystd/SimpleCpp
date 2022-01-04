#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:

    int numberEachRow(const string& str) const {
        int number = 0;
        for (int i : str) {
            if (i == '1')
                number++;
        }
        return number;
    }
    int numberOfBeams(vector<string>& bank) {
        int number = 0;
        int prevnum = 0;

        for (int i = 0; i < bank.size(); i++) {
            int rowhasbeams = numberEachRow(bank[i]);
            if (prevnum == 0 && rowhasbeams != 0)
                prevnum = numberEachRow(bank[i]);
            if (prevnum != 0 && rowhasbeams != 0) {
               number += prevnum*numberEachRow(bank[i]);
               prevnum = rowhasbeams;
            }
 
        }

        return number;
    }
};