import java.util.Deque;
import java.util.LinkedList;

public class leetcode_0224 {
    class Solution {
        public int calculate(String s) {
            //将整个表达式计算看成是具有递归性质的一个数的抽象
            //具体到细节来讲，将每个数通过跟运算符的结合表示为一个整数
            //2-1 可以看做 2 + -1, 对于乘除法来说计算优先级高，计算为一个整数
            //((stack.top()) preSign  num) 为一个整数
            //处理乘除法，这里呢需要提前存储前一个操作数和前一个操作运算符
            //扩展的话，可以根据栈来存储运算符来进行运算符优先级判断
            //细节的话，这里需要提前存储一个 操作符+ 和前一个操作数0
            //对于括号的处理采用递归的思路
            Deque<Character> deq = new LinkedList();
            char[] chs = s.toCharArray();
            for(char c : chs)
                deq.addLast(c);
            int res = helper(deq);
            return res;
        }
        private int helper(Deque<Character> deq){
            //存储操作数栈
            Deque<Integer> stk = new LinkedList();
            int num = 0;
            char preSign = '+';
            while(deq.size() > 0){
                char c = deq.pollFirst();
                if(Character.isDigit(c))
                    num = num * 10 + (c - '0');
                if(c == '('){
                    num = helper(deq);
                }
                if(!Character.isDigit(c) && !Character.isSpaceChar(c) || deq.size() == 0){
                    if(preSign == '+')
                        stk.offerLast(num);
                    else if(preSign == '-')
                        stk.offerLast(-num);
                    else if(preSign == '*'){
                        int num1 = stk.peekLast();
                        stk.pollLast();
                        stk.offerLast(num1*num);
                    }else if(preSign == '/'){
                        int num1 = stk.peekLast();
                        stk.pollLast();
                        stk.offerLast(num1/num);
                    }
                    //重置
                    preSign = c;
                    num = 0;
                }
                if(c == ')')
                    break;
            }
            int res = 0;
            while(stk.size() > 0)
                res += stk.pollLast();
            return res;
        }
    }
    public static void main(String[] args) {
        Solution solution = new leetcode_0224().new Solution();
//        String s = "2147483647";
        String s = "(1+(4+5+2)-3)+(6+8)";
        System.out.println(solution.calculate(s));
    }
}
