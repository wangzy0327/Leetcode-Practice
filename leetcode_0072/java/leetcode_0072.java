public class leetcode_0072 {
    class Solution {
        public int minDistance(String word1, String word2) {
            //首先拿到问题先考虑一种最极端的情况
            //如果word1为"",word2="ros",那word1转换到word2需要3步，每步插入一个字符
            //如果word1为"horse",word2="",那word1转换到word2需要5步，每步删除一个元素
            //我们可以假设word1的i索引位置字符到word2的j索引位置字符所需要的步数依赖于
            //dp[i-1,j-1](替换一个元素),dp[i-1,j](删除一个元素),dp[i,j-1](添加一个元素)
            //dp[i,j]代表word1从字符i到word2的字符j转换所需要的最少步数
            //当然这里有特殊情况，如果i索引的字符跟j索引的字符相等，则不需要替换直接跳过
            //状态转移方程: dp[i,j] = min(dp[i-1,j-1],dp[i-1,j],dp[i,j-1])+1| {i!=j}
            //dp[i,j] = min(dp[i-1,j-1],dp[i-1,j]+1,dp[i,j-1]+1) | {i==j}
            //初始状态：dp[0,j] = j , dp[i,0] = i
            //每个dp状态只跟左，左上，上有关 可状态压缩

            int m = word1.length();
            int n = word2.length();
            // int[][] dp = new int[m+1][n+1];
            // for(int i = 0;i < m + 1;i++)
            //     dp[i][0] = i;
            // for(int j = 0;j < n + 1;j++)
            //     dp[0][j] = j;
            //初始化
            int[] dp = new int[n+1];
            for(int i = 0;i < n + 1;i++)
                dp[i] = i;
            for(int i = 1;i < m + 1;i++){
                //记录边界左上dp[i][0]
                int pre = i - 1;
                //注意这里需要记录 左
                dp[0] = i;
                for(int j = 1;j < n + 1;j++){
                    int nextLeftUp = dp[j];
                    if(word1.charAt(i - 1) == word2.charAt(j - 1)){
                        // dp[i][j] = Math.min(dp[i][j-1]+1,Math.min(dp[i-1][j-1],dp[i-1][j]+1));
                        dp[j] = Math.min(dp[j-1]+1,Math.min(pre,dp[j]+1));
                    }else{
                        // dp[i][j] = Math.min(dp[i][j-1],Math.min(dp[i-1][j-1],dp[i-1][j]))+1;
                        dp[j] = Math.min(dp[j-1],Math.min(pre,dp[j]))+1;
                    }
                    //更新下一个左上
                    pre = nextLeftUp;
                }
            }
            return dp[n];
        }
    }
    public static void main(String[] args) {
        leetcode_0072.Solution solution = new leetcode_0072().new Solution();
        String word1 = "intention";
        String word2 = "execution";
        System.out.println(solution.minDistance(word1,word2));
        //result
        //5
        /**
         * intention -> inention (删除 't')
         * inention -> enention (将 'i' 替换为 'e')
         * enention -> exention (将 'n' 替换为 'x')
         * exention -> exection (将 'n' 替换为 'c')
         * exection -> execution (插入 'u')
         *
         *
         */
    }
}
