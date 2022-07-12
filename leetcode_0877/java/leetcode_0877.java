public class leetcode_0877 {
    class Solution {
        public boolean stoneGame(int[] piles) {
            //先手必赢的两个重要条件
            //1.石子总共有偶数堆
            //2.石子的总数为奇数
            /**
             如果要分出输赢的话，必定最后一个人得奇数，一个人得偶数;
             石子堆的数量是偶数个，所以两个人最后拿走的堆数是相同的。
             石子的摆放 按照所以可以分为 奇数索引堆 和 偶数 索引堆，而所有奇数索引堆 跟 所有偶数索引堆 石子总和一定不是相同的
             所以，先手的人可以判断 奇数索引堆石子总和 与 偶数索引堆石子总和 哪个多，而他可以控制是拿 偶数索引堆或者奇数索引堆
             */
            //ep: 偶数堆，奇数堆，偶数堆，奇数堆  (但凡取走一个堆，对手必定从其他（偶/奇）取走堆)
            return true;
        }
    }
    class Solution2{
        public boolean stoneGame(int[] piles) {
            //动态规划：
            //如果只有一堆石子，则直接取走 子问题为石子堆从[i,j]发挥最高水平时，石子差
            //用dp[i,j]来表示 当前选手与对手的石子堆的最大差
            //如果当前取piles[i],则dp[i+1,j]即为对方选手可以取得的石子堆与自己的差（反过来）,则需要相减
            //dp[i,j] = max(piles[i] - dp[i+1,j],piles[j] - dp[i,j-1])
            int n = piles.length;
            int[][] dp = new int[n][n];
            //最终求取 dp[0,n-1]的值是大于0还是小于0
            for(int i = 0;i < n;i++)
                dp[i][i] = piles[i];
            for(int i = n - 2;i >= 0;i--){
                for(int j = i+1;j < n;j++){
                    dp[i][j] = Math.max(piles[i] - dp[i+1][j],piles[j] - dp[i][j-1]);
                }
            }
            return dp[0][n-1] > 0;
        }
    }
    public static void main(String[] args) {
        leetcode_0877.Solution solution = new leetcode_0877().new Solution();
        leetcode_0877.Solution2 solution2 = new leetcode_0877().new Solution2();
        int[] piles = {5,3,4,5};
        boolean res = solution.stoneGame(piles);
        boolean res2 = solution2.stoneGame(piles);
        System.out.println(res);
        System.out.println(res2);
        //result true
        /**
         * 解释：
         * Alice 先开始，只能拿前 5 颗或后 5 颗石子 。
         * 假设他取了前 5 颗，这一行就变成了 [3,4,5] 。
         * 如果 Bob 拿走前 3 颗，那么剩下的是 [4,5]，Alice 拿走后 5 颗赢得 10 分。
         * 如果 Bob 拿走后 5 颗，那么剩下的是 [3,4]，Alice 拿走后 4 颗赢得 9 分。
         * 这表明，取前 5 颗石子对 Alice 来说是一个胜利的举动，所以返回 true 。
         *
         *
         */
    }
}
