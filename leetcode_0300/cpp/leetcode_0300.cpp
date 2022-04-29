//
// Created by wzy on 2022/4/29.
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
    int lengthOfLIS(vector<int>& nums) {
        //错误思路：使用栈来存储记录每个子序列长度
        //可能会出现递减导致不是以i开始的最长子序列
        //ep:[0,1,0,3,2,3] 本来以0开始的最长子序列应该为[0,1,2,3],但是由于有3则会导致最后统计出现[0,1,3]不是最长子序列
//        deque<int> dq;
//        int max_len = 0;
//        for(int i = 0;i < nums.size();i++){
//            dq.clear();
//            dq.push_back(nums[i]);
//            for(int j = i+1;j < nums.size();j++){
//                if(nums[j] > dq.back()){
//                    dq.push_back(nums[j]);
//                }
//            }
//            max_len = max(max_len,(int)dq.size());
//        }
//        return max_len;


        //思路：
        //由于题目要求 求最值问题，可考虑使用动态规划
        //针对i位置元素的状态可以记录为以nums[i]结尾的最长递增子序列长度为dp[i]
        //最重要的就是找出状态转移方程
        //可知每个位置的状态定义：以nums[i]结尾的最长递增子序列
        //状态转移方程
        //dp[i]=max(dp[j])+1,其中0≤j<i且num[j]<num[i]

        vector<int> arr = vector<int>(nums.size(),1);
        for(int i = 1;i < arr.size();i++){
            for(int j = 0;j < i;j++){
                if(nums[j] < nums[i]){
                    arr[i] = max(arr[i],arr[j]+1);
                }
            }
        }
        int res = 0;
        for(int i = 0;i < arr.size();i++){
            if(res < arr[i])
                res = arr[i];
        }
        return res;
    }
};

int main(){
    vector<int> nums = {0,1,0,3,2,3};
    //result 4  [0,1,2,3]
//    vector<int> nums = {10,9,2,5,3,7,101,18};
    //result 4  [2,3,7,101]
//    vector<int> nums = {7,7,7,7,7,7,7};
    //result 1
    int res = Solution().lengthOfLIS(nums);
    cout<<res<<endl;

}