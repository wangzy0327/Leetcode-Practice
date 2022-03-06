//
// Created by wangzy on 2022/3/6.
//

#include <iostream>
#include <vector>
#include <unordered_map>
#include <sstream>

class Solution {
public:
    std::vector<int> twoSum(std::vector<int>& nums, int target) {
        std::unordered_map<int,int> record;
        for(int i = 0;i < nums.size();i++){
            int pairNum = target - nums[i];
            if(record.count(pairNum)){
                int j = record[pairNum];
                if(j < i)
                    std::swap(i,j);
                return std::vector<int>{i,j};
            }
            record[nums[i]] = i;
        }
        return std::vector<int>{-1,-1};
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
    std::vector<int> nums = {2,7,11,15};
    printVec(nums);
    int target = 9;
    std::vector<int> res = Solution().twoSum(nums,target);
    printVec(res);
    //result
    //[0,1]
}

