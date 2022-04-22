public class leetcode_0211 {
    class WordDictionary {
        class Node{
            char val;
            //判断是否是一个完整单词
            boolean end;
            Node[] nexts;
            Node(char val){this.val = val;end = false;nexts = new Node[26];}
        }
        //由于需要提前知道前一个元素，才能判断下一个元素的值 这里创建一个虚拟头节点
        private Node dummyHead;
        public WordDictionary() {
            dummyHead = new Node(' ');
        }

        public void addWord(String word) {
            Node cur = dummyHead;
            for(int i = 0;i < word.length();i++){
                char ch = word.charAt(i);
                int num = ch - 'a';
                if(cur.nexts[num] == null){
                    cur.nexts[num] = new Node(ch);
                    cur = cur.nexts[num];
                }else{
                    cur = cur.nexts[num];
                }
                if(i == word.length() - 1)
                    cur.end = true;
            }
        }

        public boolean search(String word) {
            return searchHelper(dummyHead,word);
        }
        private boolean searchHelper(Node cur,String word){
            if(word.length() == 0)
                return true;
            // if(cur == null && word.length() == 0)
            //     return false;
            for(int i = 0;i < word.length();i++){
                int num = word.charAt(i) - 'a';
                if(num >= 0 && num < 26 && cur.nexts[num] == null)
                    return false;
                else if(num >= 0 && num < 26 && cur.nexts[num] != null)
                    cur = cur.nexts[num];
                else{
                    //说明字符是'.'
                    //进行dfs
                    for(int j = 0;j < 26;j++){
                        if(i + 1 < word.length()){
                            if(cur.nexts[j] != null && searchHelper(cur.nexts[j],word.substring(i+1,word.length())))
                                return true;
                        }else{
                            if(cur.nexts[j] != null && cur.nexts[j].end)
                                return true;
                        }
                    }
                    return false;
                }
            }
            return (cur == null)?true:cur.end;
        }
    }

    /**
     * Your WordDictionary object will be instantiated and called as such:
     * WordDictionary obj = new WordDictionary();
     * obj.addWord(word);
     * boolean param_2 = obj.search(word);
     */
    public static void main(String[] args) {
        leetcode_0211.WordDictionary wd = new leetcode_0211().new WordDictionary();
        wd.addWord("at");
        wd.addWord("and");
        wd.addWord("an");
        wd.addWord("add");
        System.out.println(wd.search("a"));
        //result
        //false  不是单词终点
        System.out.println(wd.search(".at"));
        //result
        //false
        wd.addWord("bat");
        //result
        //true
        System.out.println(wd.search(".at"));
        //result
        //true
        System.out.println(wd.search("an."));
        //result
        //true
        System.out.println(wd.search("a.d."));
        //result
        //false
    }
}
