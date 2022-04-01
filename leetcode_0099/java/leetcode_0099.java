import java.util.ArrayList;
import java.util.LinkedList;
import java.util.List;

public class leetcode_0099 {
    public class TreeNode{
        int val;
        TreeNode left;
        TreeNode right;
        TreeNode() {}
        TreeNode(int val) {this.val = val;}
        TreeNode(int val, TreeNode left, TreeNode right){
            this.val = val;
            this.left = left;
            this.right = right;
        }
    }
    class Solution {
        public void recoverTree(TreeNode root) {
            //考察中序遍历
            //一个正常的BST会是递增序列，如果错误的交换两个节点，则会出现递减
            //这里的递减分为两个情况，一个是交换的是相邻元素（只会有一个递减）
            //ep:1,2,3,4,5,6,7 -> 1,3,2,4,5,6,7
            //交换的是非相邻元素(两个递减)
            //ep:1,2,3,4,5,6,7 -> 1,6,3,4,5,2,7
            //可通过这个找到两个交换的元素 
            //然后重新遍历树，对两个元素的值进行 交换
            //错误交换的值

            int[] nums = new int[]{-1,-1};
            pre = null;
            inorder(root,nums);
            recover(root,nums);
        }
        //用来标识是否是第一次遇到递减
        private Integer flag = -1;
        private TreeNode pre = null;
        private void inorder(TreeNode root,int[] nums){
            if(root != null){
                inorder(root.left,nums);
                if(pre != null && pre.val > root.val && flag.equals(-1)){
                    nums[0] = pre.val;
                    nums[1] = root.val;
                    flag = 0;
                }else if(pre != null && pre.val > root.val && !flag.equals(-1)){
                    nums[1] = root.val;
                }
                pre = root;
                inorder(root.right,nums);
            }
        }
        private void recover(TreeNode root,int[] nums){
            if(root != null){
                recover(root.left,nums);
                if(root.val == nums[0]){
                    root.val = nums[1];
                }else if(root.val == nums[1]){
                    root.val = nums[0];
                }
                recover(root.right,nums);
            }
        }

        public void traversePreTree(StringBuilder sb, leetcode_0099.TreeNode root){
            if(root != null){
                sb.append(root.val+",");
                traversePreTree(sb,root.left);
                traversePreTree(sb,root.right);
            }
        }
        public void printTree(TreeNode root){
            StringBuilder res = new StringBuilder();
            traversePreTree(res,root);
            System.out.printf("[");
            String substring = res.substring(0, res.length() - 1);
            System.out.printf(substring);
            System.out.println("]");
        }

        public List<List<Integer>> levelOrder(TreeNode root) {
            List<TreeNode> cur = new ArrayList();
            List<TreeNode> next = new ArrayList();
            if(root == null)
                return new LinkedList();
            if(root != null)
                cur.add(root);
            List<List<Integer>> res = new LinkedList();
            List<Integer> curEles  = new LinkedList();
            while(cur.size() > 0){
                for(int i = 0;i < cur.size();i++){
                    curEles.add(cur.get(i).val);
                    if(cur.get(i).left != null)
                        next.add(cur.get(i).left);
                    if(cur.get(i).right != null)
                        next.add(cur.get(i).right);
                }
                res.add(new LinkedList(curEles));
                cur = new LinkedList(next);
                curEles.clear();
                next.clear();
            }
            return res;
        }
        public List<String> levelOrderStr(TreeNode root) {
            List<TreeNode> cur = new ArrayList();
            List<TreeNode> next = new ArrayList();
            if(root == null)
                return new LinkedList();
            if(root != null)
                cur.add(root);
            List<String> res = new LinkedList();
            while(cur.size() > 0){
                int flag = 0;
                for(int i = 0;i < cur.size();i++){
                    if(cur.get(i) == null){
                        res.add("null");
                        continue;
                    }
                    else
                        res.add(String.valueOf(cur.get(i).val));
                    TreeNode left = cur.get(i).left;
                    TreeNode right = cur.get(i).right;
                    if(left != null || right != null)
                        flag++;
                    next.add(left);
                    next.add(right);
                }
                cur = new LinkedList(next);
                if(flag == 0)
                    cur.clear();
                next.clear();
            }
            return res;
        }

    }
    public static void main(String[] args) {
        leetcode_0099.Solution solution = new leetcode_0099().new Solution();
        leetcode_0099.TreeNode root = new leetcode_0099().new TreeNode(1);
        leetcode_0099.TreeNode left = new leetcode_0099().new TreeNode(3);
        leetcode_0099.TreeNode right = null;
        leetcode_0099.TreeNode ll = null;
        leetcode_0099.TreeNode lr = new leetcode_0099().new TreeNode(2);
//        leetcode_0099.TreeNode rl = null;
//        leetcode_0099.TreeNode rr = new leetcode_0099().new TreeNode(7);
        left.left = ll;
        left.right = lr;
//        right.left = rl;
//        right.right = rr;
        root.left = left;
        root.right = right;
        solution.printTree(root);
        //root = [1,3,null,null,2]
        solution.recoverTree(root);
        solution.printTree(root);
        //[3,1,null,null,2]
    }
}
