//
// Created by wzy on 2022/3/7.
//

#include <iostream>
#include <vector>
#include <unordered_map>
#include <sstream>

using namespace std;

class Solution {
public:
    int firstUniqChar(string s) {
        int record[26] = {0};
        int index = -1;
        for(auto ch:s)
            record[ch - 'a']++;
        for(int i = 0;i < s.length();i++)
            if(record[s[i] - 'a'] == 1)
                return i;
        return index;
    }
};

int main(int argc,char* argv[]){
    string s = "loveleetcode";
    int res = Solution().firstUniqChar(s);
    cout<<res<<endl;
    //res
    //2
}

