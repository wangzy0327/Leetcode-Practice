public class leetcode_0005 {
    class Solution {
        public String longestPalindrome(String s) {
            //思路：动态规划 用dp[i,j]来表示是否为回文字符串
            //初始状态dp[i,i]为true
            //dp[i,j] = dp[i+1,j-1] | s[i] == s[j]
            if(s.length() < 2)
                return s;
            //记录最长回文子串的起始位置和长度
            int start = 0;
            int maxLen = 1;
            int len = s.length();
            //初始化
            boolean[][] dp = new boolean[len][len];
            for(int i = len - 1;i >= 0;i--){
                dp[i][i] = true;
                if(i + 1 < len && s.charAt(i) == s.charAt(i+1)){
                    dp[i][i+1] = true;
                    start = i;
                    maxLen = 2;
                }
            }
            //从下往上 从左到右
            for(int i = len - 2;i >= 0;i--){
                for(int j = i + 2;j < len;j++){
                    if(s.charAt(i) == s.charAt(j)){
                        dp[i][j] = dp[i+1][j-1];
                        if(dp[i][j] && j - i + 1 >= maxLen){
                            start = i;
                            maxLen = j - i + 1;
                        }
                    }

                    else{
                        dp[i][j] = false;
                    }

                }
            }
            return s.substring(start,start+maxLen);
        }
    }
    public static void main(String[] args) {
        leetcode_0005.Solution solution = new leetcode_0005().new Solution();
        String s = "babad";
        System.out.println(solution.longestPalindrome(s));
        //result
        //"bab"  "aba" 同样是符合题意的答案。
    }
}
