//
// Created by wzy on 2022/4/24.
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
    //exceed time limited O(n*n)
    int subarraySum2(vector<int>& nums, int k) {
        //思路：前缀和 计算数组的前缀和，而后遍历做差求解子数组的和
        vector<int> sum;
        int s = 0;
        for(int i = 0;i < nums.size();i++){
            s += nums[i];
            sum.push_back(s);
        }
        int count = 0;
        //子数组个数依次增加
        for(int j = 1;j <= nums.size();j++){
            int pre = 0;
            //前缀和子数组索引
            for(int t = j - 1;t < sum.size();t++){
                if(sum[t] - pre == k)
                    count++;
                //更新当前前缀和前j之前的前缀和(间隔为j)
                pre = sum[t + 1 - j];
            }
        }
        return count;
    }
    //思路:转化求子数组的和为k 为 寻找前缀和为sum[i] - k的个数
    int subarraySum(vector<int>& nums, int k) {
        //前缀和+哈希
        //原先寻找sum[i...j]的和是否为k,需要每次遍历j和i,结果就为O(n*n)
        //现在转化为寻找sum[i...j] - k的前缀和的个数(用哈希记录)
        int count = 0;
        unordered_map<int,int> record;
        int sum = 0;
        //初始前缀0以前的子数组为1
        record[0] = 1;
        for(int i = 0;i < nums.size();i++){
            sum += nums[i];
            if(record[sum-k])
                count += record[sum-k];
            record[sum] += 1;
        }
        return count;
    }
};

int main(){
    vector<int> nums = {1,2,3};
    int k = 3;
    int res = Solution().subarraySum(nums,k);
    cout<<res<<endl;
    //result
    //2
}