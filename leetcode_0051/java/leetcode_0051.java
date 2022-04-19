import java.util.ArrayList;
import java.util.Arrays;
import java.util.LinkedList;
import java.util.List;

public class leetcode_0051 {
    class Solution {
        public List<List<String>> solveNQueens(int n) {
            //思路:使用字符串数组来表示每一行 或者 int数组来表示每一行皇后的位置
            //回溯每一行，对每一行的每一列摆放进行验证
            char[] chs = new char[n];
            Arrays.fill(chs,'.');
            List<StringBuilder> sub = new ArrayList(n);
            for(int i = 0;i < n;i++)
                sub.add(new StringBuilder(String.valueOf(chs)));
            List<List<String>> res = new LinkedList();
            dfs(res,sub,n,0);
            return res;
        }
        private void dfs(List<List<String>> res,List<StringBuilder> sub,int n,int row){
            if(row == n){
                LinkedList<String> res_sub = new LinkedList();
                for(int i = 0;i < n;i++)
                    res_sub.add(sub.get(i).toString());
                res.add(res_sub);
                return ;
            }
            for(int i = 0;i < n;i++){
                if(valid(sub,n,row,i)){
                    sub.get(row).setCharAt(i,'Q');
                    dfs(res,sub,n,row+1);
                    sub.get(row).setCharAt(i,'.');
                }
            }
        }
        private boolean valid(List<StringBuilder> sub,int n,int row,int idx){
            //判断是否在同一列
            for(int i = 0;i < row;i++){
                if(sub.get(i).charAt(idx) == 'Q')
                    return false;
            }
            //判断是否在左上方
            for(int i = 0;i < row;i++){
                //row - idx = i - x
                int j = i - row + idx;
                if(j >= 0  && j < n && sub.get(i).charAt(j) == 'Q')
                    return false;
            }
            //判断是否在右上方
            for(int i = 0;i < row;i++){
                //row - (n-idx) = i - (n-x)
                int j = row + idx - i;
                if(j >= 0 && j < n && sub.get(i).charAt(j) == 'Q')
                    return false;
            }
            return true;
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
        int n = 4;
        leetcode_0051.Solution solution = new leetcode_0051().new Solution();
        List<List<String>> res = solution.solveNQueens(n);
        solution.printListArr(res);
        //result
        //[ [.Q.., ...Q, Q..., ..Q.] , [..Q., Q..., ...Q, .Q..] ]
    }
}
