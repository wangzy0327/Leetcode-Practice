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
    vector<int> findAnagrams(string s, string p) {
        //滑动窗口
        //采用哈希表来保存子串的种类和数量
        //利用valid整型来标识 是否满足异位词
        //由于只包含小写字母这里采用数组来表示
        vector<int> need(26,0);
        for(char c:p)
            need[c-'a']++;
        int sz = 0;
        vector<int> window(26,0);
        for(int i = 0;i < need.size();i++)
            if(need[i] > 0)
                sz++;
        int valid = 0;
        int left = 0;int right = 0;
        vector<int> res;
        //[0,0)
        while(right < s.size()){
            if(right - left < p.size()){
                char c = s[right];
                int idx = c - 'a';
                if(need[idx] > 0){
                    window[idx]++;
                    if(window[idx] == need[idx])
                        valid++;
                }
                right++;
            }
            if(right - left == p.size()){
                if(valid == sz){
                    res.push_back(left);
                }
                char c = s[left];
                int idx = c - 'a';
                if(need[idx] > 0){
                    if(window[idx] == need[idx])
                        valid--;
                    window[idx]--;
                }
                left++;
            }
        }
        return res;
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
    string s = "cbaebabacd";
    string p = "abc";
//    string s = "abab";
//    string p = "ab";
//  result
//  [0,1,2]
    vector<int> res = Solution().findAnagrams(s,p);
    printVec(res);
    //result
    //[0,6]
}