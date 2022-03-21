//
// Created by wangzy on 2022/3/21.
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
    int lengthOfLongestSubstring(string s) {
        int res = 0;
        //unordered_map<char,int> window;
        //字符表
        vector<int> window(128,0);
        int left = 0,right = 0;
        while(right < s.size()){
            while(right < s.size() && !window[s[right]]){
                window[s[right]] = 1;
                right++;
                if(res < right - left)
                    res = right - left;
            }
            if(right < s.size() && window[s[right]]){
                window[s[left]]--;
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
    string s = "abcabcbb";
    //result
    //3
//    string s = "bbbbbb";
    //result
    //1
//    string s = "pwwkew";
    //result
    //3
    int res = Solution().lengthOfLongestSubstring(s);
    cout<<res<<endl;
}