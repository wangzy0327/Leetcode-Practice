import java.util.Arrays;
import java.util.Deque;
import java.util.LinkedList;

public class offer_0059 {
    class Solution {
        public int[] maxSlidingWindow(int[] nums, int k) {
            //暴力：如果每次都要比较k窗口的数值，则时间复杂度为(k*n)
            //优化：这里只需要维持一个队列保证 队头到队尾是 单调队(队列里面存储索引，保证入队出队)
            //滑动窗口最大值, 这里需要维护一个大小为k的双端队列
            //双端队列里存储索引
            if(nums.length == 0)
                return new int[0];
            Deque<Integer> deq = new LinkedList();
            for(int i = 0;i < k;i++)
                helper(deq,nums,i);
            int[] res = new int[nums.length - k + 1];
            res[0] = nums[deq.peekFirst()];
            //[i,i+k)
            for(int i = k;i < nums.length;i++){
                //移除滑动窗口 如果队头索引相同
                if(deq.peekFirst() == i - k)
                    deq.pollFirst();
                helper(deq,nums,i);
                res[i-k+1] = nums[deq.peekFirst()];
            }
            return res;
        }
        //保持双端队列里按照从大到小排序  单调队列
        private void helper(Deque<Integer> deq, int[] nums, int k){
            int ele = nums[k];
            if(deq.size() == 0)
                deq.add(k);
            else{
                //保持队列是单调减小的
                while(!deq.isEmpty() && nums[deq.peekLast()] < ele)
                    deq.pollLast();
                deq.offerLast(k);
            }
        }
    }
    public static void main(String[] args) {
        leetcode_0239.Solution solution = new leetcode_0239().new Solution();
        int[] nums = {1,3,-1,-3,5,3,6,7};
        int k = 3;
        System.out.println(Arrays.toString(solution.maxSlidingWindow(nums,k)));
        //result
        //[3,3,5,5,6,7]
    }
}
