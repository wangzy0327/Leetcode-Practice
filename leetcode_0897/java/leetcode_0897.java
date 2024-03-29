import java.util.*;

public class leetcode_0897 {
    public class TreeNode {
        int val;
        TreeNode left;
        TreeNode right;

        TreeNode() {
        }

        TreeNode(int val) {
            this.val = val;
        }

        TreeNode(int val, TreeNode left, TreeNode right) {
            this.val = val;
            this.left = left;
            this.right = right;
        }
    }
    class Solution {
        public TreeNode increasingBST(TreeNode root) {
            l = new LinkedList();
            inOrder(root);
            return rebuild();
        }
        private Deque<TreeNode> l;
        private void inOrder(TreeNode root){
            if(root!=null){
                inOrder(root.left);
                root.left = null;
                l.addLast(root);
                inOrder(root.right);
            }
        }
        private TreeNode rebuild(){
            TreeNode pre = null;
            TreeNode cur = null;
            TreeNode root = null;
            while(l.size()>0){
                if(root == null){
                    root = l.pollFirst();
                    pre = root;
                }else{
                    cur = l.pollFirst();
                    pre.right = cur;
                    pre = cur;
                }
            }
            if(pre != null)
                pre.right = null;
            return root;
        }
        public List<List<Integer>> levelOrder(TreeNode root) {
            List<TreeNode> cur = new ArrayList();
            List<TreeNode> next = new ArrayList();
            if (root == null)
                return new LinkedList();
            if (root != null)
                cur.add(root);
            List<List<Integer>> res = new LinkedList();
            List<Integer> curEles = new LinkedList();
            while (cur.size() > 0) {
                for (int i = 0; i < cur.size(); i++) {
                    curEles.add(cur.get(i).val);
                    if (cur.get(i).left != null)
                        next.add(cur.get(i).left);
                    if (cur.get(i).right != null)
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
            if (root == null)
                return new LinkedList();
            if (root != null)
                cur.add(root);
            List<String> res = new LinkedList();
            while (cur.size() > 0) {
                int flag = 0;
                for (int i = 0; i < cur.size(); i++) {
                    if (cur.get(i) == null) {
                        res.add("null");
                        continue;
                    } else
                        res.add(String.valueOf(cur.get(i).val));
                    TreeNode left = cur.get(i).left;
                    TreeNode right = cur.get(i).right;
                    if (left != null || right != null)
                        flag++;
                    next.add(left);
                    next.add(right);
                }
                cur = new LinkedList(next);
                if (flag == 0)
                    cur.clear();
                next.clear();
            }
            return res;
        }

        public <T> void printListArr(List<List<T>> list) {
            for (int i = 0; i < list.size(); i++) {
                if (i == list.size() - 1) {
                    if (i == 0)
                        System.out.printf("[ ");
                    System.out.println(Arrays.toString(list.get(i).toArray((T[]) new Object[0])) + " ] ");
                } else {
                    if (i == 0)
                        System.out.printf("[ ");
                    System.out.printf(Arrays.toString(list.get(i).toArray((T[]) new Object[0])) + " , ");
                }
            }
        }
    }
    public static void main(String[] args) {
        leetcode_0897.Solution solution = new leetcode_0897().new Solution();
        leetcode_0897.TreeNode root = new leetcode_0897().new TreeNode(5);
        leetcode_0897.TreeNode left = new leetcode_0897().new TreeNode(1);
        leetcode_0897.TreeNode right = new leetcode_0897().new TreeNode(7);
//        leetcode_0897.TreeNode ll = null;
//        leetcode_0897.TreeNode lr = null;
//        leetcode_0897.TreeNode rl = new leetcode_0897().new TreeNode(3);
//        leetcode_0897.TreeNode rr = new leetcode_0897().new TreeNode(6);
//        left.left = ll;
//        left.right = lr;
//        right.left = rl;
//        right.right = rr;
        root.left = left;
        root.right = right;
//        root = [2,1,3], p = 1
        List<String> rootStr = solution.levelOrderStr(root);
        System.out.println(Arrays.toString(rootStr.toArray(String[]::new)));
        //[5, 1, 7]
        TreeNode anoNode = solution.increasingBST(root);
        List<String> anoStr = solution.levelOrderStr(anoNode);
        System.out.println(Arrays.toString(anoStr.toArray(String[]::new)));
        //result
        //[1, null, 5, null, 7]
    }
}
