import java.util.HashSet;
import java.util.Set;

public class leetcode_0653 {
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
        public boolean findTarget(TreeNode root, int k) {
            Set<Integer> s = new HashSet();
            return findHelper(root,k,s);
        }
        private boolean findHelper(TreeNode root,int k,Set<Integer> s){
            if(root != null){
                if(s.contains(k-root.val))
                    return true;
                s.add(root.val);
                return findHelper(root.left,k,s) || findHelper(root.right,k,s);
            }
            return false;
        }
        public void traversePreTree(StringBuilder sb, TreeNode root){
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
        leetcode_0653.Solution solution = new leetcode_0653().new Solution();
        leetcode_0653.TreeNode root = new leetcode_0653().new TreeNode(5);
        leetcode_0653.TreeNode left = new leetcode_0653().new TreeNode(3);
        leetcode_0653.TreeNode right = new leetcode_0653().new TreeNode(6);
        leetcode_0653.TreeNode ll = new leetcode_0653().new TreeNode(2);
        leetcode_0653.TreeNode lr = new leetcode_0653().new TreeNode(4);
        leetcode_0653.TreeNode rl = null;
        leetcode_0653.TreeNode rr = new leetcode_0653().new TreeNode(7);
        left.left = ll;
        left.right = lr;
        right.left = rl;
        right.right = rr;
        root.left = left;
        root.right = right;
        solution.printTree(root);
//        root = [5,3,6,2,4,null,7], k = 9
        int k = 9;
        boolean res = solution.findTarget(root, k);
        System.out.println(res);
        //result
        //true
    }

}
