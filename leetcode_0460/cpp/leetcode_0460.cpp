//
// Created by wzy on 2022/3/9.
//

#include <iostream>
#include <vector>
#include <unordered_map>
#include <set>
#include <list>
#include <sstream>

using namespace std;

//哈希表+平衡二叉树
//思路：快速根据键值查找元素 可想到哈希表
//     对最近最不经常使用的快速查找 可以通过平衡二叉树对每个元素进行查找、更新和删除
//     这里的对最不经常可通过每个节点的time变量值来比较
//     对节点的访问频次采用count变量值来记录
//     平衡二叉树的元素查找和删除 时间复杂度为O(logn)
struct Node{
    int key;
    int value;
    int time;
    int count;
    Node() : key(0),value(0),time(0),count(0){}
    Node(int key,int value,int time,int count):key(key),value(value),time(time),count(count){}
    bool operator<(const Node& node) const{
        //访问频次相同 按照时间的新旧来 比较 ，否则按照频次来判断  时间time值越大表明最近刚访问过(新)
        return this->count == node.count ? this->time < node.time : this->count < node.count;
    }
};

class LFUCache {
private:
    int capacity;
    unordered_map<int,Node> record;
    //平衡二叉树采用set来进行处理
    set<Node> tree;
    //记录Cache的时间
    int time;
public:
    LFUCache(int capacity) {
        this->capacity = capacity;
        this->time = 0;
    }

    int get(int key) {
        if(!record.count(key))
            return -1;
        Node cur = record[key];
        tree.erase(cur);
        cur.count++;
        //更新整体时间计数，并更新当前节点的值
        cur.time = ++time;
        tree.insert(cur);
        record[key] = cur;
        return cur.value;
    }

    void put(int key, int value) {
        //如果初始化容量为0，则直接返回
        if(this->capacity == 0)
            return ;
        //存在键值
        if(record.count(key)){
            Node cur = record[key];
            tree.erase(cur);
            cur.value = value;
            cur.count++;
            cur.time = ++time;
            tree.insert(cur);
            record[key] = cur;
        }else{  //键值不存在
            //如果容量已满
            if(record.size() == capacity){
                //删除平衡二叉树中的头结点（最小元素）
                int k = tree.begin()->key;
                Node min = record[k];
                tree.erase(min);
                record.erase(k);
            }
            //创建新的缓存节点
            Node n = Node(key,value,++time,1);
            //放入节点到平衡二叉树中
            tree.insert(n);
            record[n.key] = n;
        }
    }
    ~LFUCache(){

    }
    void printLRU(){
        stringstream ss;
        string res = "{";
        string tmp = "";
        for(auto it:tree){
            ss<<it.key<<" : "<<it.value<<",";
            ss>>tmp;
            res += tmp;
            ss.clear();
        }
        res = res.substr(0,res.size()-1);
        res += "}";
        cout<<res<<endl;
    }
};

//方法2 双哈希表 时间复杂度 O(1)
/**
第一个 freq_table 以频率 freq 为索引，每个索引存放一个双向链表，这个链表里存放所有使用频率为 freq 的缓存，
 缓存里存放三个信息，分别为键 key，值 value，以及使用频率 freq。第二个 key_table 以键值 key 为索引，
 每个索引存放对应缓存在 freq_table 中链表里的内存地址，这样我们就能利用两个哈希表来使得两个操作的时间复杂度均为 O(1)
 */
struct Node2{
    int key;
    int value;
    //频次
    int freq;
    Node2() : key(0),value(0),freq(0) {}
    Node2(int _key,int _value,int _freq) : key(_key),value(_value),freq(_freq) {}
};

class LFUCache2 {
private:
    int capacity;
    int minFreq;
    //存储双向链表中节点的位置
    unordered_map<int,list<Node2>::iterator> key_dict;
    //同样频次的出现冲突，采用拉链法(链头是时间最小的)
    unordered_map<int,list<Node2>> freq_dict;
public:
    LFUCache2(int capacity) {
        this->capacity = capacity;
        this->minFreq = 0;
    }

    int get(int key) {
        //如果不存在key
        if( this->capacity <= 0 || !key_dict.count(key))
            return -1;
        //如果存在key , key_dict存储的是list双向链表里Node的地址
        list<Node2>::iterator  iter = key_dict[key];
        int val = iter->value;
        int freq = iter->freq;
        //删除list中的Node
        freq_dict[freq].erase(iter);
        //如果freq的双向链表 容量为0
        // 如果当前链表为空，我们需要在哈希表中删除，且更新minFreq
        if(freq_dict[freq].size() == 0){
            freq_dict.erase(freq);
            if(freq == minFreq)
                minFreq = freq + 1;
        }
        //频次+1 并 存储在 更高频次的哈希表中
        freq_dict[freq + 1].push_front(Node2(key,val,freq + 1));
        //更新key_dict的值引用
        key_dict[key] = freq_dict[freq + 1].begin();
        return val;
    }

    void put(int key, int value) {
        //如果容量为0 直接返回
        if(this->capacity <= 0)
            return ;
        //如果存在key值
        if(key_dict.count(key)){
            list<Node2>::iterator iter = key_dict[key];
            int freq = iter->freq;
            //删除list中的node
            freq_dict[freq].erase(iter);
            if(freq_dict[freq].size() == 0){
                freq_dict.erase(freq);
                if(freq == minFreq)
                    minFreq = freq + 1;
            }
            freq_dict[freq + 1].push_front(Node2(key,value,freq + 1));
            key_dict[key] = freq_dict[freq + 1].begin();
        }else{//如果不存在key值
            //如果容量已满
            if(this->capacity == key_dict.size()){
                //删除频次最小链表中的尾结点
                //首先拿到链表的末尾节点
                auto lastNode = freq_dict[minFreq].back();
                key_dict.erase(lastNode.key);
                freq_dict[minFreq].pop_back();
                if(freq_dict[minFreq].size() == 0)
                    freq_dict.erase(minFreq);
            }
            //添加新元素
            freq_dict[1].push_front(Node2(key,value,1));
            key_dict[key] = freq_dict[1].begin();
            minFreq = 1;
        }
    }
};


/**
 * Your LFUCache object will be instantiated and called as such:
 * LFUCache* obj = new LFUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */

int main(int argc,char* argv[]){
    LFUCache lfuCache(2);
    lfuCache.put(1,1);
    lfuCache.put(2,2);
    cout<<lfuCache.get(1)<<",";
    lfuCache.put(3,3);
    cout<<lfuCache.get(2)<<",";
    cout<<lfuCache.get(3)<<",";
    lfuCache.put(4,4);
    cout<<lfuCache.get(1)<<",";
    cout<<lfuCache.get(3)<<",";
    cout<<lfuCache.get(4)<<endl;

    cout<<endl;

    LFUCache2 lfuCache2(2);
    lfuCache2.put(1,1);
    lfuCache2.put(2,2);
    cout<<lfuCache2.get(1)<<",";
    lfuCache2.put(3,3);
    cout<<lfuCache2.get(2)<<",";
    cout<<lfuCache2.get(3)<<",";
    lfuCache2.put(4,4);
    cout<<lfuCache2.get(1)<<",";
    cout<<lfuCache2.get(3)<<",";
    cout<<lfuCache2.get(4)<<endl;
}

