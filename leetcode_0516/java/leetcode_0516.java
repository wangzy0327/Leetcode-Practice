public class leetcode_0516 {
    class Solution {
        public int longestPalindromeSubseq(String s) {
            //思路：动态规划
            //根据回文子序列的定义可知
            //重叠子问题 dp[i,j] 回文子序列长度
            //初始状态 dp[i,i] 为 1
            //状态 变量 是i,j
            //状态转移方程 dp[i,j] = dp[i+1,j-1] + 2 | s[i]==s[j] & j-i>=2
            //dp[i,j] = max(dp[i,j-1],dp[i+1,j]) | s[i]!=s[j]
            //由于dp[i,j] 只与dp[i+1,j](下),dp[i,j-1](左),dp[i+1,j-1](左下)有关
            //通过状态转移方程可知，遍历顺序从下向上，从左向右
            int len = s.length();
            int[] dp = new int[len];
            //初始化dp[i][i]
            for(int i = 0;i < len;i++)
                dp[i] = 1;
            for(int i = len - 2;i >= 0;i--){
                //int pre = dp[i+1][j-1]
                //dp[i+1][i]
                int pre = 0;
                for(int j = i+1;j < len;j++){
                    //dp[i+1][j]
                    int temp = dp[j];
                    if(s.charAt(i) == s.charAt(j)){
                        //dp[i][j] = dp[i+1][j-1] + 2
                        dp[j] = pre + 2;
                    }else{
                        //dp[i][j] = max(dp[i+1][j],dp[i][j-1])
                        dp[j] = Math.max(dp[j],dp[j-1]);
                    }
                    pre = temp;
                }
            }
            return dp[len-1];
        }
    }
    public static void main(String[] args) {
        leetcode_0516.Solution solution = new leetcode_0516().new Solution();
        //子序列定义为：不改变剩余字符顺序的情况下，删除某些字符或者不删除任何字符形成的一个序列
        String s = "bbbab";
        System.out.println(solution.longestPalindromeSubseq(s));
        //result
        //4
        //一个可能的最长回文子序列为 "bbbb"
    }
}
