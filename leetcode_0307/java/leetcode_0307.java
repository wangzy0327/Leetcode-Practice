public class leetcode_0307 {
    class NumArray {

        public NumArray(int[] nums) {
            //思路：采用线段树来降低对元素的更新时间复杂度(Ologn)(注意线段树不一定是完全二叉树)
        /*
                           [0...9]
                  [0...4]          [5...9]
            [0...2]  [3...4]     [5...7]    [8...9]
       [0...1] [2]   [3]  [4]  [5...6] [7] [8]    [9]
       [0] [1]                 [5] [6]
        */
            //如图可知：叶子结点在最差的情况下占据下面两层
            // n = 2^k   最多 2*n就够
            // n = 2^k+1  最多需要 4*n 就够
            n = nums.length;
            segementTree = new int[4*n];
            builder(nums,0,0,n-1);
        }

        public void update(int index, int val) {
            change(index,val,0,0,n-1);
        }

        public int sumRange(int left, int right) {
            return sumRangeHelper(left,right,0,0,n-1);
        }
        private int[] segementTree;
        private int n;
        private void builder(int[] nums,int treeIdx,int start,int end){
            //分为两种情况  叶子节点和非叶子节点
            //叶子节点
            if(start == end){
                segementTree[treeIdx] = nums[start];
                return ;
            }
            int mid = start + (end - start)/2;
            int leftIdx = 2*treeIdx+1;
            int rightIdx = 2*treeIdx+2;
            builder(nums,leftIdx,start,mid);
            builder(nums,rightIdx,mid+1,end);
            segementTree[treeIdx] = segementTree[leftIdx] + segementTree[rightIdx];
        }
        private void change(int index,int val,int treeIdx,int start,int end){
            //找到指定节点
            if(start == end){
                segementTree[treeIdx] = val;
                return ;
            }
            int mid = start + (end - start)/2;
            int leftIdx = 2*treeIdx + 1;
            int rightIdx = 2*treeIdx + 2;
            //如果寻找索引在mid左侧,则 在左半侧线段子树寻找
            if(index <= mid){
                change(index,val,leftIdx,start,mid);
            }else{
                change(index,val,rightIdx,mid+1,end);
            }
            //修改节点返回后依次更新 根节点
            segementTree[treeIdx] = segementTree[leftIdx] + segementTree[rightIdx];
        }
        private int sumRangeHelper(int left,int right,int treeIdx,int start,int end){
            if(left == start && right == end){
                return segementTree[treeIdx];
            }
            int mid = start + (end - start)/2;
            int leftIdx = treeIdx * 2 + 1;
            int rightIdx = treeIdx * 2 + 2;
            //分线段区间 切分情况
            if(right <= mid ){
                //寻找区间在左边
                return sumRangeHelper(left,right,leftIdx,start,mid);
            }else if(left > mid){
                //寻找区间在右边
                return sumRangeHelper(left,right,rightIdx,mid+1,end);
            }else{
                //寻找区间两边都有
                return sumRangeHelper(left,mid,leftIdx,start,mid) + sumRangeHelper(mid+1,right,rightIdx,mid+1,end);
            }
        }
    }

    /**
     * Your NumArray object will be instantiated and called as such:
     * NumArray obj = new NumArray(nums);
     * obj.update(index,val);
     * int param_2 = obj.sumRange(left,right);
     */
    public static void main(String[] args) {
        int[] nums = {1,3,5};
        leetcode_0307.NumArray numArray = new leetcode_0307().new NumArray(nums);
        //NumArray numArray = new NumArray([1, 3, 5]);
        numArray.sumRange(0,2);
        //numArray.sumRange(0, 2); // 返回 1 + 3 + 5 = 9
        //result
        //9
        numArray.update(1,2);
        //numArray.update(1, 2);   // nums = [1,2,5]
        numArray.sumRange(0,2);
        //numArray.sumRange(0, 2); // 返回 1 + 2 + 5 = 8
        //result
        //8
    }
}
