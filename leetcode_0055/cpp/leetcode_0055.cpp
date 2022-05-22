//
// Created by wangzy on 2022/5/22.
//

#include<iostream>
#include<queue>
#include<vector>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <list>
#include <deque>
#include <stack>
#include <sstream>
#include <typeinfo>
#include <climits>
#include <random>
#include <ctime>
#include <cstring>

using namespace std;


class Solution {
public:
    bool canJump(vector<int>& nums) {
        //思路：贪心算法 greedy
        // 根据索引遍历不断更新过往索引能达到的最大索引位置
        //如果超过 最后一个下标索引 则返回true,否则返回false
        int sz = nums.size();
        int tar_inx = sz - 1;
        int num_inx = 0;
        for(int i = 0;i <= num_inx;i++){
            num_inx = max(num_inx,i+nums[i]);
            if(num_inx >= tar_inx)
                return true;
        }
        return false;
    }
};

int main(){
    vector<int> nums = {2,3,1,1,4};
    //result
    //true
    //可以先跳 1 步，从下标 0 到达下标 1, 然后再从下标 1 跳 3 步到达最后一个下标
//    vector<int> nums = {3,2,1,0,4};
    //result
    //false
    //无论怎样，总会到达下标为 3 的位置。但该下标的最大跳跃长度是 0 ， 所以永远不可能到达最后一个下标。
    bool res = Solution().canJump(nums);
    cout<<boolalpha<<res<<endl;
}