public class Solution {
    // you need to treat n as an unsigned value
    public int hammingWeight(int n) {
		int count = 0;
        int flag = 1;
        while(flag != 0 ){
            if((n & flag) != 0)
                count++;
            flag = flag << 1;
        }
        return count;
    }
	//右移传入参数有一个好处，如果左边为0就不用继续左移了
    public int hammingWeight2(int n) {
        int count = 0;
        int flag = 1;
        while(n != 0 ){
            if((n & flag) != 0)
                count++;
            n = n >>> 1;
        }
        return count;
    }

    public static void main(String[] args) {
        System.out.println(new Solution().hammingWeight(11));
        System.out.println(new Solution().hammingWeight(128));
        System.out.println(new Solution().hammingWeight(4294967293));
    }
}