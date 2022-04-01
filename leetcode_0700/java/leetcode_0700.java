import java.util.ArrayList;
import java.util.Arrays;
import java.util.LinkedList;
import java.util.List;

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
        List<String> rootStr = solution.levelOrderStr(root);
        System.out.println(Arrays.toString(rootStr.toArray(String[]::new)));
//        solution.printTree(root);
        int val = 2;
        //root = [4,2,7,1,3], val = 2
        TreeNode res = solution.searchBST(root,val);
        List<String> anoStr = solution.levelOrderStr(res);
        System.out.println(Arrays.toString(anoStr.toArray(String[]::new)));
//        solution.printTree(res);
        //[2,1,3]
    }
}
