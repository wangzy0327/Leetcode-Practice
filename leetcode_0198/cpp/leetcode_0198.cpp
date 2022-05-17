//
// Created by wangzy on 2022/5/17.
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
    //时间复杂度:O(n)
    //空间复杂度:O(n)
    int rob(vector<int>& nums) {
        //思路：动态规划，由于都是非负整数，且不能相邻取数
        //则选取当前房屋的数值的最高金额dp(i) = max(dp(i-2),dp(i-3))+nums[i]
        //偷取的最高金额为 max(dp(n),dp(n-1))
        //初始状态dp(0) = nums[0],dp(1) = nums[1];
        int n = nums.size();
        if(n == 1){
            return nums[0];
        }else if(n == 2){
            return max(nums[1],nums[0]);
        }
        vector<int> dp = vector<int>(n,0);
        //初始化
        dp[0] = nums[0];dp[1] = nums[1];
        for(int i = 2;i < nums.size();i++){
            int prevv = (i-3>=0)?dp[i-3]:0;
            int prev = dp[i-2];
            dp[i] = max(prevv,prev)+nums[i];
        }
        return max(dp[n-1],dp[n-2]);
    }
    //时间复杂度:O(n)
    //空间复杂度:O(1) 使用滚动数组
    int rob2(vector<int>& nums) {
        //思路：动态规划，由于都是非负整数，且不能相邻取数
        //用 dp[i] 表示前 i间房屋能偷窃到的最高总金额
        //dp[i] = max(dp[i-2]+nums[i],dp[i-1])
        //最简单的情况，只有一间房dp[i] = nums[0];
        //初始状态 ;
        if(nums.size() == 1)
            return nums[0];
        //dp[i-2]
        int prevv = 0;
        //dp[i-1]
        int prev = nums[0];
        //dp[i]
        int dp = 0;
        for(int i = 1;i < nums.size();i++){
            //dp[i] = max(dp[i-2]+nums[i],dp[i-1])
            dp = max(prevv+nums[i],prev);
            //更新下一个dp[i-2] 为当前dp[i-1]
            prevv = prev;
            //更新下一个dp[i-1] 为当前dp[i]
            prev = dp;
        }
        return dp;
    }
};

int main(){
    vector<int> nums = {2,7,9,3,1};
    //result
    //12
    //偷窃 1 号房屋 (金额 = 2), 偷窃 3 号房屋 (金额 = 9)，接着偷窃 5 号房屋 (金额 = 1)
    //偷窃到的最高金额 = 2 + 9 + 1 = 12
//    vector<int> nums = {1,2,3,1};
    //result
    //4
    //偷窃 1 号房屋 (金额 = 1) ，然后偷窃 3 号房屋 (金额 = 3)
    //偷窃到的最高金额 = 1 + 3 = 4
    int res = Solution().rob2(nums);
    cout<<res<<endl;
}
