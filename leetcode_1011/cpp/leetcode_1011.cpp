//
// Created by wangzy on 2022/3/19.
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
    int shipWithinDays(vector<int>& weights, int days) {
        //存在一个运载能力下限Xans,当运载能力X >= Xans,则可以在days天内完成运载
        //当 X < Xans,多于days天才能完成 运送货物。则Xans就是我们要找的运载能力下限
        // max(weights[])<= Xans <= Σ(weights[])
        // 这个范围是单调非递减，可以通过二分来找寻最合适的Xans
        // 对 Xans运载能力 判断是够能在指定时间内运送货物满足 贪心算法(只要连续的包裹不大于 Xans) 并在指定时间完成即可
        int sum = sumWeight(weights);
        int max_weight = maxWeight(weights);
        int left = max_weight;
        int right = sum;
        //二分查找 第一个满足 运载能力的重量
        //终止条件是 left == right, [left,right)为空
        //最终结束的right 位置就是刚满足的位置(向左偏移)
        while(left < right){
            int mid = left + (right - left)/2;
            if(canFinish(weights,mid,days)){
                right = mid;
            }else{
                left = mid + 1;
            }
        }
        return left;
    }
private:
    bool canFinish(vector<int>& weights,int cap,int days){
        int cap_ans = cap;
        for(int i = 0;i < weights.size();){
            //保证每次运送货物不超过 cap
            if(cap - weights[i] >= 0)
                cap -= weights[i++];
            else{
                days--;
                cap = cap_ans;
            }
            if(days < 0)
                return false;
        }
        return --days >= 0;
    }
    int maxWeight(vector<int>& weights){
        int max_value = INT_MIN;
        for(auto ele:weights)
            if(max_value < ele)
                max_value = ele;
        return max_value;
    }
    int sumWeight(vector<int>& weights){
        int sum = 0;
        for(auto ele:weights)
            sum += ele;
        return sum;
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
    vector<int> vec = {3,2,2,4,1,4};
    int days = 3;
    int res = Solution().shipWithinDays(vec,days);
    //result
    //6
    cout<<res<<endl;
}
