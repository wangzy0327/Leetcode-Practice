//
// Created by wzy on 2022/3/14.
//
#include<iostream>
#include<queue>
#include<vector>
#include <algorithm>
#include <unordered_map>
#include <list>
#include <deque>
#include <sstream>
#include <typeinfo>
#include <climits>

using namespace std;

class Solution {
    /**
     如果当前的字符为数位，解析出一个数字（连续的多个数位）并进栈
    如果当前的字符为字母或者左括号，直接进栈
    如果当前的字符为右括号，开始出栈，一直到左括号出栈，出栈序列反转后拼接成一个字符串，此时取出栈顶的数字（此时栈顶一定是数字，想想为什么？）
    就是这个字符串应该出现的次数，我们根据这个次数和字符串构造出新的字符串并进栈
     */
private:
    //模拟整数栈
    deque<int> dq;
    //模拟字符串栈
    list<string> li;
public:
    string decodeString(string s) {
        for(int i = 0;i < s.size();){
            if(isdigit(s[i])){
                int num = 0;
                while(isdigit(s[i])){
                    num = num * 10 + s[i++] - '0';
                }
                dq.push_back(num);
            }
            if(s[i] == '['){
                li.push_back("[");
                i++;
                string str = "";
                while(isalpha(s[i])){
                    str += s[i++];
                }
                li.push_back(str);
            }
            if(s[i] == ']'){
                i++;
                vector<string> tmp;
                string str = "";
                while(li.back() != "["){
                    tmp.push_back(li.back());
                    li.pop_back();
                }
                //去除左半边括号
                li.pop_back();
                for(int k = tmp.size() - 1;k >= 0;k--)
                    str += tmp[k];
                tmp.clear();
                //取数字
                int n  = dq.back();
                dq.pop_back();
                string r = "";
                for(int j = 0;j < n;j++)
                    r += str;
                li.push_back(r);
            }
            if(isalpha(s[i])){
                string str = "";
                while(i < s.size() && isalpha(s[i]))
                    str += s[i++];
                li.push_back(str);
            }
        }
        string res = "";
        while(li.size()){
            res += li.front();
            li.pop_front();
        }
        return res;
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

int main(){
//    string s = "3[a]2[bc]";
//    string s = "3[a2[c]]";
    string s = "2[abc]3[cd]ef";
    //result
    //abcabccdcdcdef
    string res = Solution().decodeString(s);
    cout<<res<<endl;

}
