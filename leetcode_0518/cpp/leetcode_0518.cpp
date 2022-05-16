//
// Created by wangzy on 2022/5/16.
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
    int change(int amount, vector<int>& coins) {
        //思路：动态规划
        //难点在于：要排除排列中可能重复的情况
        //因此在计算组合数时，依次使用硬币来保证后面的组合数与前面的组合数没有重复
        //ep: 3 = 1+1+1  3=2+1
        //在外层遍历时，只使用i以前的硬币种类比如[1,2],不使用5
        // dp[i] = for(+=dp[i-coin] {coin in coins})
        //dp[i] += dp[i-coin] {coin <= i <= amount}
        //初始化默认为 dp[0] = 1 只有当不选取任何硬币时，金额之和才为 0
        //假设coins = {1, 2, 3}，amount = 5。 凑出5的方案有三类：

        // 组合必须以硬币1结尾，且不能包含硬币1之后的其他硬币2， 3。假设这类方案数量为x1。
        // 组合必须以硬币2结尾，且不能包含硬币2之后的其他硬币3。假设这类方案数量为x2。
        // 组合必须以硬币3结尾。假设这类方案数量为x3
        vector<int> dp = vector<int>(amount+1,0);
        dp[0] = 1;
        for(auto coin : coins){
            for(int j = coin;j <= amount;j++){
                dp[j] += dp[j-coin];
            }
        }
        return dp[amount];
    }
};

int main(){
    int amount = 5;
    vector<int> coins = {1,2,5};
    int res = Solution().change(amount,coins);
    cout<<res<<endl;
    //result
    //4
}
