import java.util.ArrayList;
import java.util.Arrays;
import java.util.LinkedList;
import java.util.List;

public class leetcode_0102 {
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
        public <T> void printListArr(List<List<T>> list){
            for(int i = 0;i < list.size();i++){
                if(i == list.size() - 1){
                    if(i == 0)
                        System.out.printf("[ ");
                    System.out.println(Arrays.toString(list.get(i).toArray((T[]) new Object[0]))+" ] ");
                }else{
                    if(i == 0)
                        System.out.printf("[ ");
                    System.out.printf(Arrays.toString(list.get(i).toArray((T[]) new Object[0]))+" , ");
                }
            }
        }
    }
    public static void main(String[] args) {
        leetcode_0102.Solution solution = new leetcode_0102().new Solution();
        leetcode_0102.TreeNode root = new leetcode_0102().new TreeNode(3);
        leetcode_0102.TreeNode left = new leetcode_0102().new TreeNode(9);
        leetcode_0102.TreeNode right = new leetcode_0102().new TreeNode(20);
        leetcode_0102.TreeNode ll = null;
        leetcode_0102.TreeNode lr = null;
        leetcode_0102.TreeNode rl = new leetcode_0102().new TreeNode(15);
        leetcode_0102.TreeNode rr = new leetcode_0102().new TreeNode(7);
        left.left = ll;
        left.right = lr;
        right.left = rl;
        right.right = rr;
        root.left = left;
        root.right = right;
        List<String> rootStr = solution.levelOrderStr(root);
        System.out.println(Arrays.toString(rootStr.toArray(String[]::new)));
        List<List<Integer>> lists = solution.levelOrder(root);
//        [3,9,20,null,null,15,7]
        solution.printListArr(lists);
        //result [[3],[9,20],[15,7]]
    }
}
