import java.util.Arrays;
import java.util.LinkedList;
import java.util.List;

public class leetcode_0438 {
    class Solution {
        public List<Integer> findAnagrams(String s, String p) {
            //滑动窗口
            //采用哈希表来保存子串的种类和数量
            //利用valid整型来标识 是否满足异位词
            //由于只包含小写字母这里采用数组来表示
            int[] need = new int[26];
            for(char c : p.toCharArray())
                need[c-'a']++;
            int sz = 0;
            for(int i = 0;i < need.length;i++)
                if(need[i] > 0)
                    sz++;

            int[] window = new int[26];
            int left = 0;int right = 0;
            List<Integer> res = new LinkedList();
            int valid = 0;
            while(right < s.length()){
                if(right - left < p.length()){
                    char c = s.charAt(right);
                    int idx = c - 'a';
                    if(need[idx] > 0){
                        window[idx]++;
                        if(window[idx] == need[idx])
                            valid++;
                    }
                    right++;
                }
                if(right - left == p.length()){
                    if(valid == sz){
                        res.add(left);
                    }
                    char c = s.charAt(left);
                    int idx = c - 'a';
                    if(need[idx] > 0){
                        if(window[idx] == need[idx])
                            valid--;
                        window[idx]--;
                    }
                    left++;
                }
            }
            return res;
        }
    }
    public static void main(String[] args) {
        String s = "cbaebabacd";
        String p = "abc";
//      String s = "abab";
//      String p = "ab";
//  result
//  [0,1,2]
        Solution solution = new leetcode_0438().new Solution();
        System.out.println(Arrays.toString(solution.findAnagrams(s,p).toArray(Integer[]::new)));
        //result
        //[0,6]
    }
}
