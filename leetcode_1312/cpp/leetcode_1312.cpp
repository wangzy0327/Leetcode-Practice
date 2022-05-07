//
// Created by wzy on 2022/5/7.
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
    int minInsertions(string s) {
        //思路：动态规划 s[i,j]表示s的子串，如果s[i]==s[j],则只需考虑如何计算出s[i+1,j-1]的最小操作数
        //如果s[i]!=s[j],则需要计算出将s[i+1,j]变换到回文串需要最小操作数或变换到s[i,j-1]的最小操作数，加1
        //dp[i,j]表示字符串s[i,j]变换到回文字符串需要的最小插入操作次数
        //dp[i,j] = dp[i+1,j-1] {s[i]==s[j]} | min(dp[i,j-1],dp[i+1,j])+1 {s[i]!=s[j]}
        //初始状态 dp[i,i] = 0 {i>=0 && i < s.size()}
        // vector<vector<int>> dp = vector<vector<int>>(s.size(),vector<int>(s.size(),0));
        vector<int> dp = vector<int>(s.size(),0);
        //初始化 dp初始值 可省略
        // for(int i = 0;i < s.size();i++)
        //     dp[i][i] = 0;
        //dp 的操作从下向上，从左到右
        for(int i = s.size()-2;i >= 0;i--){
            //保存首个dp[i+1][j-1]
            int pre = 0;
            for(int j = i+1;j < s.size();j++){
                int nextLeftDown = dp[j];
                if(s[i] == s[j]){
                    // dp[i][j] = dp[i+1][j-1];
                    dp[j] = pre;
                }else{
                    // dp[i][j] = min(dp[i+1][j],dp[i][j-1]) + 1;
                    dp[j] = min(dp[j],dp[j-1]) + 1;
                }
                //更新下一个的左下
                pre = nextLeftDown;
            }
        }
        return dp[s.size()-1];
    }
};

int main(){
    string s = "leetcode";
    //result 5
    //插入 5 个字符后字符串变为 "leetcodocteel"
//    string s = "mbadm";
    //result 2
    //字符串可变为 "mbdadbm" 或者 "mdbabdm"
    int res = Solution().minInsertions(s);
    cout<<res<<endl;
}