//
// Created by wangzy on 2022/7/9.
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
#include <cstring>

using namespace std;


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

class Solution {
private:
    vector<int> tmp;
    vector<vector<int>> res;
    void dfs(int cur,int lastEle,vector<int>& nums){
        if(cur == nums.size()){
            //扫描到数组结尾
            if(tmp.size() >= 2)
                res.push_back(tmp);
            return ;
        }
        //1.选择当前元素
        //递增再加入
        if(nums[cur] >= lastEle){
            tmp.push_back(nums[cur]);
            dfs(cur+1,nums[cur],nums);
            tmp.pop_back();
        }
        //2.跳过当前元素
        //跳过的nums[cur]元素不加入,
        //如果当前元素跟上一个元素相等说明已经计算过重复元素了,不进行下面递归
        if(nums[cur] != lastEle){
            //当前元素不更新到lastEle
            dfs(cur+1,lastEle,nums);
        }
    }
public:
    vector<vector<int>> findSubsequences(vector<int>& nums) {
        //思路：采用回溯
        //去重方式通过比较上一个元素跟当前元素,如果相同的话可以跳过当前元素
        //去重防止出现: 1,2,2,3 -> [1,2,3] , [1,2,3] 在本例中，前一个选择了2,后面可以不选跳过直接判断3
        //否则可能出现 前一个2没选，后一个选了2，导致重复[1,2,3]出现, 所以在递归结构中需要保存上一个索引元素

        dfs(0,INT_MIN,nums);
        return res;
    }
};

int main(){
    vector<int> nums = {4,6,7,7};
    vector<vector<int>> res = Solution().findSubsequences(nums);
    printVecArr(res);
    //[[4,6,7,7],[4,6,7],[4,6],[4,7,7],[4,7],[6,7,7],[6,7],[7,7]]
    return 0;
}
