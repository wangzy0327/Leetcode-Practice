public class leetcode_0208 {
    class Trie {
        class Node{
            char val;
            boolean end;
            Node[] nexts;
            Node(char val){this.val = val;this.end = false;nexts = new Node[26];}
        }
        public Trie() {
            //思路：前缀树
            arr = new Node[26];
        }

        public void insert(String word) {
            Node cur = null;
            for(int i = 0;i < word.length();i++){
                int num = word.charAt(i) - 'a';
                if(i == 0){
                    if(arr[num] == null){
                        arr[num] = new Node(word.charAt(i));
                        cur = arr[num];
                    }else
                        cur = arr[num];
                }else{
                    if(cur.nexts[num] == null){
                        cur.nexts[num] = new Node(word.charAt(i));
                        cur = cur.nexts[num];
                    }else{
                        cur = cur.nexts[num];
                    }
                }
                //设置终点为终止标志
                if(i == word.length() - 1){
                    cur.end = true;
                }
            }
        }

        public boolean search(String word) {
            Node cur = null;
            for(int i = 0;i < word.length();i++){
                int num = word.charAt(i) - 'a';
                if(i == 0){
                    if(arr[num] == null)
                        return false;
                    else{
                        cur = arr[num];
                    }
                }else{
                    if(cur.nexts[num] == null)
                        return false;
                    else
                        cur = cur.nexts[num];
                }
            }
            //最后判断最后一个节点带有结束标志
            return (cur == null)?true:(cur.end);
        }

        public boolean startsWith(String prefix) {
            Node cur = null;
            for(int i = 0;i < prefix.length();i++){
                int num = prefix.charAt(i) - 'a';
                if(i == 0){
                    if(arr[num] == null)
                        return false;
                    else{
                        cur = arr[num];
                    }
                }else{
                    if(cur.nexts[num] == null)
                        return false;
                    else
                        cur = cur.nexts[num];
                }
            }
            return true;
        }

        Node[] arr;

    }

    /**
     * Your Trie object will be instantiated and called as such:
     * Trie obj = new Trie();
     * obj.insert(word);
     * boolean param_2 = obj.search(word);
     * boolean param_3 = obj.startsWith(prefix);
     */
    public static void main(String[] args) {
        leetcode_0208.Trie trie = new leetcode_0208().new Trie();
        trie.insert("apple");
        System.out.println(trie.search("apple"));
        //result
        // 返回 True
        System.out.println(trie.search("app"));
        //result
        // 返回 False
        System.out.println(trie.startsWith("app"));
        //result
        // 返回 True
        trie.insert("app");
        System.out.println(trie.search("app"));
        //result
        //返回 True
    }
}
