//
// Created by wzy on 2022/5/10.
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
    int coinChange(vector<int>& coins, int amount) {
        //思路：动态规划
        //整数amount总金额所需最少的硬币个数，由前面重叠子问题amount-coin[i]所需的硬币个数+1构成
        //dp[i]表示金额i所需最少的硬币个数
        //初始状态 base case dp[0] = 0 不需要硬币就能组成
        //状态转移方程 dp[i] = min(dp[i- coins[j]] + 1) {j -[1,coins.size() && i - coins[j] >= 0]}
        //初始化所有dp为amount+1 硬币数量
        vector<int> dp = vector<int>(amount+1,amount+1);
        dp[0] = 0;
        for(int i = 1;i <= amount;i++){
            for(int j = 0;j < coins.size();j++){
                if(i - coins[j] >= 0)
                    dp[i] = min(dp[i],dp[i-coins[j]]+1);
            }
        }
//        printVec(dp);
        return (dp[amount]==amount+1)?-1:dp[amount];
    }
};

int main(){
    vector<int> coins = {1,2,5};
    int amount = 11;
    //result
    //3
    // 11 = 5 + 5 + 1
//    vector<int> coins = {2};
//    int amount = 3;
    //result
    //-1
//    vector<int> coins = {1};
//    int amount = 0;
    //result
    //0
    int res = Solution().coinChange(coins,amount);
    cout<<res<<endl;
}