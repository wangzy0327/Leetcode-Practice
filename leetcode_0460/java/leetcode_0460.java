import java.util.*;

public class leetcode_0460 {
    //哈希表+平衡二叉树
//思路：快速根据键值查找元素 可想到哈希表
//     对最近最不经常使用的快速查找 可以通过平衡二叉树对每个元素进行查找、更新和删除
//     这里的对最不经常可通过每个节点的time变量值来比较
//     对节点的访问频次采用count变量值来记录
//     平衡二叉树的元素查找和删除 时间复杂度为O(logn)
    class Node implements Comparable{
        int key;
        int value;
        //访问频次
        int count;
        //时间
        int time;
        public Node(){ }
        public Node(int _key,int _value,int _count,int _time){
            this.key = _key; this.value = _value; this.count = _count; this.time = _time;
        }
        @Override
        public int compareTo(Object o) {
            Node node = (Node) o;
            return this.count == node.count ? this.time - node.time : this.count - node.count;
        }
    }
    class LFUCache {
        private Map<Integer,Node> record;
        private TreeSet<Node> tree;
        private int capacity;
        private int time;

        public LFUCache(int capacity) {
            this.capacity = capacity;
            this.time = time;
            this.record = new HashMap<>();
            this.tree = new TreeSet<>();
        }

        public int get(int key) {
            //如果key不存在
            if(!record.containsKey(key))
                return -1;
            //如果key存在
            Node cur = record.get(key);
            //注意要提前删除，否则修改过后，cur的引用可能会变，导致删除失败
            tree.remove(cur);
            //修改节点的访问频次和时间戳
            cur.time = ++time;
            cur.count = cur.count + 1;
            //将节点取出再插入 重新排序
            tree.add(cur);
            return cur.value;
        }

        public void put(int key, int value) {
            //如果容量为0，则直接返回
            if(this.capacity <= 0)
                return;
            //否则进行判断 如果key值存在
            if (record.containsKey(key)){
                Node cur = record.get(key);
                tree.remove(cur);
                cur.value = value;
                cur.count = cur.count + 1;
                cur.time = ++time;
                tree.add(cur);
            }else{//如果key值不存在
                //如果容量满了  删除tree中节点
                if(record.size() == this.capacity){
                    //弹出节点 删除 字典记录
                    Node node = tree.pollFirst();
                    record.remove(node.key);
                }
                //添加新节点
                Node cur = new Node(key,value,1,++time);
                record.put(key,cur);
                tree.add(cur);
            }
        }
    }
    //方法2 双哈希表 时间复杂度 O(1)
    /**
     第一个 freq_table 以频率 freq 为索引，每个索引存放一个双向链表，这个链表里存放所有使用频率为 freq 的缓存，
     缓存里存放三个信息，分别为键 key，值 value，以及使用频率 freq。第二个 key_table 以键值 key 为索引，
     每个索引存放对应缓存在 freq_table 中链表里的内存地址，这样我们就能利用两个哈希表来使得两个操作的时间复杂度均为 O(1)
     */
    class Node2{
        int key;
        int value;
        int freq;
        Node2(){}
        Node2(int _key,int _value,int _freq){this.key = _key; this.value = _value; this.freq = _freq;}
    }

    class LFUCache2{
        private int capacity;
        private int minFreq;
        private Map<Integer,Node2> key_dict;
        private Map<Integer, LinkedList<Node2>> freq_dict;

        public LFUCache2(int capacity) {
            this.capacity = capacity;
            this.minFreq = 0;
            key_dict = new HashMap<>();
            freq_dict = new HashMap<>();
        }

        public int get(int key) {
            if(!key_dict.containsKey(key))
                return -1;
            //如果存在key
            Node2 node = key_dict.get(key);
            int val = node.value;
            int freq = node.freq;
            freq_dict.get(freq).remove(node);
            //如果双向链表容量为 0
            if(freq_dict.get(freq).size() == 0){
                freq_dict.remove(freq);
                if(minFreq == freq)
                    minFreq = freq + 1;
            }
            LinkedList<Node2> list = freq_dict.getOrDefault(freq + 1,new LinkedList<Node2>());
            list.offerFirst(new Node2(key,val,freq + 1));
            freq_dict.put(freq + 1,list);
            key_dict.put(key,freq_dict.get(freq + 1).peekFirst());
            return val;
        }

        public void put(int key, int value) {
            if(this.capacity <= 0)
                return ;
            //如果key值存在
            if(key_dict.containsKey(key)){
                //跟get操作类似
                Node2 node2 = key_dict.get(key);
                int freq = node2.freq;
                freq_dict.get(freq).remove(node2);
                //如果双向链表容量为 0
                if(freq_dict.get(freq).size() == 0){
                    freq_dict.remove(freq);
                    if(minFreq == freq)
                        minFreq = freq + 1;
                }
                LinkedList<Node2> list = freq_dict.getOrDefault(freq + 1,new LinkedList<Node2>());
                list.offerFirst(new Node2(key,value,freq + 1));
                freq_dict.put(freq + 1,list);
                key_dict.put(key,freq_dict.get(freq + 1).peekFirst());
            }else{
                //如果key值不存在
                //如果容量已满
                if(this.capacity == key_dict.size()){
                    //删除双向链表的元素  最后的元素是最小的
                    Node2 node2 = freq_dict.get(minFreq).getLast();
                    key_dict.remove(node2.key);
                    freq_dict.get(minFreq).pollLast();
                    if(freq_dict.get(minFreq).size() == 0){
                        freq_dict.remove(minFreq);
                        minFreq = 1;
                    }
                }
                LinkedList<Node2> list = freq_dict.getOrDefault(1,new LinkedList<Node2>());
                list.offerFirst(new Node2(key,value, 1));
                freq_dict.put(1,list);
                key_dict.put(key,freq_dict.get(1).peekFirst());
                minFreq = 1;
            }
        }

    }

    public static void main(String[] args) {
        LFUCache lfuCache = new leetcode_0460().new LFUCache(2);
        lfuCache.put(1,1);
        lfuCache.put(2,2);
        System.out.printf("%d,", lfuCache.get(1));
        lfuCache.put(3,3);
        System.out.printf("%d,", lfuCache.get(2));
        System.out.printf("%d,", lfuCache.get(3));
        lfuCache.put(4,4);
        System.out.printf("%d,", lfuCache.get(1));
        System.out.printf("%d,", lfuCache.get(3));
        System.out.printf("%d\n", lfuCache.get(4));
        //result
        // 1,-1,3,-1,3,4

        System.out.println();

        LFUCache2 lfuCache2 = new leetcode_0460().new LFUCache2(2);
        lfuCache2.put(1,1);
        lfuCache2.put(2,2);
        System.out.printf("%d,", lfuCache2.get(1));
        lfuCache2.put(3,3);
        System.out.printf("%d,", lfuCache2.get(2));
        System.out.printf("%d,", lfuCache2.get(3));
        lfuCache2.put(4,4);
        System.out.printf("%d,", lfuCache2.get(1));
        System.out.printf("%d,", lfuCache2.get(3));
        System.out.printf("%d\n", lfuCache2.get(4));
    }
}
