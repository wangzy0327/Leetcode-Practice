import java.util.Arrays;
import java.util.LinkedList;
import java.util.List;

public class interview_0809 {
    class Solution {
        public List<String> generateParenthesis(int n) {
            //思路：采用回溯 , 由于括号需要配对，所以必定已经进入集合的左括号数量大于等于右括号
            //如果集合中左括号大于右括号则可以放入右括号，否则只能放入左括号
            List<String> res = new LinkedList();
            StringBuilder sb = new StringBuilder();
            //左括号数量 右括号数量
            int lNum = 0;
            int rNum = 0;
            dfs(res,sb,n,lNum,rNum);
            return res;
        }
        private void dfs(List<String> res,StringBuilder sb,int n,int lNum,int rNum){
            if(sb.length() == 2*n){
                res.add(sb.toString());
                return ;
            }
            //当左括号数量小于n 即可放入左括号
            if(lNum < n){
                sb.append("(");
                dfs(res,sb,n,lNum + 1,rNum);
                sb.deleteCharAt(sb.length()-1);
            }
            //当左括号数量大于右括号数量 可放入右括号
            if(lNum > rNum){
                sb.append(")");
                dfs(res,sb,n,lNum,rNum + 1);
                sb.deleteCharAt(sb.length()-1);
            }

        }
    }
    public static void main(String[] args) {
        interview_0809.Solution solution = new interview_0809().new Solution();
        int n = 3;
        List<String> res = solution.generateParenthesis(n);
        System.out.println(Arrays.toString(res.toArray(String[]::new)));
        //[((())), (()()), (())(), ()(()), ()()()]
    }
}
