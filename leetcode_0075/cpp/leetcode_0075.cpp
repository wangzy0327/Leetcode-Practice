//
// Created by wzy on 2022/3/28.
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
#include <random>
#include <ctime>

using namespace std;

class Solution {
public:
    void sortColors(vector<int>& nums) {
        //由于只含有三个元素
        //采用三路快排的思想 遍历一遍完成排序
        //[start,l] == 0 [l+1,lt)==1 [r,end]==2
        //start==0 end==nums.size()-1
        int l = -1,r = nums.size();
        int lt = 0;
        int v = 1;
        while(lt < r){
            //<v
            if(nums[lt] < v)
                swap(nums[++l],nums[lt++]);
            else if(nums[lt] == v)
                lt++;
            else if(nums[lt] > v)
                swap(nums[lt],nums[--r]);
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
    vector<int> nums = {2,0,2,1,1,0};
    //result
    //[0,0,1,1,2,2]
    printVec(nums);
    Solution().sortColors(nums);
    printVec(nums);
}