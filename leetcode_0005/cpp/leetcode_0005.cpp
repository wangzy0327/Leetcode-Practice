//
// Created by wangzy on 2022/5/1.
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

//时间复杂度O(n*n*n) 超时
class Solution {
public:
    string longestPalindrome(string s) {
        //思路：动态规划 dp[i]表示以i结尾的最长回文子串
        //dp[i]的最长回文子串判定需要依次遍历到索引为0的位置
        if(s.size() == 0)
            return "";
        int max_len = 0;
        string max_palindrome = "";
        vector<int> dp = vector<int>(s.size(),0);
        for(int i = 0;i < dp.size();i++){
            for(int j = i;j >= 0;j--){
                if(isPalindrome(s,j,i)){
                    if(i - j + 1 > max_len){
                        max_len = i - j + 1;
                        max_palindrome = s.substr(j,max_len);
                    }
                }
            }
        }
        return max_palindrome;
    }
private:
    bool isPalindrome(const string& s,int start,int end)    {
        while(start < end){
            if(s[start] != s[end])
                return false;
            else{
                start++;end--;
            }
        }
        return true;
    }
};

class Solution2 {
public:
    string longestPalindrome(string s) {
        //思路：动态规划 用dp[i,j]来表示是否为回文字符串
        //初始状态dp[i,i]为true
        //dp[i,j] = dp[i+1,j-1] | s[i] == s[j]
        if(s.size() <= 1)
            return s;
        //记录最长回文子串的起始位置和长度
        int start = 0;
        int max_len = 1;
        int sz = s.size();
        vector<vector<int>> dp = vector<vector<int>>(sz,vector<int>(sz,0));
        for(int i = sz-1;i >= 0;i--){
            dp[i][i] = 1;
            if(i + 1 < sz && s[i] == s[i+1]){
                dp[i][i+1] = 1;
                start = i;
                max_len = 2;
            }
        }

        //遍历从下往上 从左往右
        for(int i = sz - 2;i >= 0;i--){
            for(int j = i + 2;j < sz;j++){
                if(s[i] == s[j]){
                    dp[i][j] = dp[i+1][j-1];
                    if(dp[i][j] && j - i + 1 >= max_len){
                        start = i;
                        max_len = j-i+1;
                    }
                }else{
                    dp[i][j] = 0;
                }
            }
        }
        return s.substr(start,max_len);
    }
};

int main(){
    string s = "babad";
    string res = Solution2().longestPalindrome(s);
    cout<<res<<endl;
    //result
    //"bab"  "aba" 同样是符合题意的答案。
}
