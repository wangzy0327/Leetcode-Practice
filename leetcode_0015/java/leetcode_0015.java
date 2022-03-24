import java.util.Arrays;
import java.util.LinkedList;
import java.util.List;

public class leetcode_0015 {
    class Solution {
        public List<List<Integer>> threeSum(int[] nums) {
            //暴力解法：O(n^3)
            //思路：先排序O(nlogn)，然后依次选定元素 对 后面的列表进行双指针判定O(n^2)
            //1.排序
            List<List<Integer>> res = new LinkedList<>();
            //1.排序
            Arrays.sort(nums);
            //2.双指针 判定
            for(int i = 0;i < nums.length;i++){
                if(i == 0 || nums[i] != nums[i-1]){
                    dfs(nums[i],res,nums,i+1,nums.length - 1);
                }
            }
            return res;
        }
        private void dfs(int target,List<List<Integer>> res,int[] nums,int start,int end){
            List<Integer> sub = new LinkedList();
            while(start < end){
                if(nums[start] + nums[end] < -target)
                    start++;
                else if(nums[start] + nums[end] > -target)
                    end--;
                else{
                    //nums[start] + nums[end] == -target
                    sub.add(target);
                    sub.add(nums[start]);
                    sub.add(nums[end]);
                    res.add(new LinkedList(sub));
                    sub.clear();
                    while(start < end && nums[start + 1] == nums[start])
                        start++;
                    start++;
                    while(start < end && nums[end - 1] == nums[end])
                        end--;
                    end--;
                }
            }
        }
    }
    public static void main(String[] args) {
        Solution solution = new leetcode_0015().new Solution();
//        int[] nums = {-1,0,1,2,-1,-4};
        //result
        //[ [-1, -1, 2] , [-1, 0, 1] ]
        int[] nums = {-1,0,1,1,2,-1,-1,2,-1,2,-4};
        //result
        //[ [-4, 2, 2] , [-1, -1, 2] , [-1, 0, 1] ]
        List<List<Integer>> res = solution.threeSum(nums);
        for(int i = 0;i < res.size();i++){
            if(i == res.size() - 1){
                if(i == 0)
                    System.out.printf("[ ");
                System.out.println(Arrays.toString(res.get(i).toArray(Integer[]::new))+" ] ");
            }else{
                if(i == 0)
                    System.out.printf("[ ");
                System.out.printf(Arrays.toString(res.get(i).toArray(Integer[]::new))+" , ");
            }
        }
    }
}
