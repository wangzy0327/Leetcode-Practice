public class leetcode_0213 {
    class Solution {
        public int rob(int[] nums) {
            //思路：由于围城一个环，所以首尾两个数不能都选
            //拆分 分别取(start,end) = (0,n-2)和(start,end)=(1,n-1)进行计算，取两个dp[end]中的最大值，即可得到最终结果
            //边界条件
            //dp[start] = num[start] 只有一间房，直接取 | dp[start+1] = max(nums[start],nums[start+1) 只有两间房，取其中最大的
            //动态规划 dp[i]表示i个屋子能达到的最高金额
            //dp[i] = max(dp[i-1],dp[i-2]+nums[i]) (i >= 2)
            int n = nums.length;
            if(n == 1)
                return nums[0];
            if(n == 2)
                return Math.max(nums[0],nums[1]);
            //(0,n-2)范围内
            //dp[i-2]
            int prevv = 0;
            int prev = nums[0];
            int dp_0 = 0;
            for(int i = 1;i < n - 1;i++){
                //dp[i] = max(dp[i-2]+nums[i],dp[i-1])
                dp_0 = Math.max(prev,prevv+nums[i]);
                //更新下一个dp[i-2] 为当前dp[i-1]
                prevv = prev;
                ////更新下一个dp[i-1] 为当前dp[i]
                prev = dp_0;
            }
            //(1,n-1)范围内
            prevv = 0;
            prev = nums[1];
            int dp_1 = 0;
            //注意这范围是[1,n-1],所以从下一个即2开始取
            for(int i = 2;i < n;i++){
                //dp[i] = max(dp[i-2]+nums[i],dp[i-1])
                dp_1 = Math.max(prev,prevv+nums[i]);
                //更新下一个dp[i-2] 为当前dp[i-1]
                prevv = prev;
                ////更新下一个dp[i-1] 为当前dp[i]
                prev = dp_1;
            }
            return Math.max(dp_0,dp_1);
        }
    }
    public static void main(String[] args) {
        leetcode_0213.Solution solution = new leetcode_0213().new Solution();
        int[] nums = {2,3,2};
        //result
        //3
        //你不能先偷窃 1 号房屋（金额 = 2），然后偷窃 3 号房屋（金额 = 2）, 因为他们是相邻的
        System.out.println(solution.rob(nums));
    }
}
