//
// Created by wzy on 2022/3/18.
//

#include<iostream>
#include<queue>
#include<vector>
#include <algorithm>
#include <unordered_map>
#include <list>
#include <deque>
#include <stack>
#include <sstream>
#include <typeinfo>
#include <climits>

using namespace std;

class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        if(nums.size() == 0)
            return {-1,-1};
        //如果要找到目标值的最左位置，索引搜索应向左偏移
        int begin_pos = find_begin_pos(nums,target);
        int end_pos = find_end_pos(nums,target);
        if(begin_pos < 0 || begin_pos >= nums.size() || nums[begin_pos] != target)
            return {-1,-1};
        return {begin_pos,end_pos};
    }
    int find_begin_pos(vector<int>& nums,int target){
        int left = 0;
        int right = nums.size();
        int mid = 0;
        //[left,right) 终止条件 left == right
        while(left < right){
            mid = left + (right - left)/2;
            if(nums[mid] == target)
                right = mid;
            else if(nums[mid] > target)
                right = mid;
            else if(nums[mid] < target)
                left = mid + 1;
        }
        return left;
    }
    int find_end_pos(vector<int>& nums,int target){
        int left = 0;
        int right = nums.size();
        int mid = 0;
        //[left,right) 终止条件 left == right
        while(left < right){
            mid = left + (right - left)/2;
            if(nums[mid] == target)
                left = mid + 1;
            else if(nums[mid] > target)
                right = mid;
            else if(nums[mid] < target)
                left = mid + 1;
        }
        return right - 1;
    }
};

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

int main() {
    vector<int> nums = {5,7,7,8,8,10};
    int target = 8;
    vector<int> res = Solution().searchRange(nums,target);
    printVec(res);
}