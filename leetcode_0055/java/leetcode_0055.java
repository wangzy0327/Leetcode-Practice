public class leetcode_0055 {
    class Solution {
        public boolean canJump(int[] nums) {
            //思路：贪心算法 greedy
            // 根据索引遍历不断更新过往索引能达到的最大索引位置
            //如果超过 最后一个下标索引 则返回true,否则返回false
            int tar_idx = nums.length - 1;
            //最大索引位置初始化为0
            int num_idx = 0;
            for(int i = 0;i <= num_idx;i++){
                num_idx = Math.max(num_idx,i+nums[i]);
                if(num_idx >= tar_idx)
                    return true;
            }
            return false;
        }
    }
    public static void main(String[] args) {
        leetcode_0055.Solution solution = new leetcode_0055().new Solution();
        int[] nums = {2,3,1,1,4};
        //result
        //true
        //可以先跳 1 步，从下标 0 到达下标 1, 然后再从下标 1 跳 3 步到达最后一个下标
//        int[] nums = {3,2,1,0,4};
        //result
        //false
        //无论怎样，总会到达下标为 3 的位置。但该下标的最大跳跃长度是 0 ， 所以永远不可能到达最后一个下标。
        System.out.println(solution.canJump(nums));
    }
}
