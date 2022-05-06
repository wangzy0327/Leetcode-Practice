//
// Created by wzy on 2022/5/6.
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

class Solution {
public:
    int minDistance(string word1, string word2) {
        //首先拿到问题先考虑一种最极端的情况
        //如果word1为"",word2="ros",那word1转换到word2需要3步，每步插入一个字符
        //如果word1为"horse",word2="",那word1转换到word2需要5步，每步删除一个元素
        //我们可以假设word1的i索引位置字符到word2的j索引位置字符所需要的步数依赖于
        //dp[i-1,j-1](替换一个元素),dp[i-1,j](删除一个元素),dp[i,j-1](添加一个元素)
        //dp[i,j]代表word1从字符i到word2的字符j转换所需要的最少步数
        //当然这里有特殊情况，如果i索引的字符跟j索引的字符相等，则不需要替换直接跳过
        //状态转移方程: dp[i,j] = min(dp[i-1,j-1],dp[i-1,j],dp[i,j-1])+1| {i!=j}
        //dp[i,j] = min(dp[i-1,j-1],dp[i-1,j]+1,dp[i,j-1]+1) | {i==j}
        //初始状态：dp[0,j] = j , dp[i,0] = i
        //每个dp状态只跟左，左上，上有关 可状态压缩

        int m = word1.size();
        int n = word2.size();
        //设置word1到word2所需要的距离最长为 m + n
//        vector<vector<int>> dp = vector<vector<int>>(m+1,vector<int>(n+1,m+n));
//        for(int i = 0;i < dp.size();i++)
//            dp[i][0] = i;
//        for(int j = 0;j < dp[0].size();j++)
//            dp[0][j] = j;
         vector<int> dp = vector<int>(n+1,m+n);
        //初始化dp[][]边界
         for(int i = 0;i < n+1;i++)
             dp[i] = i;
        for(int i = 1;i < m+1;i++){
            //第一个左上
             int pre = i-1;
            //注意 这里也需要更新左边值
             dp[0] = i;
            for(int j = 1;j < n+1;j++){
                //当前的位置就是下一个的左上
                 int nextLeftUp = dp[j];
                if(word1[i-1] == word2[j-1]){
//                    dp[i][j] = min(dp[i][j-1]+1,min(dp[i-1][j-1],dp[i-1][j]+1));
                     dp[j] = min(dp[j-1]+1,min(pre,dp[j]+1));
                }else{
//                    dp[i][j] = min(dp[i][j-1],min(dp[i-1][j-1],dp[i-1][j])) + 1;
                     dp[j] = min(dp[j-1],min(pre,dp[j]))+1;
                }
                //更新下一个左上
                 pre = nextLeftUp;
            }
//            printVec(dp);
        }
        return dp[n];
    }
};

int main(){
    string word1 = "intention";
    string word2 = "execution";
    int res = Solution().minDistance(word1,word2);
    cout<<res<<endl;
    //result 5
    /*
     *  intention -> inention (删除 't')
        inention -> enention (将 'i' 替换为 'e')
        enention -> exention (将 'n' 替换为 'x')
        exention -> exection (将 'n' 替换为 'c')
        exection -> execution (插入 'u')
     *
     * */
}