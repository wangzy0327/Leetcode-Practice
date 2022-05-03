//
// Created by wangzy on 2022/5/3.
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
    int longestCommonSubsequence(string text1, string text2) {
        //思路：动态规划
        //重叠子问题：text1,text2索引向右递增的子序列长度
        //初始状态: text1="",text2="",最长公共子序列为0
        //状态：text1,text2的逐渐递增的索引长度i,j
        //状态转移方程: dp[i,j] = dp[i-1,j-1] + 1 | s[i]==s[j]
        //dp[i,j] = max(dp[i-1,j],dp[i,j-1]) | s[i]!=s[j]
        //状态转移方程从左到右，从上到下
        int m = text1.size();
        int n = text2.size();
//        vector<vector<int>> dp = vector<vector<int>>(m+1,vector<int>(n+1,0));
        //因为dp只跟左上，左，上三个相邻元素相关
        vector<int> dp = vector<int>(n+1,0);
        for(int i = 0;i < m;i++){
            //首先存储dp[i][j] 左上
            int pre = dp[0];
            for(int j = 0;j < n;j++){
                //存储正上 dp[i][j+1]
                int temp = dp[j+1];
                if(text1[i] == text2[j]){
                    //dp[i+1][j+1] = dp[i][j] + 1;
                    dp[j+1] = pre + 1;
                }else{
                    //dp[i+1][j+1] = max(dp[i][j+1],dp[i+1][j]);
                    dp[j+1] = max(temp,dp[j]);
                }
                //目前的正上为下一个的左上
                pre = temp;
            }
        }
        return dp[n];
    }
};

int main(){
    //一个字符串的 子序列 是指这样一个新的字符串：它是由原字符串在不改变字符的相对顺序的情况下删除某些字符（也可以不删除任何字符）后组成的新字符串
    string text1 = "abcde";
    string text2 = "ace";
    //result
    //3  最长公共子序列是 "abc" ，它的长度为 3
//    string text1 = "abc";
//    string text2 = "def";
    //result
    //0  两个字符串没有公共子序列，返回 0
    int res = Solution().longestCommonSubsequence(text1,text2);
    cout<<res<<endl;
}