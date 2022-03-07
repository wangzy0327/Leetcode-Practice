//
// Created by wzy on 2022/3/7.
//
#include <iostream>
#include <vector>
#include <unordered_map>
#include <sstream>

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
    vector<int> intersect(vector<int>& nums1, vector<int>& nums2) {
        unordered_map<int,int> record;
        for(auto ele:nums1)
            record[ele]++;
        vector<int> res;
        for(auto ele:nums2){
            if(record.count(ele)){
                res.push_back(ele);;
                if(!(--record[ele]))
                    record.erase(ele);
            }
        }
        //思考：
        //方法一：当前解决采用哈希表，时间复杂度为O(m+n),空间复杂度为O(min(m,n))
        //如果给定的数组已经是排好序的，则使用方法二：排序+双指针分别指向两个数组头右移进行操作,时间复杂度(mlogm+nlogn),空间复杂度O(1)
        //如果nums2的元素存储在磁盘上，内存是有限的，则不能使用方法二对数组进行高效的排序，则采用方法一
        return res;
    }
};

int main(int argc,char* argv[]){
    vector<int> nums1 = {1,2,2,1};
    vector<int> nums2 = {2,2};

    vector<int> res = Solution().intersect(nums1,nums2);
    printVec(res);

    //[2]
}
