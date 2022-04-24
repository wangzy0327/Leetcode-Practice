import java.util.HashMap;
import java.util.Map;

public class leetcode_0560 {
    class Solution {
        public int subarraySum(int[] nums, int k) {
            //思路:转化求子数组的和为k 为 寻找前缀和为sum[i] - k的个数
            //前缀和+哈希
            //原先寻找sum[i...j]的和是否为k,需要每次遍历j和i,结果就为O(n*n)
            //现在转化为寻找sum[i...j] - k的前缀和的个数(用哈希记录)
            Map<Integer,Integer> record = new HashMap();
            int count = 0;
            int sum = 0;
            record.put(0,1);
            for(int i = 0;i < nums.length;i++){
                sum += nums[i];
                if(record.containsKey(sum - k))
                    count += record.get(sum-k);
                record.put(sum,record.getOrDefault(sum,0)+1);
            }
            return count;
        }
    }
    public static void main(String[] args) {
        leetcode_0560.Solution solution = new leetcode_0560().new Solution();
        int[] nums = {1,2,3};
        int k = 3;
        int res = solution.subarraySum(nums, k);
        System.out.println(res);
        //result
        //2
    }
}
