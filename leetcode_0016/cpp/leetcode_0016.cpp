//
// Created by wangzy on 2022/4/16.
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
    int threeSumClosest(vector<int>& nums, int target) {
        //思路：先排序，然后用双指针进行寻找
        sort(nums.begin(),nums.end());
        //设置三数之和与target之差
        ans = INT_MAX;
        for(int i = 0;i < nums.size();i++){
            if(ans != 0)
                dfs(nums,target,nums[i],i+1,nums.size()-1);
            else
                return min_sum;
        }
        return min_sum;
    }
private:
    int ans;
    int min_sum;
    void dfs(vector<int>& nums,int target,int num,int start,int end){
        while(start < end){
            int sum = num + nums[start] + nums[end];
            if(abs(sum - target) < ans){
                ans = abs(sum - target);
                min_sum = sum;
            }
            if(sum <= target){
                start++;
            }else if(sum > target){
                end--;
            }
        }
    }
};

int main(){
    vector<int> nums = {0,0,1,2,1,3};
    int target = 1;
    int res = Solution().threeSumClosest(nums,target);
    cout<<res<<endl;
    //result
    //与target最接近的和是 1 (0,0,1)
    //1
}