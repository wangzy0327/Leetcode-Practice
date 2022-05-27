//
// Created by wangzy on 2022/5/27.
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
    bool canPartition(vector<int>& nums) {
        //思路：背包问题，动态规划
        //将数组划分为两个相等子集，可以通过先求数组的和
        //如果数组的和为奇数，则只包含正整数的非空数组不可能分割成两个相等的子集
        //数组和Sum为偶数的话，其和的一半target即为 从数组中找到集合等于target
        //转化为背包问题，每个数组的数字有两个选择，放进或者不放，背包的和为target
        //状态dp(i,sub_sum) = x 表示对于前i个数字，当容量为sub_sum时，若x为true时，则更好可以将背包装满
        //如果x为false时，则不能将背包装满
        //状态就是 背包的容量和可选择的物品，选择就是放进背包或者不放进背包
        //状态转移 dp(i,sub_sum) = dp(i-1,sub_sum-nums[i-1]) {i不放进背包} || dp(i-1,sub_sum) {i不放进背包}
        //初始状态 base case : dp(...,0) = true (背包容量为0) dp(0,...) = false (没有可选的物品)
        int sum = 0;
        for(auto ele:nums)
            sum += ele;
        if(sum % 2 != 0)
            return false;
        int target = sum/2;
        int n = nums.size();
        vector<vector<bool>> dp = vector<vector<bool>>(n+1,vector<bool>(target+1,false));
        for(int i = 0;i <= n;i++)
            dp[i][0] = true;

        printVec(dp[0]);
        for(int i = 1;i <= n;i++){
            //每一行只与上一行相关
            //遍历直到背包容量为1
            for(int j = target;j >= 1;j--){
                if(j - nums[i-1] >= 0)
                    dp[i][j] = dp[i-1][j] || dp[i-1][j-nums[i-1]];
                else
                    dp[i][j] = dp[i-1][j];
            }
            printVec(dp[i]);
        }
        return dp[n][target];
    }
    bool canPartition2(vector<int>& nums) {
        //思路：背包问题，动态规划
        //将数组划分为两个相等子集，可以通过先求数组的和
        //如果数组的和为奇数，则只包含正整数的非空数组不可能分割成两个相等的子集
        //数组和Sum为偶数的话，其和的一半target即为 从数组中找到集合等于target
        //转化为背包问题，每个数组的数字有两个选择，放进或者不放，背包的和为target
        //状态dp(i,sub_sum) = x 表示对于前i个数字，当容量为sub_sum时，若x为true时，则更好可以将背包装满
        //如果x为false时，则不能将背包装满
        //状态就是 背包的容量和可选择的物品，选择就是放进背包或者不放进背包
        //状态转移 dp(i,sub_sum) = dp(i-1,sub_sum-nums[i-1]) {i不放进背包} || dp(i-1,sub_sum) {i不放进背包}
        //初始状态 base case : dp(...,0) = true (背包容量为0) dp(0,...) = false (没有可选的物品)
        int sum = 0;
        for(auto ele:nums)
            sum += ele;
        if(sum % 2 != 0)
            return false;
        int target = sum/2;
        int n = nums.size();
        //由于只与上一层有关，采用状态压缩
        // vector<vector<bool>> dp = vector<vector<bool>>(n+1,vector<bool>(target+1,false));
        //初始化
        // for(int i = 0;i <= n;i++)
        //     dp[i][0] = true;

        vector<bool> dp = vector<bool>(target+1,false);
        dp[0] = true;

        //由于只与上一层有关，采用状态压缩
        for(int i = 1;i <= n;i++){
            //每一行只与上一行相关
            //遍历直到背包容量为1
            //由于后面跟上一层的前面相关所以 从后往前遍历
            for(int j = target;j >= 1;j--){
                if(j - nums[i-1] >= 0)
                    dp[j] = dp[j] || dp[j-nums[i-1]];
                //当j-nums[i-1] < 0,则跟上一层一样
                // else
                //     dp[i][j] = dp[i-1][j];
            }
        }
        return dp[target];
    }
};

int main(){
    vector<int> nums = {1,5,11,5};
    bool res = Solution().canPartition2(nums);
    //result
    //true
    //数组可以分割成 [1, 5, 5] 和 [11]
    cout<<boolalpha<<res<<endl;
}