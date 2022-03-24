//
// Created by wzy on 2022/3/24.
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
    vector<vector<int>> threeSum(vector<int>& nums) {
        //暴力解法：O(n^3)
        //思路：先排序O(nlogn)，然后依次选定元素 对 后面的列表进行双指针判定O(n^2)
        //1.排序
        sort(nums.begin(),nums.end());
        vector<vector<int>> res;
        for(int i = 0;i < nums.size();i++){
            if(i == 0 || nums[i] != nums[i-1])
                dfs(nums[i],res,nums,i+1,nums.size()-1);
        }
        return res;
    }
private:
    void dfs(int target,vector<vector<int>>& res,vector<int>& nums,int start,int end){
        vector<int> sub;
        while(start < end){
            if(nums[start] + nums[end] < -target)
                start++;
            else if(nums[start] + nums[end] > -target)
                end--;
            else{
                //nums[start] + nums[end]  == target
                sub.push_back(target);
                sub.push_back(nums[start]);
                sub.push_back(nums[end]);
                res.push_back(sub);
                sub.clear();
                while(start < end && nums[start + 1] == nums[start])
                    start++;
                start++;
                while(start < end && nums[end] == nums[end - 1])
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
//    vector<int> nums = {-1,0,1,2,-1,-4};
    //result
    // [[-1,-1,2],[-1,0,1]]
    vector<int> nums = {-1,0,1,1,2,-1,-1,2,-1,2,-4};
    auto res = Solution().threeSum(nums);
    printVecArr(res);
    //result
    //[[-4,2,2],[-1,-1,2],[-1,0,1]]
}