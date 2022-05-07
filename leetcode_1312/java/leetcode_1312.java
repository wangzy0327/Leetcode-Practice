public class leetcode_1312 {
    class Solution {
        public int minInsertions(String s) {
            //思路：动态规划 s[i,j]表示s的子串，如果s[i]==s[j],则只需考虑如何计算出s[i+1,j-1]的最小操作数
            //如果s[i]!=s[j],则需要计算出将s[i+1,j]变换到回文串需要最小操作数或变换到s[i,j-1]的最小操作数，加1
            //dp[i,j]表示字符串s[i,j]变换到回文字符串需要的最小插入操作次数
            //dp[i,j] = dp[i+1,j-1] {s[i]==s[j]} | min(dp[i,j-1],dp[i+1,j])+1 {s[i]!=s[j]}
            //初始状态 dp[i,i] = 0 {i>=0 && i < s.size()}
            int sz = s.length();
            // int[][] dp = new int[sz][sz];
            //压缩空间
            int[] dp = new int[sz];
            //初始化 可省略
            for(int i = sz-2;i >= 0;i--){
                //存储第一个左下 dp[i+1][j-1]
                int pre = 0;
                for(int j = i+1;j < sz;j++){
                    //存储下一个左下
                    int nextLeftDown = dp[j];
                    if(s.charAt(i) == s.charAt(j)){
                        // dp[i][j] = dp[i+1][j-1];
                        dp[j] = pre;
                    }else{
                        // dp[i][j] = Math.min(dp[i+1][j],dp[i][j-1])+1;
                        dp[j] = Math.min(dp[j],dp[j-1]) + 1;
                    }
                    //更新下一个左下
                    pre = nextLeftDown;
                }
            }
            return dp[sz-1];
        }
    }
    public static void main(String[] args) {
        leetcode_1312.Solution solution = new leetcode_1312().new Solution();
        String s = "leetcode";
        //result 5
        //插入 5 个字符后字符串变为 "leetcodocteel"
//        String s = "mbadm";
        //result 2
        //字符串可变为 "mbdadbm" 或者 "mdbabdm"
        System.out.println(solution.minInsertions(s));
    }
}
