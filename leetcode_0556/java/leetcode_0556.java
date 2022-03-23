public class leetcode_0556 {
    public class Solution {
        public int nextGreaterElement(int n) {
            //1.从后向前遍历找到 后一个位置大于前一个位置的元素. 记录为pos 如果找不到则返回 -1(降序排列不可能有比其更大)
            //2.从后向前遍历，找到刚好大于pos的位置的值 j，然后反转两个位置元素
            //  s[pos]|...>...|s[j]|...>...|
            //3.然后反转pos后面的元素(因为j后面的元素为降序，反转后保证其为下一个更大元素)
            //并将后面的数字按照从小到大排列

            //步骤1
            StringBuilder s = new StringBuilder(Integer.toString(n));
            int pos = -1;
            for(int i = s.length() - 1;i > 0;i--){
                if(s.charAt(i) > s.charAt(i-1)){
                    pos = i - 1;
                    break;
                }
            }
            if(pos == -1)
                return -1;

            //步骤2
            for(int i = s.length() - 1;i > 0;i--){
                if(s.charAt(i) > s.charAt(pos)){
                    char tmp = s.charAt(i);
                    s.setCharAt(i,s.charAt(pos));
                    s.setCharAt(pos,tmp);
                    break;
                }
            }

            //步骤3
            reverse(s,pos+1,s.length() - 1);

            //防止int越界
            String strIntMax = Integer.toString(Integer.MAX_VALUE);
            StringBuilder anoSB = new StringBuilder(s);
            while(anoSB.length() < strIntMax.length())
                anoSB = anoSB.insert(0,"0");
            String anoStr = anoSB.toString();
            return (anoStr.compareTo(strIntMax)>0)?-1:Integer.parseInt(s.toString());
        }
        private void reverse(StringBuilder sb,int start,int end){
            while(start < end){
                char tmp = sb.charAt(start);
                sb.setCharAt(start,sb.charAt(end));
                sb.setCharAt(end,tmp);
                start++;end--;
            }
        }
    }
    public static void main(String[] args) {
        Solution solution = new leetcode_0556().new Solution();
//    int n = 21;
        //result
        //-1

            int n = 2147438647;
        //result
        //2147438674

//    int n = 2147483647;
        //result
        //-1

//    int n = 1999999999;
        //result
        // -1

//        int n = 13;
        //result
        // 31
        System.out.println(solution.nextGreaterElement(n));
    }
}
