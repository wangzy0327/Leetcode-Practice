import java.util.Arrays;
import java.util.LinkedList;
import java.util.List;

public class leetcode_0046 {
    class Solution {
        public List<List<Integer>> permute(int[] nums) {
            //思路：回溯 dfs 每次交换当前元素与后序元素然后向后移动序列
            List<List<Integer>> res = new LinkedList();
            LinkedList<Integer> sub = new LinkedList();
            dfs(res,nums,sub,0,nums.length - 1);
            return res;
        }
        private void dfs(List<List<Integer>> res,int[] nums,LinkedList<Integer> sub,int start,int end){
            if(start > end)
                return;
            else if(start == end){
                sub.addLast(new Integer(nums[start]));
                res.add(new LinkedList(sub));
                sub.removeLast();
                return;
            }
            for(int i = start;i <= end;i++){
                swap(nums,start,i);
                sub.addLast(new Integer(nums[start]));
                dfs(res,nums,sub,start+1,end);
                sub.removeLast();
                swap(nums,start,i);
            }
        }
        private void swap(int[] nums,int i,int j){
            int tmp = nums[i];
            nums[i] = nums[j];
            nums[j] = tmp;
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
        leetcode_0046.Solution solution = new leetcode_0046().new Solution();
        int[] nums = {1,2,3};
        //nums = [1,2,3]
        List<List<Integer>> res = solution.permute(nums);
        solution.printListArr(res);
        //[[1,2,3],[1,3,2],[2,1,3],[2,3,1],[3,1,2],[3,2,1]]
    }
}
