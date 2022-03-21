public class leetcode_0567 {
    class Solution {
        public boolean checkInclusion(String s1, String s2) {
            //滑动窗口
            //哈希表来存储s1的排列
            //valid整型来计算是否满足所需要的子串字母的整型
            //由于仅存在小写字母，这里采用数组来代替哈希表
            int[] need = new int[26];
            for(char c : s1.toCharArray())
                need[c-'a']++;
            int sz = 0;
            for(int i = 0;i < need.length;i++)
                if(need[i] > 0)
                    sz++;
            int[] window = new int[26];
            int left = 0;int right = 0;
            int valid = 0;
            while(right < s2.length()){
                if(right - left < s1.length()){
                    char c = s2.charAt(right);
                    int idx = c - 'a';
                    if(need[idx] > 0){
                        window[idx]++;
                        if(window[idx] == need[idx])
                            valid++;
                    }
                    right++;
                }
                if(right - left == s1.length()){
                    if(valid == sz)
                        return true;
                    char c = s2.charAt(left);
                    int idx = c - 'a';
                    if(need[idx] > 0){
                        if(window[idx] == need[idx])
                            valid--;
                        window[idx]--;
                    }
                    left++;
                }
            }
            return false;
        }
    }
    public static void main(String[] args) {
        String s1 = "ab";
        String s2 = "eidbaooo";
        //result
        //true
//        String s1 = "ab";
//        String s2 = "eidboaoo";
        //result
        //false

        Solution solution = new leetcode_0567().new Solution();
        System.out.println(solution.checkInclusion(s1, s2));
    }
}
