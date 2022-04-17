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
    vector<vector<int>> combine(int n, int k) {
        //思路：由于是组合，就不交换元素的先后顺序
        //而是每次递归
        vector<vector<int>> res;
        vector<int> sub;
        dfs(res,sub,n,1,k);
        return res;
    }
private:
    void dfs(vector<vector<int>>& res,vector<int>& sub,int n,int start,int k){
        if(sub.size() == k){
            res.push_back(sub);
            return ;
        }
        for(int i = start;i <= n;i++){
            if(n - start + 1 + sub.size() < k)
                return ;
            sub.push_back(i);
            dfs(res,sub,n,i+1,k);
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
    int n = 4;int k = 2;
    //nums = [1,2,3,4]  C(2,4)
    auto res = Solution().combine(n,k);
    printVecArr(res);
    //[[1,2],[1,3],[1,4],[2,3],[2,4],[3,4]]
}