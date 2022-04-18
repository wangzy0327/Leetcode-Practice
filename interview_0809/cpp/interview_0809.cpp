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
    vector<string> generateParenthesis(int n) {
        //思路：采用回溯 , 由于括号需要配对，所以必定已经进入集合的左括号数量大于等于右括号
        //如果集合中左括号大于右括号则可以放入右括号，否则只能放入左括号
        vector<string> res;
        string sub = "";
        //设置左括号、右括号数量
        int lNum = 0;
        int rNum = 0;
        dfs(res,sub,n,lNum,rNum);
        return res;
    }
private:
    void dfs(vector<string>& res,string& sub,int n,int lNum,int rNum){
        if(sub.size() == 2*n){
            res.push_back(sub);
            return ;
        }
        if(lNum < n){
            //左括号等于右括号数量时并且 左括号数量不超过n 才能放置左括号
            sub += "(";
            dfs(res,sub,n,lNum + 1,rNum);
            sub = sub.substr(0,sub.size()-1);
        }
        //左括号数量大于等于右括号数量( 可以放置左括号/右括号 )
        if(lNum > rNum){
            sub += ")";
            dfs(res,sub,n,lNum,rNum+1);
            sub = sub.substr(0,sub.size()-1);
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
    int n = 3;
    auto res = Solution().generateParenthesis(n);
    printVec(res);
    //[((())),(()()),(())(),()(()),()()()]
}