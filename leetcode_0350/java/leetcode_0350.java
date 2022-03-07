import java.util.*;

public class leetcode_0350 {
    static class Solution {
        public static int[] intersect(int[] nums1, int[] nums2) {
            Map<Integer,Integer> record = new HashMap<Integer,Integer>();
            int[] iterArr = nums2;
            if(nums1.length <= nums2.length)
                minRecord(nums1,record);
            else{
                minRecord(nums2,record);
                iterArr = nums1;
            }
            List<Integer> arr = new LinkedList();
            for(int ele:iterArr){
                if(record.containsKey(ele))
                    arr.add(ele);
                else
                    continue;
                int val = record.get(ele).intValue();
                if(--val == 0)
                    record.remove(ele);
                else
                    record.put(ele,record.get(ele)-1);
            }
            return arr.stream().mapToInt(Integer::intValue).toArray();
        }
        private static void minRecord(int[] nums,Map<Integer,Integer> record){
            for(int ele : nums)
                record.put(ele,record.getOrDefault(ele,0)+1);
        }
    }
    public static void main(String[] args) {
        int[] nums1 = {1,2,2,1};
        int[] nums2 = {2,2};
        int[] res = Solution.intersect(nums1, nums2);
        System.out.println(Arrays.toString(res));
        //result
        //[2,2]
        //思考：
        //方法一：当前解决采用哈希表，时间复杂度为O(m+n),空间复杂度为O(min(m,n))
        //如果给定的数组已经是排好序的，则使用方法二：排序+双指针分别指向两个数组头右移进行操作,时间复杂度(mlogm+nlogn),空间复杂度O(1)
        //如果nums2的元素存储在磁盘上，内存是有限的，则不能使用方法二对数组进行高效的排序，则采用方法一
    }
}
