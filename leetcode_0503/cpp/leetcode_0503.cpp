//
// Created by wzy on 2022/3/15.
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
    vector<int> nextGreaterElements(vector<int>& nums) {
        //单调栈 + 循环数组
        //模拟栈 存储数组索引
        //遍历数组，当遇到当前值大于 栈顶索引对应元素循环执行，则将对应索引改为当前值
        //保持栈始终 按照对应数组索引值的 递减顺序 或者栈为空
        //最终将栈中的元素取出 对应索引位置 赋值为 -1
        //单调栈
        stack<int> s;
        vector<int> res(nums.size(),-1);
        int sz = nums.size() * 2;
        for(int i = 0;i < sz;i++){
            int j = i % nums.size();
            while(!s.empty() && nums[s.top()] < nums[j]){
                res[s.top()] = nums[j];
                s.pop();
            }
            s.push(j);
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
//    vector<int> vec = {1,2,1};
//    vector<int> vec = {1,2,3,4,3};
    //result
    //[2,3,4,-1,4]
    vector<int> vec = {5,4,3,2,1};
    //result
    //[-1,5,5,5,5]
    vector<int> res = Solution().nextGreaterElements(vec);
    printVec(res);
}