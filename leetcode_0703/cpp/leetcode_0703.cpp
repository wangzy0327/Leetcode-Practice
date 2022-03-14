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

class KthLargest {
private:
    int k;
    //最小堆，堆顶为最小元素
    priority_queue<int,vector<int>,greater<int>> pq;
public:
    KthLargest(int k, vector<int>& nums) {
        this->k = k;
        //只存储前k大个元素
        for(int i = 0;i < nums.size();i++)
            add(nums[i]);
    }
    //时间复杂度为O(klogk)
    int add(int val) {
        if(pq.size() < k)
            pq.push(val);
        else if(val > pq.top()){
            pq.pop();
            pq.push(val);
        }
        return pq.top();
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
    int k = 3;
    vector<int> nums = {4,5,8,2};
    KthLargest* kthLargest = new KthLargest(k,nums);
    vector<int> res;
    res.push_back(kthLargest->add(3));
    res.push_back(kthLargest->add(5));
    res.push_back(kthLargest->add(10));
    res.push_back(kthLargest->add(9));
    res.push_back(kthLargest->add(4));
    printVec(res);
    //result
    //[4,5,5,8,8]
    delete kthLargest;
}
