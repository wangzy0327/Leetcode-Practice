//
// Created by wangzy on 2022/7/23.
//

#include<iostream>
#include<queue>
#include<vector>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <list>
#include <deque>
#include <stack>
#include <sstream>
#include <typeinfo>
#include <climits>
#include <random>
#include <ctime>
#include <cstring>

using namespace std;

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

class Solution {
public:
    vector<int> singleNumbers(vector<int>& nums) {
        int num_xor = 0;
        int ano = 0;
        for(auto ele:nums)
            num_xor ^= ele;
        int pos = 0;
        cout<<"num_xor : "<<num_xor<<endl;
        int tmp = num_xor;
        while((tmp & 1) == 0){
            pos++;
            tmp = (num_xor>>pos);
        }
//        for(int tmp = (num_xor>>pos);(tmp&1) == 0;pos++);
        for(auto ele:nums){
            int tmp = ele >> pos;
            if((tmp & 1) == 0){
                ano ^= ele;
            }
        }
        cout<<"ano_xor : "<<ano<<endl;
        int res1 = num_xor^ano;
        int res2 = num_xor^res1;
        vector<int> res{res1,res2};
        return res;
    }
};

int main(){
//    vector<int> nums = {4,1,4,6};
    vector<int> nums = {1,2,10,4,1,4,3,3};
    vector<int> res = Solution().singleNumbers(nums);
    printVec(res);
}