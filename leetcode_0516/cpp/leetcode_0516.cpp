//
// Created by wangzy on 2022/5/2.
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

using namespace std;

class Solution {
public:
    int longestPalindromeSubseq(string s) {
        //思路：动态规划
        //根据回文子序列的定义可知
        //重叠子问题 dp[i,j] 回文子序列长度
        //初始状态 dp[i,i] 为 1
        //状态 变量 是i,j
        //状态转移方程 dp[i,j] = dp[i+1,j-1] + 2 | s[i]==s[j] & j-i>=2
        //dp[i,j] = max(dp[i,j-1],dp[i+1,j]) | s[i]!=s[j]
        //由于dp[i,j] 只与dp[i+1,j](下),dp[i,j-1](左),dp[i+1,j-1](左下)有关
        //通过状态转移方程可知，遍历顺序从下向上，从左向右
        int len = s.size();
        //状态压缩
        vector<int> dp = vector<int>(len,0);
        for(int i = 0;i < len;i++)
            dp[i] = 1;
        for(int i = len - 2;i >= 0;i--){
            //假设初始 dp[i+1,j-1] 设置为 0(左下)
            //dp[i+1,j-1] = 0
            int pre = 0;
            for(int j = i+1;j < len;j++){
                //temp = dp[i+1][j]
                int temp = dp[j];
                if(s[i] == s[j]){
                    // dp[i][j] = dp[i+1][j-1]+2;
                    dp[j] = pre + 2;
                }else{
                    // dp[i][j] = max(dp[i+1][j],dp[i][j-1])
                    dp[j] = max(dp[j],dp[j-1]);
                }
                pre = temp;
            }
        }
        return dp[len-1];
    }
};

int main(){
    string s = "bbbab";
    //子序列定义为：不改变剩余字符顺序的情况下，删除某些字符或者不删除任何字符形成的一个序列
    int res = Solution().longestPalindromeSubseq(s);
    cout<<res<<endl;
    //result
    //4
    //一个可能的最长回文子序列为 "bbbb"
}
