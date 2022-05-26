//
// Created by wangzy on 2022/5/26.
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
    int maxCoins(vector<int>& nums) {
        //思路：可以通过给边界两边补充nums[-1]=1,nums[n]=1,可以认为是“虚拟气球”
        //首先可以想到极限状态下，只有一个气球的话, 1*nums[i]*1
        //题目可以改变为，在nums中，戳破气球0到气球n+1中间的所有气球（不包括0和n+1）
        //使得最终只剩下0和n+1气球，最多能得到多少分
        //定义数组dp[i][j] 表示 (i,j) 戳破开区间所有气球，可以获得的最高分数x
        //初始状态dp[i][j] = 0,其中0<=i<=n+1,j <= i+1
        //状态转移方程dp[i][j] = max(dp[i][k]+nums[k]*nums[i]*nums[j]+dp[k][j])
        //k表示最后戳破第k个气球,在戳破气球中选择最多可以得到多少分 由于状态表示为是开区间 i<k<j
        //由于k>=i,k<=j ,所以状态转移方程是从左往右，从下往上
        int n = nums.size()+2;
        vector<int> points = vector<int>(n,0);
        //初始化边界
        points[0] = 1;points[n-1] = 1;
        for(int i = 1;i < n-1;i++)
            points[i] = nums[i-1];
        vector<vector<int>> dp = vector<vector<int>>(n,vector<int>(n,0));
        for(int i = n - 1;i >= 0;i--){
            for(int j = i+1;j < n;j++){
                //选择最后戳破的那个气球
                for(int k = i+1;k < j;k++){
                    dp[i][j] = max(dp[i][j],dp[i][k]+points[k]*points[i]*points[j]+dp[k][j]);
                }
            }
        }
        return dp[0][n-1];
    }
};

int main(){
    vector<int> nums = {3,1,5,8};
    //result
    //167
    //nums = [3,1,5,8] --> [3,5,8] --> [3,8] --> [8] --> []
    //coins =  3*1*5    +   3*5*8   +  1*3*8  + 1*8*1 = 167
    int res = Solution().maxCoins(nums);
    cout<<res<<endl;
}