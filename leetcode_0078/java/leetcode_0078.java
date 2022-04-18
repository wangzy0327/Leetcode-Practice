import java.util.Arrays;
import java.util.LinkedList;
import java.util.List;

public class leetcode_0078 {
    class Solution {
        public List<List<Integer>> subsets(int[] nums) {
            //思路：回溯
            int sz = nums.length;
            List<List<Integer>> res = new LinkedList();
            LinkedList<Integer> sub = new LinkedList();
            for(int i = 0;i <= sz;i++)
                dfs(res,sub,nums,0,i);
            return res;
        }
        private void dfs(List<List<Integer>> res,LinkedList<Integer> sub,int[] nums,int start,int k){
            if(sub.size() == k){
                res.add(new LinkedList(sub));
                return ;
            }
            for(int i = start;i < nums.length;i++){
                //如果后序元素加上已有元素不足k则直接返回
                if(sub.size() + nums.length - i + 1 < k)
                    return ;
                sub.addLast(Integer.valueOf(nums[i]));
                dfs(res,sub,nums,i+1,k);
                sub.removeLast();
            }
        }
        public <T> void printListArr(List<List<T>> list) {
            for (int i = 0; i < list.size(); i++) {
                if (i == list.size() - 1) {
                    if (i == 0)
                        System.out.printf("[ ");
                    System.out.println(Arrays.toString(list.get(i).toArray(Integer[]::new)) + " ] ");
                } else {
                    if (i == 0)
                        System.out.printf("[ ");
                    System.out.printf(Arrays.toString(list.get(i).toArray(Integer[]::new)) + " , ");
                }
            }
        }
    }
    public static void main(String[] args) {
        leetcode_0078.Solution solution = new leetcode_0078().new Solution();
        int[] nums = {1,2,3};
        List<List<Integer>> res = solution.subsets(nums);
        solution.printListArr(res);
        //[ [] , [1] , [2] , [3] , [1, 2] , [1, 3] , [2, 3] , [1, 2, 3] ]
    }
}
