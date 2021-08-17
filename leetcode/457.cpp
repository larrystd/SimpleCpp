#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    bool circularArrayLoop(vector<int>& nums) {
        int n = nums.size();
        vector<int> mark(n, 0);
        for (int i = 0; i < nums.size(); i++) {
            mark = vector<int>(n,0);
            if (mark[i] == 0) {
                mark[i] = 1;
                int step = nums[i];
                int pos;
                if (i + nums[i] < 0) 
                    pos = i + nums[i]%n + n;
                else
                    pos = (i + nums[i]) % n;
                while (1) {
                    //if (step > n || step < -n)
                    //    break;
                    if (mark[pos] == 1) {
                        bool istrue = true;
                        bool flag = nums[pos]>0;
                        int pos_;
                        if (pos + nums[pos] < 0)
                            pos_ = pos + nums[pos]%n + n;
                        else
                            pos_ = (pos + nums[pos]) % n;
                        if (pos_ == pos)
                            break;
                        
                        while (pos_ != pos) {
                            if (nums[pos_] >0 != flag){
                                istrue = false;
                                break;
                            }     
                            if (pos_ + nums[pos_] < 0)
                                pos_ = pos_ + nums[pos_]%n + n;
                            else
                                pos_ = (pos_ + nums[pos_]) % n;
                        }
                        if (istrue)
                            return true;
                        else
                            break;
                    }
                        
                    step += nums[pos];
                    mark[pos] = 1;
                    if (pos + nums[pos] < 0) 
                        pos = pos + nums[pos]%n + n;
                    else
                        pos = (pos + nums[pos]) % n;
                    
                }
            }  
        }
        return false;
    }
};

int main() {
    vector<int> vect = {-2,-3,-9};
    Solution s;
    //cout << (-10 % 3) <<endl;
    cout << s.circularArrayLoop(vect)<<endl;
    return 0;
}