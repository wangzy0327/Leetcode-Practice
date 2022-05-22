import java.util.Arrays;

public class leetcode_0045 {
    class Solution {
        public int jump(int[] nums) {
            //思路：动态规划
            //dp(i)表示到达该位置的最少跳跃次数
            //动态转移方程 dp(i) = min(dp(j)+1) {j+nums[j] >= i}
            //初始状态dp(0) = 0
            //因为总是可以到达最后一个位置，所以设置跳跃的次数初始化为nums.size()
            int[] dp = new int[nums.length];
            Arrays.fill(dp,nums.length);
            dp[0] = 0;
            int nextIdx = 0;
            for(int i = 0;i < nums.length;i++){
                if(i + nums[i] <= nextIdx)
                    continue;
                nextIdx = Math.min(i+nums[i],nums.length-1);
                for(int j = i+1;j <= nextIdx;j++){
                    dp[j] = Math.min(dp[j],dp[i]+1);
                    if(j >= nums.length - 1)
                        return dp[j];
                }
            }
            return dp[nums.length - 1];
        }
        public int jump2(int[] nums) {
            //思路：贪心算法 greedy
            //每次只需要选择出 所能跳出的最具潜力的选择即可
            //用jump来表示跳跃次数
            int jump = 0;
            //表示下一跳的区间
            int nextIdx = 0;
            //在当前跳跃区间内所能达到的最远距离
            int farth = 0;
            //注意循环索引，到达最后num.length - 1是不用跳的，已经到达最后的位置了
            for(int i = 0;i < nums.length - 1;i++){
                //找出在[i...nextIdx]所能跳出的最远距离
                farth = Math.max(farth,i + nums[i]);
                //到达下一跳区间的末尾 更新
                if(i == nextIdx){
                    jump++;
                    //更新下一跳
                    nextIdx = farth;
                    //如果所能达到的最远索引距离达到最后索引，则返回
                    if(farth >= nums.length - 1)
                        return jump;
                }
            }
            return jump;
        }
    }
    public static void main(String[] args) {
        leetcode_0045.Solution solution = new leetcode_0045().new Solution();
        int[] nums = {2,3,1,1,4};
        //result
        //2
        //可以先跳 1 步，从下标 0 到达下标 1, 然后再从下标 1 跳 3 步到达最后一个下标
//    int[] nums = {2,3,0,1,4};
        //result
        //2
        System.out.println(solution.jump2(nums));
    }
}
