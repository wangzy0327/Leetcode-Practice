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
    Node(char val,bool end):val(val),end(end),nexts(vector<Node*>(26,nullptr)){};
};
class Trie {
public:
    Trie() {
        //思路：前缀树
        arr = vector<Node*>(26,nullptr);
    }

    void insert(string word) {
        //表示上一个节点
        Node* cur = nullptr;
        for(int i = 0;i < word.size();i++){
            int num = word[i] - 'a';
            if(i == 0){
                if(!arr[num]){
                    arr[num] = new Node(word[i]);
                    cur = arr[num];
                }else{
                    cur = arr[num];
                }
            }else{
                if(!cur->nexts[num]){
                    cur->nexts[num] = new Node(word[i]);
                    cur = cur->nexts[num];
                }else{
                    cur = cur->nexts[num];
                }
            }
            if(i == word.size()-1){
                cur->end = true;
            }
        }
    }

    bool search(string word) {
        Node* cur = nullptr;
        for(int i = 0;i < word.size();i++){
            int num = word[i] - 'a';
            if(i == 0){
                if(!arr[num])
                    return false;
                else{
                    cur = arr[num];
                }
            }else{
                if(!cur->nexts[num])
                    return false;
                else{
                    cur = cur->nexts[num];
                }
            }
        }
        return (cur == nullptr)?true:(cur->end);
    }

    bool startsWith(string prefix) {
        Node* cur = nullptr;
        for(int i = 0;i < prefix.size();i++){
            int num = prefix[i] - 'a';
            if(i == 0){
                if(!arr[num])
                    return false;
                else{
                    cur = arr[num];
                }
            }else{
                if(!cur->nexts[num])
                    return false;
                else{
                    cur = cur->nexts[num];
                }
            }
        }
        return true;
    }
    ~Trie() = default;
private:
    vector<Node*> arr;
};


int main(){
    Trie* trie = new Trie();
    trie->insert("apple");
    cout<<boolalpha<<trie->search("apple")<<endl;
    //result
    // 返回 True
    cout<<boolalpha<<trie->search("app")<<endl;
    //result
    // 返回 False
    cout<<boolalpha<<trie->startsWith("app")<<endl;
    //result
    // 返回 True
    trie->insert("app");
    cout<<boolalpha<<trie->search("app")<<endl;
    //result
    //返回 True
    return 0;
}