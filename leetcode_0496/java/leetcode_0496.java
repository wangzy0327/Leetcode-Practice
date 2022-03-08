import java.util.Arrays;
import java.util.HashMap;
import java.util.LinkedList;
import java.util.Map;

public class leetcode_0496 {
    class Solution {
        public int[] nextGreaterElement(int[] nums1, int[] nums2) {
            Map<Integer,Integer> record = new HashMap();
            for(int i = 0;i < nums2.length;i++)
                record.put(nums2[i],i);
            int[] res = new int[nums1.length];
            int[] ans = new int[nums2.length];
            //双向链表模拟栈
            LinkedList<Integer> stack = new LinkedList();
            for(int i = nums2.length-1;i >= 0;i--){
                //如果当前元素大于栈顶元素，则一直弹出栈顶元素
                while(!stack.isEmpty() && nums2[i] >= stack.peekLast())
                    stack.removeLast();
                //将栈顶元素(大于当前元素)或-1放入结果集中
                ans[i] = (stack.isEmpty())?-1:stack.peekLast();
                //当前元素进栈
                stack.offerLast(nums2[i]);
            }
            for(int i = 0;i < nums1.length;i++)
                res[i] = ans[record.get(nums1[i])];
            return res;
        }
    }
    public static void main(String[] args) {
        int[] nums1 = {4,1,2};
        int[] nums2 = {1,3,4,2};
        Solution solution = new leetcode_0496().new Solution();
        int[] res = solution.nextGreaterElement(nums1,nums2);
        System.out.println(Arrays.toString(res));
    }
}
