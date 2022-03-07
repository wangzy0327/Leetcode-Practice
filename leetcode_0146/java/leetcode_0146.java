import java.util.HashMap;
import java.util.Map;

public class leetcode_0146 {
    /**
     * 函数 get 和 put 必须以 O(1) 的平均时间复杂度运行
     *
     * 分析：
     * 1.get 和 put 需要以O(1) 的平均时间复杂度运行，可以想到采用哈希表来实现
     * 2.对 LRU 元素的使用和逐出，可以联想到链表可以满足 插入和删除操作 以O(1)的时间复杂度 完成Cache队列的操作
     * 3.且删除操作需要知道 待删除元素的前置元素（可知这里的链表需要双向链表来实现）
     *
     */
    class ListNode{
        int key;
        int value;
        ListNode prev;
        ListNode next;
        ListNode(){}
        ListNode(int key,int value){this.key = key;this.value = value;}
    }
    class LRUCache {

        private int capacity;
        private Map<Integer,ListNode> record;
        private ListNode dummyHead;
        private ListNode dummyTail;

        private int removeTail(){
            ListNode cur = dummyTail.prev;
            dummyTail.prev = cur.prev;
            cur.prev.next = dummyTail;
            return cur.key;
        }

        private void moveTOHead(ListNode node){
            //截断node节点
            node.next.prev = node.prev;
            node.prev.next = node.next;
            addTOHead(node);

        }
        private void addTOHead(ListNode node){
            dummyHead.next.prev = node;
            node.next = dummyHead.next;
            node.prev = dummyHead;
            dummyHead.next = node;
        }

        private ListNode addNode(int key,int value){
            ListNode cur = new ListNode(key,value);
            addTOHead(cur);
            return cur;
        }

        public LRUCache(int capacity) {
            this.capacity = capacity;
            dummyHead = new ListNode();
            dummyTail = new ListNode();
            dummyHead.next = dummyTail;
            dummyTail.prev = dummyHead;
            record = new HashMap<>();
        }

        public int get(int key) {
            if(!record.containsKey(key))
                return -1;
            ListNode cur = record.get(key);
            moveTOHead(cur);
            return cur.value;
        }

        public void put(int key, int value) {
            //查看是否已经包含键值
            if(record.containsKey(key)){
                ListNode cur = record.get(key);
                cur.value = value;
                moveTOHead(cur);
            }else{
                //查看是否达到容量上界
                if(this.capacity == record.size()){
                    int delKey = removeTail();
                    record.remove(delKey);
                }
                //往LRUCache中添加元素
                ListNode cur = addNode(key,value);
                record.put(key,cur);
            }
        }

        public void printLRU(){
            ListNode cur = dummyHead.next;
            StringBuilder sb = new StringBuilder("{");
            while(cur != dummyTail){
                sb.append(cur.key);
                sb.append("=");
                sb.append(cur.value);
                sb.append(",");
                cur = cur.next;
            }
            String res = sb.substring(0,sb.length()-1);
            res += "}";
            System.out.println(res);
        }
    }


    public static void main(String[] args) {
        LRUCache lruCache = new leetcode_0146().new LRUCache(2);
        lruCache.put(1,1);
        lruCache.put(2,2);
        System.out.println(lruCache.get(1));
        lruCache.put(3,3);
        lruCache.printLRU();
//    {3 = 3, 1 = 1};
        System.out.println(lruCache.get(2));
        lruCache.put(4,4);
        lruCache.printLRU();
        System.out.println(lruCache.get(1));
        System.out.println(lruCache.get(3));
        System.out.println(lruCache.get(4));

        /**
         *
         * LRUCache lRUCache = new LRUCache(2);
         * lRUCache.put(1, 1); // 缓存是 {1=1}
         * lRUCache.put(2, 2); // 缓存是 {1=1, 2=2}
         * lRUCache.get(1);    // 返回 1
         * lRUCache.put(3, 3); // 该操作会使得关键字 2 作废，缓存是 {1=1, 3=3}
         * lRUCache.get(2);    // 返回 -1 (未找到)
         * lRUCache.put(4, 4); // 该操作会使得关键字 1 作废，缓存是 {4=4, 3=3}
         * lRUCache.get(1);    // 返回 -1 (未找到)
         * lRUCache.get(3);    // 返回 3
         * lRUCache.get(4);    // 返回 4
         *
         *
         */
    }
}
