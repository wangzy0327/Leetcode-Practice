//
// Created by wzy on 2022/3/17.
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
    bool isValid(string s) {
        stack<char> stk;
        for(int i = 0;i < s.size();i++){
            if(s[i] == '(' || s[i] == '[' || s[i] == '{')
                stk.push(s[i]);
            else{
                //遇到右半边括号
                if(stk.size() == 0)
                    return false;
                else{
                    char top_char = stk.top();
                    if(s[i] == ')' && top_char != '('){
                        return false;
                    }else if(s[i] == ']' && top_char != '['){
                        return false;
                    }else if(s[i] == '}' && top_char != '{'){
                        return false;
                    }
                    //否则匹配 出栈
                    stk.pop();
                }
            }
        }
        return stk.empty();
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
//    string s = "{[]}";
//    string s = "([)]";
    string s = "()[]{}";
    cout<<Solution().isValid(s)<<endl;
}