import java.util.Arrays;
import java.util.LinkedList;
import java.util.List;

public class leetcode_0077 {
    class Solution {
        public List<List<Integer>> combine(int n, int k) {
            //思路：由于是组合，就不交换元素的先后顺序
            //而是每次递归依次序列递增找寻元素
            List<List<Integer>> res = new LinkedList();
            LinkedList<Integer> sub = new LinkedList();
            dfs(res,sub,n,1,k);
            return res;
        }
        private void dfs(List<List<Integer>> res,LinkedList<Integer> sub,int n,int start,int k){
            if(sub.size() == k){
                res.add(new LinkedList(sub));
                return ;
            }
            for(int i = start;i <= n;i++){
                //如果后序元素加上已有元素不足k则直接返回
                if(n - i + 1 + sub.size() < k)
                    return;
                sub.addLast(new Integer(i));
                dfs(res,sub,n,i+1,k);
                sub.removeLast();
            }
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
        leetcode_0077.Solution solution = new leetcode_0077().new Solution();
        int n = 4;int k = 2;
        //nums = [1,2,3,4] C(2,4)
        List<List<Integer>> res = solution.combine(n,k);
        solution.printListArr(res);
        //[ [1, 2] , [1, 3] , [1, 4] , [2, 3] , [2, 4] , [3, 4] ]
    }
}
