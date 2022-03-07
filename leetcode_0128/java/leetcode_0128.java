import java.util.HashSet;
import java.util.Set;

public class leetcode_0128 {
    class Solution {
        public int longestConsecutive(int[] nums) {
            //首先要读懂题意 什么是连续的序列
            // 举栗 [100,4,200,1,3,2] 中 1,2,3,4是连续的整数就是连续序列(不要求它们本身有顺序)
            //每次只有最小的数字 去统计长度，避免中间数字统计，如果遇到前后有连续的数字跳过
            Set<Integer> record = new HashSet();
            //去重减少重复元素的判断
            for(int num : nums)
                record.add(num);
            int longestSeqLen = 0;
            for(Integer num : record){
                int curLen = 1;
                //从连续序列最下数值开始，ep[100,4,200,1,3,2] 只从1开始，其他跳过
                //内层循环判断连续序列的长度进行比较
                if(!record.contains(num - 1)){
                    for(int j = num + 1;record.contains(j);j++)
                        curLen++;
                    longestSeqLen = Math.max(curLen,longestSeqLen);
                }
            }
            return longestSeqLen;
        }
    }
    public static void main(String[] args) {
        int[] nums = new int[]{100,4,200,1,3,2};
        int res = new leetcode_0128().new Solution().longestConsecutive(nums);
        System.out.println(res);
    }
}
