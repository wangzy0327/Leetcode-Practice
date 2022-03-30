public class leetcode_0700 {
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
        public TreeNode searchBST(TreeNode root, int val) {
            if(root != null){
                if(val == root.val)
                    return root;
                else if(val < root.val)
                    return searchBST(root.left,val);
                else if(val > root.val)
                    return searchBST(root.right,val);
            }
            return null;
        }
        public void traversePreTree(StringBuilder sb, leetcode_0700.TreeNode root){
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
        leetcode_0700.Solution solution = new leetcode_0700().new Solution();
        leetcode_0700.TreeNode root = new leetcode_0700().new TreeNode(4);
        leetcode_0700.TreeNode left = new leetcode_0700().new TreeNode(2);
        leetcode_0700.TreeNode right = new leetcode_0700().new TreeNode(7);
        leetcode_0700.TreeNode ll = new leetcode_0700().new TreeNode(1);
        leetcode_0700.TreeNode lr = new leetcode_0700().new TreeNode(3);
        left.left = ll;
        left.right = lr;
//        right.left = rl;
//        right.right = rr;
        root.left = left;
        root.right = right;
        solution.printTree(root);
        int val = 2;
        //root = [4,2,7,1,3], val = 2
        TreeNode res = solution.searchBST(root,val);
        solution.printTree(res);
        //[2,1,3]
    }
}
