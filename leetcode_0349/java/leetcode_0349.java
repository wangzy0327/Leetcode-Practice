import java.util.Arrays;
import java.util.HashSet;
import java.util.Set;

public class leetcode_0349 {
    static class Solution {
        public static int[] intersection(int[] nums1, int[] nums2) {
            Set<Integer> record = new HashSet();
            Set<Integer> inter = new HashSet();
            for(int num : nums1)
                record.add(num);
            for(int num : nums2){
                if(record.contains(num))
                    inter.add(num);
            }
            int[] res = new int[inter.size()];
            int i = 0;
            for(Integer tmp:inter)
                res[i++] = tmp.intValue();
            return res;
        }
    }
    public static void main(String[] args) {
        int[] nums1 = {1,2,2,1};
        int[] nums2 = {2,2};
        int[] res = Solution.intersection(nums1, nums2);
        System.out.println(Arrays.toString(res));
        //result
        //[2]
    }
}
