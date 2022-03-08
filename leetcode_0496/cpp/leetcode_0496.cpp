//
// Created by wangzy on 2022/3/8.
//
#include <iostream>
#include <vector>
#include <unordered_map>
#include <stack>
#include <sstream>

using namespace std;

class Solution {
public:
    vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2) {
        //哈希表+单调栈
        unordered_map<int,int> record;
        int i = 0;
        for(auto num:nums2)
            record[num] = i++;
        stack<int> mono_stk;
        //可以预先处理nums2使查询nums1中的每个元素在nums2中对应位置的右边第一个更大的元素时不需要再遍历，于是问题分解为两个子问题。
        //1.如何高效的计算nums2中每个元素右边的第一个更大的值(单调栈 从右往左遍历)
        //2.如何存储第1个问题的结果(采用数组存储 不存在右第一更大存-1)
        vector<int> ans(nums2.size(),0);
        for(int j = nums2.size()-1;j >= 0;j-- ){
            //如果当前元素大于栈顶元素，则一直弹出栈顶元素
            while(!mono_stk.empty() && nums2[j] >= mono_stk.top())
                mono_stk.pop();
            //将栈顶元素(大于当前元素)或-1放入结果集中
            ans[j] = (mono_stk.empty())?-1:mono_stk.top();
            //当前元素进栈
            mono_stk.push(nums2[j]);
        }
        i = 0;
        vector<int> res(nums1.size(),0);
        for(auto num:nums1)
            res[i++] = ans[record[num]];
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

int main(int argc,char* argv[]){
    vector<int> nums1 = {4,1,2};
    vector<int> nums2 = {1,3,4,2};
    vector<int> res = Solution().nextGreaterElement(nums1,nums2);
    printVec(res);
}

