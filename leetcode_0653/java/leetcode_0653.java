import java.util.*;

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
//        solution.printTree(root);
        List<String> rootStr = solution.levelOrderStr(root);
        System.out.println(Arrays.toString(rootStr.toArray(String[]::new)));
//        root = [5,3,6,2,4,null,7], k = 9
        int k = 9;
        boolean res = solution.findTarget(root, k);
        System.out.println(res);
        //result
        //true
    }

}
