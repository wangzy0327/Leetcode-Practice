//
// Created by wangzy on 2022/4/17.
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
    vector<vector<int>> permute(vector<int>& nums) {
        //思路：回溯 dfs 每次交换当前元素与后序元素然后向后移动序列
        vector<vector<int>> res;
        vector<int> sub;
        dfs(res,nums,sub,0,nums.size()-1);
        return res;
    }
private:
    void dfs(vector<vector<int>>& res,vector<int>& nums,vector<int>& sub,int start,int end){
        if(start > end)
            return ;
        else if(start == end){
            sub.push_back(nums[start]);
            res.push_back(sub);
            sub.pop_back();
            return ;
        }
        for(int i = start;i <= end;i++){
            swap(nums[start],nums[i]);
            sub.push_back(nums[start]);
            dfs(res,nums,sub,start+1,end);
            sub.pop_back();
            swap(nums[start],nums[i]);
        }
    }
};


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

int main(){
    vector<int> nums = {1,2,3};
    //nums = [1,2,3]
    auto res = Solution().permute(nums);
    printVecArr(res);
    //[[1,2,3],[1,3,2],[2,1,3],[2,3,1],[3,1,2],[3,2,1]]
}

