import java.util.Deque;
import java.util.LinkedList;

public class offer_0016 {
    class Solution {
        public int calculate(String s) {
            Deque<Character> deq = new LinkedList();
            for(int i = 0;i < s.length();i++)
                deq.addLast(s.charAt(i));
            int res = helper(deq);
            return res;
        }
        private int helper(Deque<Character> deq){
            Deque<Integer> stk = new LinkedList();
            int num = 0;
            char preSign = '+';
            while(deq.size() > 0){
                char c = deq.pollFirst();
                if(Character.isDigit(c))
                    num = num * 10 + (c - '0');
                if(c == '(')
                    num = helper(deq);
                if(!Character.isDigit(c) && !Character.isSpaceChar(c) || deq.size() == 0){
                    if(preSign == '+')
                        stk.offerLast(num);
                    else if(preSign == '-')
                        stk.offerLast(-num);
                    else if(preSign == '*'){
                        int preNum = stk.pollLast();
                        stk.offerLast(preNum*num);
                    }else if(preSign == '/'){
                        int preNum = stk.pollLast();
                        stk.offerLast(preNum/num);
                    }
                    num = 0;
                    preSign = c;
                }
                if(c == ')')
                    break;
            }
            int res = 0;
            while(stk.size() > 0)
                res += stk.pollFirst();
            return res;
        }
    }
    public static void main(String[] args) {
        Solution solution = new offer_0016().new Solution();
//        String s = "2147483647";
//        String s = "(1+(4+5+2)-3)+(6+8)";
        //result 23
        String s = " 3+5 / 2 ";
        //result 5
        System.out.println(solution.calculate(s));
    }
}
