//
// Created by wzy on 2022/3/21.
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
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        //暴力：如果每次都要比较k窗口的数值，则时间复杂度为(k*n)
        //优化：这里只需要维持一个队列保证 队头到队尾是 单调队(队列里面存储索引，保证入队出队)
        //滑动窗口最大值, 这里需要维护一个大小为k的双端队列
        //双端队列里存储索引
        if(nums.size() == 0)
            return vector<int>{};
        deque<int> deq;
        vector<int> res;
        //[0,k-1] k个元素
        for(int i = 0;i < k;i++)
            helper(deq,nums,i);
        res.push_back(nums[deq.front()]);
        //[i,i+k)
        for(int i = k;i < nums.size();i++){
            int topIdx = deq.front();
            //如果队头索引是要移除的元素索引
            if(topIdx == i - k)
                deq.pop_front();
            helper(deq,nums,i);
            res.push_back(nums[deq.front()]);
        }
        return res;
    }
private:
    //保持双端队列里按照从大到小排序
    void helper(deque<int>& deq,vector<int>& nums,int k){
        if(deq.size() == 0)
            deq.push_back(k);
        else{
            while(!deq.empty() && nums[deq.back()] < nums[k])
                deq.pop_back();
            deq.push_back(k);
        }
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
    vector<int> nums = {1,3,-1,-3,5,3,6,7};
    int k = 3;
    vector<int> res = Solution().maxSlidingWindow(nums,k);
    printVec(res);
    //result
    //[3,3,5,5,6,7]
}