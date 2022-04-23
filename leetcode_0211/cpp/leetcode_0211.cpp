//
// Created by wzy on 2022/4/22.
//

#include<iostream>
#include<queue>
#include<vector>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <list>
#include <deque>
#include <stack>
#include <sstream>
#include <typeinfo>
#include <climits>
#include <random>
#include <ctime>

using namespace std;

struct Node{
    char val;
    bool end;
    vector<Node*> nexts;
    Node(char val):val(val),end(false),nexts(vector<Node*>(26,nullptr)){};
};
class WordDictionary {
public:
    WordDictionary() {
        //思路：Trie 前缀树 对于.的判断使用递归处理
        dummyHead = new Node(' ');
    }
    ~WordDictionary() = default;

    void addWord(string word) {
        Node* cur = dummyHead;
        for(int i = 0;i < word.size();i++){
            int num = word[i] - 'a';
            if(!cur->nexts[num]){
                cur->nexts[num] = new Node(word[i]);
                cur = cur->nexts[num];
            }else{
                cur = cur->nexts[num];
            }
            if(i == word.size()-1)
                cur->end = true;
        }
    }

    bool search(string word) {
        return searchHelper(dummyHead,word);
    }
private:
    Node* dummyHead;
    bool searchHelper(Node* cur,string word){
        if(!word.size() )
            return true;
        if(!cur && word.size())
            return false;
        for(int i = 0;i < word.size();i++){
            int num = word[i] - 'a';
            if(num >= 0 && num < 26 && !cur->nexts[num])
                return false;
            else if(num >= 0 && num < 26 && cur->nexts[num]){
                cur = cur->nexts[num];
            }else{
                for(int j = 0;j < 26;j++){
                    if(i + 1 < word.size()){
                        if(cur->nexts[j] && searchHelper(cur->nexts[j],word.substr(i+1,word.size()-i-1)))
                            return true;
                    }
                    else{
                        //i+1 == word.size()
                        if(cur->nexts[j] && cur->nexts[j]->end)
                            return true;
                    }
                }
                return false;
            }
        }
        //如果都是字母从这里结束，判断节点是否有完整单词标志
        return (!cur)?true:cur->end;
    }
};

/**
 * Your WordDictionary object will be instantiated and called as such:
 * WordDictionary* obj = new WordDictionary();
 * obj->addWord(word);
 * bool param_2 = obj->search(word);
 */

int main(){
    WordDictionary* wd = new WordDictionary();
    wd->addWord("at");
    wd->addWord("and");
    wd->addWord("an");
    wd->addWord("add");
    cout<<boolalpha<<wd->search("a")<<endl;
    //result
    //false  不是单词终点
    cout<<boolalpha<<wd->search(".at")<<endl;
    //result
    //false
    wd->addWord("bat");
    cout<<boolalpha<<wd->search(".at")<<endl;
    //result
    //true
    cout<<boolalpha<<wd->search("an.")<<endl;
    //result
    //true
    cout<<boolalpha<<wd->search("a.d.")<<endl;
    //result
    //false

}