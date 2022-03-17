import java.util.Deque;
import java.util.LinkedList;

public class leetcode_0020 {
    class Solution {
        public boolean isValid(String s) {
            Deque<Character> stk = new LinkedList();
            for(int i = 0;i < s.length();i++){
                if(s.charAt(i) == '(' || s.charAt(i) == '[' || s.charAt(i) == '{' )
                    stk.offerLast(s.charAt(i));
                else{
                    //否则 右边括号判断
                    if(stk.size() == 0)
                        return false;
                    else{
                        char topChar = stk.peekLast();
                        if(s.charAt(i) == ')' && topChar != '(' ||
                                s.charAt(i) == ']' && topChar != '[' ||
                                s.charAt(i) == '}' && topChar != '{' )
                            return false;
                        stk.pollLast();
                    }
                }
            }
            return stk.isEmpty();
        }
    }
    public static void main(String[] args) {
//        String s = "{[]}";
//        String s = "([)]";
        String s = "()[]{}";
        Solution solution = new leetcode_0020().new Solution();
        System.out.println(solution.isValid(s));
    }
}
