//
// Created by wangzy on 2022/4/30.
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
    int maxSubArray(vector<int>& nums) {
        //思路：设置arr(start,end)为子数组
        //如果arr[start,end]<0,则start++,否则end++,更新最大和
        if(nums.size() == 0)
            return 0;
        int max_sum = INT_MIN;
        int sub_arr = nums[0];
        int start = 0;
        int end = 0;
        //[start,end]
        while(start <= end && end < nums.size()){
            if(start <= end && sub_arr < 0){
                max_sum = max(max_sum,sub_arr);
                sub_arr -= nums[start++];
                if(start > end ){
                    if(end < nums.size() - 1)
                        sub_arr += nums[end+1];
                    end++;
                }
            }else if(start <= end && sub_arr >= 0){
                //start <= end && sub_arr >= 0
                max_sum = max(max_sum,sub_arr);
                if(end < nums.size() - 1)
                    sub_arr += nums[++end];
                else
                    end++;
            }
        }
        return max_sum;
    }
    int maxSubArray2(vector<int>& nums) {
        //思路：动态规划
        //假设nums的长度为n,下标从0到n-1
        //我们用 f(i)代表以第 i 个数结尾的「连续子数组的最大和」
        //我们要求的答案就是 max{f(i)} 0<i<n-1
        //如何求出f(i) = max{f(i-1)+nums[i] | nums[i]}
        //即如果f(i-1)为负,则f(i) = nums[i] 否则f(i) = f(i-1)+nums[i]
        //因为f(i)只跟f(i-1)有关，则可以用pre来存储f(i-1)
        if(nums.size() == 0)
            return 0;
        int pre = 0;
        int max_sum = nums[0];
        for(auto ele : nums){
            pre = max(pre+ele,ele);
            max_sum = max(max_sum,pre);
        }
        return max_sum;
    }
};

int main(){
    vector<int> nums = {-2,1,-3,4,-1,2,1,-5,4};
    //result
    //6 最大子数组{4,-1,2,1}
//    vector<int> nums = {1};
//result
//1
    int res = Solution().maxSubArray2(nums);
    cout<<res<<endl;
}