public class leetcode_0154 {
    /**
     * 思路：
     * 二分查找法的要求：
     * 1、顺序存储
     * 2、元素有序
     *
     * 原因：
     * 1、通过下标即可得到关键字
     * 2、任取一个关键字的值即可确定所寻找关键字是在它前面还是后面
     *
     * 由于旋转排序数组，可以转化为对两个顺序数组(如果旋转正好一个周期，则为一个顺序数组)的分界点的寻找
     * ep:[4,4,1,2,2]
     * 因为既有可能是一个顺序数组也有可能是两个顺序数组。则可以将共同点转化为寻找后一个有序数组的最小值
     *
     * 要找到一种判断方法来判定 最小值在哪一侧，如果找到就可以通过二分法来解决问题
     *
     *  当没有重复元素时，比较当前元素是否比最右边元素大,如果大则可以确定最小值在右半边
     *    numbers[mid] > numbers[right]
     *  如果当前元素比最右边元素小，则说明右侧半边数组为递增数组。反转元素应该在最左端（不管是否是一个顺序数组还是两个顺序数组都满足）
     *    numbers[mid] < numbers[right]
     *  反过来，如果numbers[mid] 跟 numbers[left] 元素比较则无法判断截断的是一边是否含有最小元素 如下示例
     *  ep:[4,4,4,5,1,2]
     *     [1,2,4,4,4,5]
     *  所以不能根据比较 最左端元素的值进行判断
     *
     *  当存在重复元素时，无法判断最小值在哪一侧
     *      numbers[mid] == numbers[right]
     *  ep: [4,4,1,4] 最小值在右侧
     *      [1,4,4,4] 最小值在左侧
     *   在这种情况下，由于right索引对应的值与mid索引对应的值相同，可以通过缩减right右侧的范围来继续寻找最小值
     *   即 right--;
     *
     *
     */
    class Solution {
        public int findMin(int[] nums) {
            int left = 0;
            int right = nums.length - 1;
            int mid = 0;
            while(left < right){
                mid = left + (right - left)/2;
                if(nums[mid] < nums[right])
                    right = mid;
                else if(nums[mid] > nums[right])
                    left = mid + 1;
                else if(nums[mid] == nums[right])
                    right--;
            }
            return nums[left];
        }
    }
    public static void main(String[] args) {
        Solution solution = new leetcode_0154().new Solution();
//        int[] nums = new int[]{2,2,2,0,1};
//        int[] nums = new int[]{1,3,5};
        int[] nums = new int[]{3,3,1,3};
        System.out.println(solution.findMin(nums));
    }
}
