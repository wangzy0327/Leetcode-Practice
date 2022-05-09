public class leetcode_0010 {
    class Solution {
        public boolean isMatch(String s, String p) {
            //思路:动态规划
            //如果pattern当前字符是'.'的话,则其可以匹配任意s字符串中的当前字符
            //如果pattern当前字符是'*'的话，则其匹配前一个pattern中字符0次或n次
            //dp[i,j]表示p的前i个字符是否跟s的前j个字符匹配
            //初始状态dp[0,0] = 1;1表示匹配,0表示不匹配
            //状态转移方程 dp[i,j] = dp[i-1,j-1] { p[i-1]=='.' | p[i-1] == s[j-1]}

            //dp[i,j] = dp[i-2,j]|dp[i-1][j]|dp[i][j-1] {(p[i-2]==s[j-1]} || p[i-2]=='.') && p[i] == '*' | {匹配0个|匹配1个|匹配多个}
            //dp[i,j] = dp[i-2][j] {(p[i-2] != s[j-1] && p[i-2] != '.') && p[i] == '*'}
            //初始状态 dp[0,0] = 1

            int m = p.length();
            int n = s.length();
            boolean[][] dp = new boolean[m+1][n+1];
            dp[0][0] = true;
            //初始化 很重要
            // "" "c*" 匹配
            for(int i = 2;i <= m;i++){
                if(p.charAt(i-1) == '*')
                    dp[i][0] = dp[i-2][0];
            }
            for(int i = 1;i < m+1;i++){
                for(int j = 1;j < n+1;j++){
                    if(p.charAt(i-1) == s.charAt(j-1) || p.charAt(i-1) == '.'){
                        dp[i][j] = dp[i-1][j-1];
                    }else if(p.charAt(i-1) == '*'){
                        //匹配0个
                        if(p.charAt(i-2) != s.charAt(j-1) && p.charAt(i-2) != '.'){
                            dp[i][j] = dp[i-2][j];
                        }else{
                            //.*就相当于.. , 那就只要看前面匹不匹配就行
                            //匹配多个
                            dp[i][j] = (dp[i-2][j] | dp[i][j-1] | dp[i-1][j]);
                        }
                    }
                }
            }
            return dp[m][n];
        }
    }
    public static void main(String[] args) {
//    String s = "aaa";
//    String p = "a*";
        //result
        //true
        //因为 '*' 代表可以匹配零个或多个前面的那一个元素, 在这里前面的元素就是 'a'。因此，字符串 "aa" 可被视为 'a' 重复了一次
        String s = "aab";
        String p = "c*a*b";
        //result
        //true
//    String s = "ab";
//    String p = ".*";
        //result
        //true
        //".*" 表示可匹配零个或多个（'*'）任意字符（'.'）
        leetcode_0010.Solution solution = new leetcode_0010().new Solution();
        System.out.println(solution.isMatch(s, p));
    }
}
