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
    int findDuplicate(vector<int>& nums) {
        int n = nums.size();
        if(n == 0)
            return -1;
        vector<int> record(n+1,0);
        for(auto ele : nums){
            if(record[ele] == 0)
                record[ele] = 1;
            else
                return ele;
        }
        return -1;
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
    vector<int> vec = {1,3,4,2,2};
    int res = Solution().findDuplicate(vec);
    cout<<res<<endl;
    //result
    //2
}
