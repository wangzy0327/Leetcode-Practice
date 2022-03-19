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
    vector<int> twoSum(vector<int>& numbers, int target) {
        int left = 0;
        int right = numbers.size() - 1;
        int sum = 0;
        while(left < right){
            sum = numbers[left] + numbers[right];
            if(sum == target)
                return vector<int>{left+1,right+1};
            else if(sum < target)
                left++;
            else if(sum > target)
                right--;
        }
        return vector<int>{-1,-1};
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
    vector<int> vec = {2,7,11,15};
    int target = 9;
    //下标从1开始
    vector<int> res = Solution().twoSum(vec,target);
    printVec(res);
    //result
    //[1,2]
}

