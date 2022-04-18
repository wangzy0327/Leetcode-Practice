//
// Created by wzy on 2022/4/18.
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
    vector<vector<int>> subsets(vector<int>& nums) {
        //思路：回溯
        vector<vector<int>> res;
        int sz = nums.size();
        vector<int> sub;
        //依次设置子集的元素个数
        for(int i = 0;i <= sz;i++)
            // sub.clear();
            dfs(res,sub,nums,0,i);
        return res;
    }
private:
    void dfs(vector<vector<int>>& res,vector<int>& sub,vector<int>& nums,int start,int k){
        if(sub.size() == k){
            res.push_back(sub);
            return ;
        }
        for(int i = start;i < nums.size();i++){
            //如果后序元素加上已有元素不足k则直接返回
            if(sub.size() + nums.size() - i + 1 < k)
                return ;
            sub.push_back(nums[i]);
            dfs(res,sub,nums,i+1,k);
            sub.pop_back();
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
    auto res = Solution().subsets(nums);
    printVecArr(res);
    //[],[1],[2],[3],[1,2],[1,3],[2,3],[1,2,3]]
}