public class leetcode_0003 {
    class Solution {
        public int lengthOfLongestSubstring(String s) {
            int res = 0;
            //字符表
            int[] window = new int[128];
            int left = 0,right = 0;
            while(right < s.length()){
                while(right < s.length() && window[s.charAt(right)] == 0){
                    window[s.charAt(right)] = 1;
                    right++;
                    if(right - left > res)
                        res = right - left;
                }
                if(right < s.length() && window[s.charAt(right)] == 1){
                    window[s.charAt(left)] = 0;
                    left++;
                }
            }
            return res;
        }
    }
    public static void main(String[] args) {
        Solution solution = new leetcode_0003().new Solution();
        String s = "abcabcbb";
        //result
        //3
//        String s = "bbbbb";
        //result
        //1
//        String s = "pwwkew";
        //result
        //3
        System.out.println(solution.lengthOfLongestSubstring(s));
    }
}
