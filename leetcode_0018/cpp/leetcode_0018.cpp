//
// Created by wzy on 2022/3/25.
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
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        //暴力解法是 O(n^4)
        //这里先排序O(nlogn)，然后再根据双指针找到合适的组合 O(n^3)
        vector<vector<int>> res;
        sort(nums.begin(),nums.end());
        for(int i = 0;i < nums.size();i++){
            if(i == 0 || nums[i] != nums[i-1]){
                for(int j = i+1;j < nums.size();j++){
                    if(j == i+1 || nums[j] != nums[j-1]){
                        vector<int> sub{nums[i],nums[j]};
                        bfs(res,sub,nums,target-nums[i]-nums[j],j+1,nums.size()-1);
                    }
                }
            }
        }
        return res;
    }
private:
    void bfs(vector<vector<int>>& res,vector<int>& sub,vector<int>& nums,int target,int start,int end){
        while(start < end){
            if(nums[start]+nums[end] > target)
                end--;
            else if(nums[start]+nums[end] < target)
                start++;
            else{
                //nums[start] + nums[end] == target
                sub.push_back(nums[start]);
                sub.push_back(nums[end]);
                res.push_back(sub);
                sub.pop_back();
                sub.pop_back();
                while(start < end && nums[start+1] == nums[start])
                    start++;
                start++;
                while(start < end && nums[end-1] == nums[end])
                    end--;
                end--;
            }
        }
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

template<typename T>
string convertVecToStr(std::vector<T> l){
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
    return res;
}

template<typename T>
void printVecArr(std::vector<std::vector<T>> l){
    std::string res = "[";
    std::string tmp = "";
    std::stringstream ss;
    for(auto ele : l){
        ss << convertVecToStr(ele);
        ss >> tmp;
        res += tmp + ",";
        ss.clear();
    }
    res = res.substr(0,res.size()-1);
    res += "]";
    std::cout<<res<<std::endl;
}

int main() {
    vector<int> nums = {-2,-1,-1,1,1,2,2};
    int target = 0;
    //result
    //[[-2,-1,1,2],[-1,-1,1,1]]
//    vector<int> nums = {1,0,-1,0,-2,2};
//    int target = 0;
    //result
    //[[-2,-1,1,2],[-2,0,0,2],[-1,0,0,1]]
//    vector<int> nums = {2,2,2,2,2};
//    int target = 8;
    //result
    //[[2,2,2,2]]
    auto res = Solution().fourSum(nums,target);
    printVecArr(res);
    //[[-2,-1,1,2],[-1,-1,1,1]]
}