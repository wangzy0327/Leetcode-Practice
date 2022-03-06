import java.util.Arrays;
import java.util.HashMap;
import java.util.Map;

public class leetcode_0001 {
    static class Solution {
        public static int[] twoSum(int[] nums, int target) {
            Map<Integer, Integer> map = new HashMap();
            for (int i = 0; i < nums.length; i++) {
                int pairNum = target - nums[i];
                if (map.containsKey(pairNum)) {
                    int j = map.get(pairNum);
                    if(i > j){
                        int tmp = i;
                        i = j;j = tmp;
                    }
                    return new int[]{i,j};
                }
                map.put(nums[i], i);
            }
            return new int[]{-1, -1};
        }
    }
    public static void main(String[] args) {
        int[] nums = {2,7,11,15};
        System.out.println(Arrays.toString(nums));
        int target = 9;
        System.out.println(Arrays.toString(Solution.twoSum(nums,target)));
        //result
        //[0, 1]
    }
}
