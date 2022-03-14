import java.util.Deque;
import java.util.LinkedList;
import java.util.List;

public class leetcode_0394 {
    class Solution {
        //双端队列 模拟栈 来存储 整数
        private Deque<Integer> dq;
        //双向链表 模拟栈来存储字符串
        private LinkedList<String> list;
        public String decodeString(String s) {
            dq = new LinkedList<>();
            list = new LinkedList<>();
            char[] chs = s.toCharArray();
            for(int i = 0;i < chs.length;){
                //判断是否为数字
                if(Character.isDigit(chs[i])){
                    int num = 0;
                    while(Character.isDigit(chs[i]))
                        num = num * 10 + chs[i++] - '0';
                    //将数字放入双端队列中
                    dq.addLast(num);
                }else if(Character.isAlphabetic(chs[i])){
                    //判断是否为字母
                    String str = "";
                    while(i < chs.length && Character.isAlphabetic(chs[i]))
                        str += chs[i++];
                    list.add(str);
                }else if(chs[i] == '['){
                    //左括号
                    //将左括号入栈
                    list.add("[");
                    i++;continue;//跳出 后面判断字母
                }else if(chs[i] == ']'){
                    //右括号
                    i++;
                    //循环取出字符串栈顶元素，直到遇到"["
                    LinkedList<String> sub = new LinkedList<>();
                    while(list.peekLast() != "[")
                        sub.add(list.pollLast());
                    //移除 "["
                    list.pollLast();
                    StringBuilder subStr = new StringBuilder();
                    while(sub.size() > 0)
                        subStr.append(sub.pollLast());
                    //匹配整数 进行字符串拼接
                    int n = dq.pollLast();
                    StringBuilder rs = new StringBuilder();
                    for(int k = 0;k < n;k++)
                        rs.append(subStr);
                    //字符串入栈
                    list.offerLast(rs.toString());
                }
            }
            StringBuilder res = new StringBuilder();
            //最后拼接栈中字符串
            for(String str:list)
                res.append(str);
            return res.toString();
        }
    }
    public static void main(String[] args) {
//        String s = "3[a]2[bc]";
        String s = "3[a2[c]]";
//        String s = "2[abc]3[cd]ef";
//        String s = "abc3[cd]xyz";
        Solution solution = new leetcode_0394().new Solution();
        System.out.println(solution.decodeString(s));
    }
}
