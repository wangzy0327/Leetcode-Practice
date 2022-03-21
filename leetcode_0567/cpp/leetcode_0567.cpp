//
// Created by wzy on 2022/3/21.
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
    bool checkInclusion(string s1, string s2) {
        //滑动窗口
        //哈希表来存储s1的排列
        //valid整型来计算是否满足所需要的子串字母的整型
        //由于仅存在小写字母，这里采用数组来代替哈希表
        if(s1.size() > s2.size())
            return false;
        vector<int> need(26,0);
        for(char c : s1)
            need[c-'a']++;
        int sz = 0;
        for(int i = 0;i < need.size();i++)
            if(need[i] > 0)
                sz++;
        //滑动窗口
        vector<int> watch(26,0);
        int valid = 0;
        int left = 0;int right = 0;
        //[0,0)
        while(right < s2.size()){
            if(right - left < s1.size()){
                char c = s2[right];
                int index = c-'a';
                if(need[index] > 0){
                    watch[index]++;
                    if(watch[index] == need[index])
                        valid++;
                }
                right++;
            }
            if(right -left == s1.size()){
                if(valid == sz)
                    return true;
                char lChar = s2[left];
                int lInx = lChar - 'a';
                if(need[lInx] > 0){
                    if(watch[lInx] == need[lInx])
                        valid--;
                    watch[lInx]--;
                }
                left++;
            }
        }
        return false;
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
    string s1 = "ab";
    string s2 = "eidbaooo";
    //result
    //true
//    string s1 = "ab";
//    string s2 = "eidboaoo";
    //result
    //false

    cout<<boolalpha<<Solution().checkInclusion(s1,s2)<<endl;
    //true

}