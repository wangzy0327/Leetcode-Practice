import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class leetcode_0491 {
    class Solution {
        private List<Integer> tmp;
        private List<List<Integer>> res;
        private void dfs(int cur,int lastEle,int[] nums){
            if(cur == nums.length){
                if(tmp.size() >= 2)
                    res.add(new ArrayList(tmp));
                return ;
            }
            //选择当前元素
            if(nums[cur] >= lastEle){
                tmp.add(nums[cur]);
                dfs(cur+1,nums[cur],nums);
                tmp.remove(tmp.size()-1);
            }
            //跳过当前元素
            if(nums[cur] != lastEle){
                dfs(cur+1,lastEle,nums);
            }
        }
        public List<List<Integer>> findSubsequences(int[] nums) {
            tmp = new ArrayList();
            res = new ArrayList<List<Integer>>();
            dfs(0,Integer.MIN_VALUE,nums);
            return res;
        }
        public <T> void printArr(T[][] arr) {
            System.out.print("[ ");
            String res = "";
            for (int i = 0; i < arr.length; i++)
                res += Arrays.toString(arr[i])+",";
            res = res.substring(0,res.length()-1);
            System.out.print(res);
            System.out.println(" ]");
        }
        public <T> void printListArr(List<List<T>> list) {
            for (int i = 0; i < list.size(); i++) {
                if (i == list.size() - 1) {
                    if (i == 0)
                        System.out.printf("[ ");
                    System.out.println(Arrays.toString(list.get(i).toArray((T[]) new Object[0])) + " ] ");
                } else {
                    if (i == 0)
                        System.out.printf("[ ");
                    System.out.printf(Arrays.toString(list.get(i).toArray((T[]) new Object[0])) + " , ");
                }
            }
        }
    }
    public static void main(String[] args) {
        leetcode_0491.Solution solution = new leetcode_0491().new Solution();
        int[] nums = {4,6,7,7};
        List<List<Integer>> subsequences = solution.findSubsequences(nums);
        solution.printListArr(subsequences);
        //[ [4, 6, 7, 7] , [4, 6, 7] , [4, 6] , [4, 7, 7] , [4, 7] , [6, 7, 7] , [6, 7] , [7, 7] ]
    }
}
