//
// Created by wangzy on 2022/5/19.
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


template<typename T>
void printVec(std::vector<T> l){
    std::string res = "[";
    std::string tmp = "";
    std::stringstream ss;
    for(auto ele : l){
        ss << ele;
        ss >> tmp;
        res += tmp + ",";
        ss.clear();
    }
    res = res.substr(0,res.size()-1);
    res += "]";
    std::cout<<res<<std::endl;
}

template<typename T>
string convertVecToStr(std::vector<T> l){
    std::string res = "[";
    std::string tmp = "";
    std::stringstream ss;
    for(auto ele : l){
        ss << ele;
        ss >> tmp;
        res += tmp + ",";
        ss.clear();
    }
    res = res.substr(0,res.size()-1);
    res += "]";
    return res;
}

template<typename T>
void printVecArr(std::vector<std::vector<T>> l){
    std::string res = "[";
    std::string tmp = "";
    std::stringstream ss;
    for(auto ele : l){
        ss << convertVecToStr(ele);
        ss >> tmp;
        res += tmp + ",";
        ss.clear();
    }
    res = res.substr(0,res.size()-1);
    res += "]";
    std::cout<<res<<std::endl;
}

class Solution {
public:
    int findTargetSumWays(vector<int>& nums, int target) {
        //思路：重叠子结构
        //记录 表达式累加和结果 如果到最后达到target则表达式数目+1
        //如果前面 子表达式(1...i)的累加和集合 X , 第i+1个数字为y,目标为target
        //则dp(i)代表前i个表达式的累加和等于target的数量
        //状态转移方程:dp(i,target) = dp(i-1,target-nums[i])+dp(i-1,target+nums[i])
        //初始状态: dp(0,0) = 1
        //由于nums个数字能够达到的最大数字为 nums均为正数，最小数字为 nums均为负数

        int max_target = 0;
        for(auto ele:nums)
            max_target += ele;

        //target 大于最大范围，取不到 返回 0
        if(abs(target) > abs(max_target))
            return 0;

        int n = nums.size();
        //二维数组列 的区间
        int col = 2*max_target+1;
        //dp[i][target] target的范围从[-max_target,max_target] 包括0
        //需要整体向右扩展 2*max_target+1
        vector<vector<int>> dp = vector<vector<int>>(n+1,vector<int>(col+1,0));
        //dp[i][max_target + 1] 相当于dp[i][0]
        //初始化 dp(1,nums[0]) dp(1,-nums[0])
        dp[0][max_target + 1] = 1;


        for(int i = 1;i <= n;i++){
            for(int j = 1;j <= col;j++){
                //dp(i,target) = dp(i-1,target-nums[i])+dp(i-1,target+nums[i])
                //二维数组 索引边界 [1,max_target*2+1]
                //超出索引边界就取0索引 0索引列的值为0
                int left = (j-nums[i-1] >= 1)?j-nums[i-1]:0;
                int right = (j+nums[i-1] <= col)?j+nums[i-1]:0;
                dp[i][j] = dp[i-1][left]+dp[i-1][right];
            }
            printVec(dp[i]);
        }
        return dp[n][target+max_target+1];
    }
    int findTargetSumWays2(vector<int>& nums, int target) {
        //思路：重叠子结构
        //记录 表达式累加和结果 如果到最后达到target则表达式数目+1
        //如果前面 子表达式(1...i)的累加和集合 X , 第i+1个数字为y,目标为target
        //则dp(i)代表前i个表达式的累加和等于target的数量
        //状态转移方程:dp(i,target) = dp(i-1,target-nums[i])+dp(i-1,target+nums[i])
        //初始状态: dp(0,0) = 1
        //由于nums个数字能够达到的最大数字为 nums均为正数，最小数字为 nums均为负数

        int max_target = 0;
        for(auto ele:nums)
            max_target += ele;

        //target 大于最大范围，取不到 返回 0
        if(abs(target) > abs(max_target))
            return 0;

        int n = nums.size();
        //二维数组列 的区间
        int col = 2*max_target+1;
        //dp[i][target] target的范围从[-max_target,max_target] 包括0
        //需要整体向右扩展 2*max_target+1
//        vector<vector<int>> dp = vector<vector<int>>(n+1,vector<int>(col+1,0));
        vector<int> dp = vector<int>(col+1,0);
        //上一行
        vector<int> prev = vector<int>(col+1,0);
        //dp[i][max_target + 1] 相当于dp[i][0]
        //初始化 dp(1,nums[0]) dp(1,-nums[0])
//        dp[0][max_target + 1] = 1;
        prev[max_target+1] = 1;

        for(int i = 1;i <= n;i++){
            for(int j = 1;j <= col;j++){
                //dp(i,target) = dp(i-1,target-nums[i])+dp(i-1,target+nums[i])
                //二维数组 索引边界 [1,max_target*2+1]
                //超出索引边界就取0索引 0索引列的值为0
                int left = (j-nums[i-1] >= 1)?j-nums[i-1]:0;
                int right = (j+nums[i-1] <= col)?j+nums[i-1]:0;
                // dp[i][j] = dp[i-1][left]+dp[i-1][right];
                dp[j] = prev[left] + prev[right];
            }
            prev.assign(dp.begin(),dp.end());
            //将dp数组中col+1个元素都重置为0
            dp.assign(col+1,0);
            printVec(prev);
        }
//        printVecArr(dp);
//        return dp[n][target+max_target+1];
        return prev[target+max_target+1];
    }
};

int main(){
    vector<int> nums = {1,1,1,1,1};
    int target = 3;
    //result
    //5
    /**
     * 一共有 5 种方法让最终目标和为 3
        -1 + 1 + 1 + 1 + 1 = 3
        +1 - 1 + 1 + 1 + 1 = 3
        +1 + 1 - 1 + 1 + 1 = 3
        +1 + 1 + 1 - 1 + 1 = 3
        +1 + 1 + 1 + 1 - 1 = 3

        状态转移数组
        [0,0,0,0,0,1,0,1,0,0,0,0]
        [0,0,0,0,1,0,2,0,1,0,0,0]
        [0,0,0,1,0,3,0,3,0,1,0,0]
        [0,0,1,0,4,0,6,0,4,0,1,0]
        [0,1,0,5,0,10,0,10,0,5,0,1]
     *
     */
    int res = Solution().findTargetSumWays(nums,target);
    cout<<res<<endl;
}
