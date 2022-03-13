//
// Created by wangzy on 2022/3/12.
//

#include<iostream>
#include<queue>
#include<vector>
#include <algorithm>
#include <climits>

using namespace std;

class Solution {
    static bool cmp(int a, int b) {
        return abs(a) > abs(b);
    }
public:
    int largestSumAfterKNegations(vector<int>& nums, int k) {
//  贪心的思路，局部最优：让绝对值大的负数变为正数，当前数值达到最大，整体最优：整个数组和达到最大。

// 局部最优可以推出全局最优。

// 那么如果将负数都转变为正数了，K依然大于0，此时的问题是一个有序正整数序列，如何转变K次正负，让 数组和 达到最大。

// 那么又是一个贪心：局部最优：只找数值最小的正整数进行反转，当前数值可以达到最大（例如正整数数组{5, 3, 1}，反转1 得到-1 比 反转5得到的-5 大多了），
// 全局最优：整个 数组和 达到最大。
/**
那么本题的解题步骤为：

第一步：将数组按照绝对值大小从大到小排序，**注意要按照绝对值的大小**
第二步：从前向后遍历，遇到负数将其变为正数，同时K--
第三步：如果K还大于0，那么反复转变数值最小的元素，将K用完
第四步：求和
*/
        sort(nums.begin(), nums.end(), cmp);       // 第一步
        for (int i = 0; i < nums.size(); i++) { // 第二步
            if (nums[i] < 0 && k > 0) {
                nums[i] *= -1;
                k--;
            }
        }
        if (k % 2 == 1) nums[nums.size() - 1] *= -1; // 第三步
        int result = 0;
        for (int a : nums) result += a;        // 第四步
        return result;
    }
};

class Solution2 {
public:
    int largestSumAfterKNegations(vector<int>& nums, int k) {
        //大顶堆
        priority_queue<int,vector<int>,less<int>> q;
        //小顶堆
        priority_queue<int,vector<int>,greater<int>> q2;
        int sum = 0;
        //记录最小的绝对值
        int min_abs = INT_MAX;
        //防止k 大于 nums 的长度
        int sz = min((int)nums.size(),k);
        for(int each : nums){
            sum += each;
            if(abs(min_abs) > abs(each) || (abs(min_abs) == abs(each) && each > 0))
                min_abs = each;
            if(q.size() == sz && q.top() > each){
                q.pop();
                q.push(each);
            }else if(q.size() < sz){
                q.push(each);
            }
        }
        for(int i = 0;i < sz;i++){
            q2.push(q.top());
            q.pop();
        }
        int pre_top = 0;
        while(sz){
            int t = q2.top();
            if(t < 0){
                sum -= 2*t;pre_top = q2.top();q2.pop();sz--;k--;
            }
            else
                break;
        }
        //说明还有剩余k
        int _k = (k)?(k):sz;
        if(_k){
            //需要注意的是，在之前将负数修改为正数的过程中，可能出现了（相较于原始数组中最小的正数）更小的正数，这一点不能忽略
            min_abs = (abs(pre_top) == abs(min_abs))?abs(pre_top):min_abs;
            if(_k%2 == 1 && min_abs > 0)
                sum -= 2*min_abs;
            if(_k%2 == 0 && min_abs < 0)
                sum += 2*min_abs;
        }
        return sum;
    }
};

int main(){
//    vector<int> nums = {-2,5,0,2,-2};
//    vector<int> nums = {-4,-2,-3};
//    vector<int> nums = {4,2,3};
//    int k = 1;
      vector<int> nums = {5,6,9,-3,3};
      int k = 2;
//      vector<int> nums = {-2,9,9,8,4};
//      int k = 5;
//    vector<int> nums = {8,-7,-3,-9,1,9,-6,-9,3};
//    int k = 3;
//    int k = 4;
//    int k = 8;
    int res = Solution2().largestSumAfterKNegations(nums,k);
    cout<<res<<endl;
}

