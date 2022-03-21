import java.util.HashMap;
import java.util.Map;

public class leetcode_0076 {
    class Solution {
        public String minWindow(String s, String t) {
            //采用哈希表存储t所需要的每个字符数量和字符种类
            //滑动窗口(当字符种类少于 所需种类 右边界向右滑动)
            // 当字符种类等于 所需种类 左边界向右滑动
            //滑动窗口退出条件，右边界滑动到最大长度 并且 valid小于所需字符种类
            //如果滑动窗口该字符数量达到所需字符数量则 有效数量+1
            Map<Character,Integer> need = new HashMap();
            char[] tArr = t.toCharArray();
            for(char c : tArr)
                need.put(c,need.getOrDefault(c,0)+1);
            Map<Character,Integer> window = new HashMap();
            //valid 所需字符种类
            int valid = 0;
            int left = 0;
            int right = 0;
            //[0,0)
            //最小子串左侧索引 ，长度
            int start = 0,len = Integer.MAX_VALUE;
            while(right < s.length() || valid == need.size()){
                if(valid < need.size()){
                    char rChar = s.charAt(right);
                    if(need.containsKey(rChar)){
                        window.put(rChar,window.getOrDefault(rChar,0)+1);
                        //注意Integer 不能用 == 比较 否则出现bug
                        if(window.get(rChar).intValue() == need.get(rChar).intValue())
                            valid++;
                    }
                    right++;
                }
                if(valid == need.size()){
                    char lChar = s.charAt(left);
                    // [left,right)
                    if(len > right - left){
                        len = right - left;
                        start = left;
                    }
                    if(need.containsKey(lChar)){
                        if(window.get(lChar).intValue() == need.get(lChar).intValue())
                            valid--;
                        window.put(lChar,window.get(lChar) - 1);
                    }
                    left++;
                }
            }
            return (len == Integer.MAX_VALUE)?"":s.substring(start,start+len);
        }
    }
    public static void main(String[] args) {
        Solution solution = new leetcode_0076().new Solution();
        String s = "ADOBECODEBANC";
        String t = "ABC";
        String res = solution.minWindow(s, t);
        System.out.println(res);
    }
}
