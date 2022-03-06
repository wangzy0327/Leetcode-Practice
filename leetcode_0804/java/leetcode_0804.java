import java.util.HashSet;
import java.util.Set;

public class leetcode_0804 {
    static class Solution {
        public static int uniqueMorseRepresentations(String[] words) {
            Set<String> record = new HashSet();
            String[] morse = {
                    ".-","-...","-.-.","-..",".","..-.","--.","....","..",".---","-.-",".-..","--","-.","---",".--.","--.-",".-.","...","-","..-","...-",".--","-..-","-.--","--.."
            };
            StringBuilder tmp = new StringBuilder();
            for(String ele:words){
                tmp.delete(0,tmp.length());
                char[] arr = ele.toCharArray();
                for(char alpha:arr)
                    tmp.append(morse[alpha - 'a']);
                record.add(tmp.toString());
            }
            return record.size();
        }
    }

    public static void main(String[] args) {
        String[] words = {"gin", "zen", "gig", "msg"};
//        各单词翻译如下:
//        "gin" -> "--...-."
//        "zen" -> "--...-."
//        "gig" -> "--...--."
//        "msg" -> "--...--."
//
//        共有 2 种不同翻译, "--...-." 和 "--...--.".
        int res = Solution.uniqueMorseRepresentations(words);
        System.out.println(res);
        //result
        //2
    }
}
