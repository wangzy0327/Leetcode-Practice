public class leetcode_0226 {
    public class TreeNode{
        int val;
        TreeNode left;
        TreeNode right;
        TreeNode() {}
        TreeNode(int val) {this.val = val;}
        TreeNode(int val,TreeNode left,TreeNode right){
            this.val = val;
            this.left = left;
            this.right = right;
        }
    }
    class Solution {
        public TreeNode invertTree(TreeNode root) {
            if(root != null){
                TreeNode left = root.left;
                TreeNode right = root.right;
                root.left = invertTree(right);
                root.right = invertTree(left);
            }
            return root;
        }
        public void traversePreTree(StringBuilder sb,TreeNode root){
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
    }
    public static void main(String[] args) {
        Solution solution = new leetcode_0226().new Solution();
        TreeNode root = new leetcode_0226().new TreeNode(4);
        TreeNode left = new leetcode_0226().new TreeNode(2);
        TreeNode right = new leetcode_0226().new TreeNode(7);
        TreeNode ll = new leetcode_0226().new TreeNode(1);
        TreeNode lr = new leetcode_0226().new TreeNode(3);
        TreeNode rl = new leetcode_0226().new TreeNode(6);
        TreeNode rr = new leetcode_0226().new TreeNode(9);
        left.left = ll;
        left.right = lr;
        right.left = rl;
        right.right = rr;
        root.left = left;
        root.right = right;
        solution.printTree(root);
        //root = [4,2,7,1,3,6,9]
        root = solution.invertTree(root);
        solution.printTree(root);
        //result
        //[4,7,2,9,6,3,1]
    }
}
