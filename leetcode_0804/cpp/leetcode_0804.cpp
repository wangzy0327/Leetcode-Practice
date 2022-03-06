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
    int uniqueMorseRepresentations(vector<string>& words) {
        unordered_set<string> record;
        vector<string> vec = {
                ".-","-...","-.-.","-..",".","..-.","--.","....","..",".---","-.-",".-..","--","-.","---",".--.","--.-",".-.","...","-","..-","...-",".--","-..-","-.--","--.."
        };
        string tmp = "";
        int res = 0;
        for(auto ele : words){
            tmp = "";
            for(auto alpha:ele)
                tmp += vec[alpha-'a'];
            record.emplace(tmp);
        }
        return record.size();
    }
};

int main(int argc,char* argv[]){
    vector<string> vec = {"gin", "zen", "gig", "msg"};
    /**
     各单词翻译如下:
    "gin" -> "--...-."
    "zen" -> "--...-."
    "gig" -> "--...--."
    "msg" -> "--...--."
     共有 2 种不同翻译, "--...-." 和 "--...--.".
     */

    int res = Solution().uniqueMorseRepresentations(vec);
    cout<<res<<endl;
}

