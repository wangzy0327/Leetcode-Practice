public class leetcode_0677 {
    class MapSum {
        class Node{
            char ch;
            int val;
            Node[] nexts;
            Node(char ch,int val){
                this.ch = ch;
                this.val = val;
                nexts = new Node[26];
            }
            Node(char ch){
                this.ch = ch;
                this.val = 0;
                nexts = new Node[26];
            }
        }
        private Node dummyHead;
        public MapSum() {
            //思路：前缀树
            //使用虚拟头节点来存储前一个节点，来对接下来要判断的节点进行判定
            dummyHead = new Node(' ');
        }

        public void insert(String key, int val) {
            Node cur = dummyHead;
            for(int i = 0;i < key.length();i++){
                int num = key.charAt(i) - 'a';
                if(cur.nexts[num] == null)
                    cur.nexts[num] = new Node(key.charAt(i));
                cur = cur.nexts[num];
                if(i == key.length()-1)
                    cur.val = val;
            }
        }

        public int sum(String prefix) {
            int ans = 0;
            Node cur = dummyHead;
            //找到对应前缀的节点，如果没找到则直接返回0
            for(int i = 0;i < prefix.length();i++){
                int num = prefix.charAt(i) - 'a';
                if(cur.nexts[num] == null)
                    return ans;
                else
                    cur = cur.nexts[num];
            }
            //找到后回溯dfs 节点找到前缀和
            return dfs(cur);
        }

        private int dfs(Node node){
            Node cur = node;
            int ans = cur.val;
            for(int i = 0;i < 26;i++){
                Node next = cur.nexts[i];
                if(next != null)
                    ans += dfs(next);
            }
            return ans;
        }
    }

    /**
     * Your MapSum object will be instantiated and called as such:
     * MapSum obj = new MapSum();
     * obj.insert(key,val);
     * int param_2 = obj.sum(prefix);
     */
    public static void main(String[] args) {
        leetcode_0677.MapSum mapSum = new leetcode_0677().new MapSum();
        mapSum.insert("apple",3);
        System.out.println(mapSum.sum("ap"));
        // 返回 3 (apple = 3)
        mapSum.insert("app",2);
        System.out.println(mapSum.sum("ap"));
        // 返回 5 (apple + app = 3 + 2 = 5)
    }
}
