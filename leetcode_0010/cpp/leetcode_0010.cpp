//
// Created by wzy on 2022/5/9.
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
    bool isMatch(string s, string p) {
        //思路:动态规划
        //如果pattern当前字符是'.'的话,则其可以匹配任意s字符串中的当前字符
        //如果pattern当前字符是'*'的话，则其匹配前一个pattern中字符0次或n次
        //dp[i,j]表示p的前i个字符是否跟s的前j个字符匹配
        //初始状态dp[0,0] = 1;1表示匹配,0表示不匹配
        //状态转移方程 dp[i,j] = dp[i-1,j-1] { p[i-1]=='.' | p[i-1] == s[j-1]}

        //dp[i,j] = dp[i-2,j]|dp[i-1][j]|dp[i][j-1] {(p[i-2]==s[j-1]} || p[i-2]=='.') && p[i] == '*' | {匹配0个|匹配1个|匹配多个}
        //dp[i,j] = dp[i-2][j] {(p[i-2] != s[j-1] && p[i-2] != '.') && p[i] == '*'}
        //初始状态 dp[0,0] = 1
        int m = p.size();
        int n = s.size();
        vector<vector<int>> dp = vector<vector<int>>(m + 1,vector<int>(n + 1,0));
        dp[0][0] = 1;
        //初始化 很重要
        // "" "c*" 匹配
        for(int i = 2;i <= m;i++){
            if(p[i-1] == '*')
                dp[i][0] = dp[i-2][0];
        }
        for(int i = 1;i < dp.size();i++){
            for(int j = 1;j < dp[i].size();j++){
                if(p[i-1] == s[j-1] || p[i-1] == '.'){
                    dp[i][j] = dp[i-1][j-1];
                }else if(p[i-1] == '*'){
                    //匹配0个
                    if(p[i-2] != s[j-1] && p[i-2]!= '.'){
                        dp[i][j] = dp[i-2][j];
                    }else {
                        //.*就相当于.. , 那就只要看前面匹不匹配就行
                        //匹配多个
                        dp[i][j] = (dp[i-2][j] | dp[i][j-1] | dp[i-1][j]);
                    }
                }
            }
        }
        printVecArr(dp);
        return dp[m][n];
    }
};


int main(){
//    string s = "aaa";
//    string p = "a*";
    //result
    //true
    //因为 '*' 代表可以匹配零个或多个前面的那一个元素, 在这里前面的元素就是 'a'。因此，字符串 "aa" 可被视为 'a' 重复了一次
    string s = "aab";
    string p = "c*a*b";
    //result
    //true
//    string s = "ab";
//    string p = ".*";
    //result
    //true
    //".*" 表示可匹配零个或多个（'*'）任意字符（'.'）
    bool res = Solution().isMatch(s,p);
    cout<<boolalpha<<res<<endl;

}