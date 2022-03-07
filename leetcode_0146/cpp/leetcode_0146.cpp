//
// Created by wangzy on 2022/3/7.
//
#include <iostream>
#include <vector>
#include <unordered_map>
#include <sstream>

using namespace std;

struct DListNode{
    int key;
    int val;
    DListNode* prev;
    DListNode* next;
    DListNode() : key(0),val(0),prev(nullptr),next(nullptr) {};
    DListNode(int key,int val) : key(key),val(val),prev(nullptr),next(nullptr) {};
    DListNode(int key,int val,DListNode* prev,DListNode* next) : key(key),val(val),prev(prev),next(next) {};
};

class LRUCache {
    /**
     * 函数 get 和 put 必须以 O(1) 的平均时间复杂度运行
     *
     * 分析：
     * 1.get 和 put 需要以O(1) 的平均时间复杂度运行，可以想到采用哈希表来实现
     * 2.对LRU 元素的使用和逐出，可以联想到链表可以满足 插入和删除操作 以O(1)的时间复杂度 完成Cache队列的操作
     * 3.且删除操作需要知道 待删除元素的前置元素（可知这里的链表需要双向链表来实现）
     *
     */
public:
    LRUCache(int capacity) {
        this->capacity = capacity;
        dummyHead = new DListNode();
        dummyTail = new DListNode();
        dummyHead->next = dummyTail;
        dummyTail->prev = dummyHead;
    }
    int get(int key) {
        if(!record.count(key))
            return -1;
        DListNode* cur = record[key];
        moveTOHead(cur);
        return cur->val;
    }
    void put(int key, int value) {
        if(record.count(key)){
            DListNode* cur = record[key];
            cur->val = value;
            moveTOHead(cur);
        }
        else{
            if(this->capacity == record.size()){
                //删除队尾元素
                int delKey = removeTail();
                record.erase(delKey);
            }
            DListNode* cur = addNode(key,value);
            record[key] = cur;
        }
    }
    void printLRU(){
        DListNode* cur = dummyHead->next;
        string res = "{";
        string tmp = "";
        stringstream ss;
        while(cur != dummyTail){
            ss<<cur->key<<"="<<cur->val<<", ";
            ss>>tmp;
            res += tmp;
            ss.clear();
            cur = cur->next;
        }
        res = res.substr(0,res.size() - 1);
        res += "}";
        cout<<res<<endl;
    }
    ~LRUCache(){
        while(dummyHead->next){
            DListNode* cur = dummyHead->next;
            dummyHead->next = cur->next;
            delete cur;
        }
        delete dummyHead;
        delete dummyTail;
    }
private:
    int capacity;
    DListNode* dummyHead;
    DListNode* dummyTail;
    unordered_map<int,DListNode*> record;
    int removeTail(){
        DListNode* cur = dummyTail->prev;
        DListNode* prev = cur->prev;
        prev->next = dummyTail;
        dummyTail->prev = prev;
        int key = cur->key;
        return key;
    };
    void moveTOHead(DListNode* node){
        //拆解要移动的节点
        node->prev->next = node->next;
        node->next->prev = node->prev;
        //将拆解的节点放在头结点位置
        addNodeTOHead(node);
    };
    void addNodeTOHead(DListNode* node){
        DListNode* next = dummyHead->next;
        node->next = next;
        node->prev = dummyHead;
        next->prev = node;
        dummyHead->next = node;
    }
    DListNode* addNode(int key,int value){
        //创建节点 并 记录在哈希表
        DListNode* cur = new DListNode(key,value);
        record[key] = cur;
        //添加到头结点位置
        addNodeTOHead(cur);
        return cur;
    }
};

int main(int argc,char* argv[]){
    LRUCache* lRUCache = new LRUCache(2);
    lRUCache->put(1,1);
    lRUCache->put(2,2);
    cout<<lRUCache->get(1)<<endl;
    lRUCache->put(3,3);
    lRUCache->printLRU();
//    {1 = 1, 3 = 3};
    cout<<lRUCache->get(2)<<endl;
    lRUCache->put(4,4);
    lRUCache->printLRU();
    cout<<lRUCache->get(1)<<endl;
    cout<<lRUCache->get(3)<<endl;
    cout<<lRUCache->get(4)<<endl;
    delete lRUCache;

    /**
    LRUCache lRUCache = new LRUCache(2);
    lRUCache.put(1, 1); // 缓存是 {1=1}
    lRUCache.put(2, 2); // 缓存是 {1=1, 2=2}
    lRUCache.get(1);    // 返回 1
    lRUCache.put(3, 3); // 该操作会使得关键字 2 作废，缓存是 {1=1, 3=3}
    lRUCache.get(2);    // 返回 -1 (未找到)
    lRUCache.put(4, 4); // 该操作会使得关键字 1 作废，缓存是 {4=4, 3=3}
    lRUCache.get(1);    // 返回 -1 (未找到)
    lRUCache.get(3);    // 返回 3
    lRUCache.get(4);    // 返回 4
     */
    return 0;
}
