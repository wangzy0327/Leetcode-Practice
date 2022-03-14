//
// Created by wzy on 2022/3/14.
//

#include<iostream>
#include<queue>
#include<vector>
#include <algorithm>
#include <unordered_map>
#include <sstream>
#include <typeinfo>
#include <climits>

using namespace std;

class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        //前K个高频元素 会用到 优先队列，而且优先队列的比较函数应该以频次作为标准
        //元素出现频次统计 用到 哈希表
        unordered_map<int,int> record;
        for(auto ele:nums)
            record[ele]++;
        //采用lambda表达式定义 函数对象
        auto my_cmp = [](const pair<int,int>& a,const pair<int,int>& b)-> bool {return a.second > b.second;};
        //priority_queue 默认使用less<T> 比较函数，而且默认最大的放在堆顶(默认大顶堆)
        //采用小顶堆(优先级高的在头部)，频率最低的元素在堆顶
        //第三个泛型参数为 函数对象类型 而不是函数对象
        priority_queue<pair<int,int>,vector<pair<int,int>>, decltype(my_cmp)> q(my_cmp);
        for(auto p : record){
            if(q.size() < k)
                q.push(p);
            else if(p.second > q.top().second){
                q.pop();
                q.push(p);
            }
        }
        vector<int> vec;
        while(q.size()){
            vec.push_back(q.top().first);
            q.pop();
        }
        return vec;
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
    vector<int> vec = {1,1,1,2,2,3};
    int k = 2;
    vector<int> res = Solution().topKFrequent(vec,k);
    printVec(res);
    //res
    //[1,2]
}

