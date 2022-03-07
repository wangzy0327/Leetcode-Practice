public class leetcode_0387 {
    class Solution {
        public int firstUniqChar(String s) {
            int[] record = new int[26];
            char[] chs = s.toCharArray();
            int index = -1;
            for(char ch:chs)
                record[ch-'a']++;
            for(int i = 0;i < chs.length;i++)
                if(record[chs[i]-'a'] == 1)
                    return i;
            return index;
        }
    }
    public static void main(String[] args) {
        String s = "loveleetcode";
//        leetcode_0387 leetcode_0387 = ;
        int res = new leetcode_0387().new Solution().firstUniqChar(s);
        System.out.println(res);
        //result
        //2
    }
}
