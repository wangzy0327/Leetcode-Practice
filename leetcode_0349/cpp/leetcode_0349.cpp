//
// Created by wangzy on 2022/3/6.
//
#include <iostream>
#include <vector>
#include <unordered_set>
#include <sstream>

using namespace std;

class Solution {
public:
    vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
        unordered_set<int> record;
        unordered_set<int> inter;
        for(auto num : nums1)
            record.emplace(num);
        for(auto num : nums2){
            if(record.count(num))
                inter.emplace(num);
        }
        return vector<int>(inter.begin(),inter.end());
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
    vector<int> nums1 = {1,2,2,1};
    vector<int> nums2 = {2,2};

    vector<int> res = Solution().intersection(nums1,nums2);
    printVec(res);

    //[2]
}
