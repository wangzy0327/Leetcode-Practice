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
    int calculate(string s) {
        //将整个表达式计算看成是具有递归性质的一个数的抽象
        //具体到细节来讲，将每个数通过跟运算符的结合表示为一个整数
        //2-1 可以看做 2 + -1, 对于乘除法来说计算优先级高，计算为一个整数
        //((stack.top()) preSign  num) 为一个整数
        //处理乘除法，这里呢需要提前存储前一个操作数和前一个操作运算符
        //扩展的话，可以根据栈来存储运算符来进行运算符优先级判断
        //细节的话，这里需要提前存储一个 操作符+ 和前一个操作数0
        //对于括号的处理采用递归的思路
        deque<char> deq;
        for(char c:s)
            deq.push_back(c);
        int res = helper(deq);
        return res;
    }
private:
    int helper(deque<char> deq)    {
        //操作数栈
        stack<int> stk;
        //提前的符号设置为+
        char preSign = '+';
        int num = 0;
        while(deq.size()){
            char c = deq.front();
            deq.pop_front();
            if(isdigit(c)){
                num = num * 10 + (c - '0');
            }
            if(c == '('){
                num = helper(deq);
            }
            if(!isdigit(c) && !isspace(c) || deq.size() == 0){
                if(preSign == '+')
                    stk.push(num);
                else if(preSign == '-')
                    stk.push(-num);
                else if(preSign == '*'){
                    int pre_num = stk.top();
                    stk.pop();
                    stk.push(pre_num * num);
                }
                else if(preSign == '/'){
                    int pre_num = stk.top();
                    stk.pop();
                    stk.push(pre_num / num);
                }
                num = 0;
                preSign = c;
            }
            if(c == ')'){
                break;
            }
        }
        int res = 0;
        while(stk.size()){
            res += stk.top();
            stk.pop();
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
//    string s = "1 + 1";
//    string s = "(1+(4+5+2)-3)+(6+8)";
    // result 23
    string s = " 3+5 / 2 ";
    //result 5
    int res = Solution().calculate(s);
    cout<<res<<endl;
}


