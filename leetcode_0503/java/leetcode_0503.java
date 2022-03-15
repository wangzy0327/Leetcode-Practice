import java.util.Arrays;
import java.util.Deque;
import java.util.LinkedList;

public class leetcode_0503 {
    class Solution {
        public int[] nextGreaterElements(int[] nums) {
            //单调栈 + 循环数组
            //模拟栈 存储数组索引
            //遍历数组，当遇到当前值大于 栈顶索引对应元素循环执行，则将对应索引改为当前值
            //保持栈始终 按照对应数组索引值的 递减顺序 或者栈为空
            //最终将栈中的元素取出 对应索引位置 赋值为 -1
            //单调栈
            //双端队列
            Deque<Integer> dq = new LinkedList();
            int[] res = new int[nums.length];
            for(int i = 0;i < res.length;i++)
                res[i] = -1;
            int sz = nums.length * 2;
            for(int i = 0;i < sz;i++){
                int j = i%nums.length;
                while(!dq.isEmpty() && nums[dq.peekLast()] < nums[j]){
                    res[dq.peekLast()] = nums[j];
                    dq.pollLast();
                }
                dq.offerLast(j);
            }
            return res;
        }
    }
    public static void main(String[] args) {
        Solution solution = new leetcode_0503().new Solution();
        int[] nums = {5,4,3,2,1};
//        int[] nums = {1,2,3,4,3};
        System.out.println(Arrays.toString(solution.nextGreaterElements(nums)));
    }
}
