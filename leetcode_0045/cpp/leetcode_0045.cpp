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
    int jump(vector<int>& nums) {
        //思路：动态规划
        //dp(i)表示到达该位置的最少跳跃次数
        //动态转移方程 dp(i) = min(dp(j)+1) {j+nums[j] >= i}
        //初始状态dp(0) = 0
        //因为总是可以到达最后一个位置，所以设置跳跃的次数初始化为nums.size()
        vector<int> dp = vector<int>(nums.size(),nums.size());
        dp[0] = 0;
        int nextIdx = 0;
        for(int i = 0;i < nums.size();i++){
            //如果当下索引所能达到的最远索引距离小于 前面能达到的最远索引距离则直接跳过
            if(i + nums[i] <= nextIdx)
                continue;
            nextIdx = min(i + nums[i],(int)nums.size()-1);
            for(int j = i+1;j <= nextIdx;j++){
                dp[j] = min(dp[j],dp[i]+1);
                if(j >= nums.size() - 1)
                    return dp[j];
            }
        }
        return dp[nums.size()-1];
    }
    int jump2(vector<int>& nums) {
        //思路：贪心算法 greedy
        //每次只需要选择出 所能跳出的最具潜力的选择即可
        //用jump来表示跳跃次数
        int jump = 0;
        int nextIdx = 0;
        //在当前跳跃区间内所能达到的最远距离
        int farth = 0;
        //注意循环索引，到达最后num.length - 1是不用跳的，已经到达最后的位置了
        //ep:[2]  result 0
        for(int i = 0;i < nums.size() - 1;i++){
            //更新[i...nextIdx]所能达到的最远距离
            farth = max(farth,i+nums[i]);
            if(i == nextIdx){
                jump++;
                //更新下一个最远索引
                nextIdx = farth;
                //如果所能达到的最远索引距离达到最后索引，则返回
                if(farth >= nums.size()-1)
                    return jump;
            }
        }
        return jump;
    }
};


int main(){
    vector<int> nums = {2,3,1,1,4};
    //result
    //2
    //可以先跳 1 步，从下标 0 到达下标 1, 然后再从下标 1 跳 3 步到达最后一个下标
//    vector<int> nums = {2,3,0,1,4};
    //result
    //2
    int res = Solution().jump2(nums);
    cout<<res<<endl;
}