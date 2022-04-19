import java.util.ArrayList;
import java.util.Arrays;
import java.util.LinkedList;
import java.util.List;

public class leetcode_1382 {
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
        public TreeNode balanceBST(TreeNode root) {
            //贪心 取中间节点为根 递归分 左右子树
            list = new ArrayList();
            inOrder(root);
            return builder(list,0,list.size()-1);
        }
        private List<TreeNode> list;
        private void inOrder(TreeNode root){
            if(root != null){
                inOrder(root.left);
                list.add(root);
                inOrder(root.right);
            }
        }
        private TreeNode builder(List<TreeNode> list,int start,int end){
            if(start > end)
                return null;
            if(start == end)
                return new TreeNode(list.get(start).val);
            int mid = start + (end - start)/2;
            int target = list.get(mid).val;
            TreeNode root = new TreeNode(target);
            root.left = builder(list,start,mid - 1);
            root.right = builder(list,mid+1,end);
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
        leetcode_1382.Solution solution = new leetcode_1382().new Solution();
        leetcode_1382.TreeNode root = new leetcode_1382().new TreeNode(1);
//        leetcode_1382.TreeNode left = null;
        leetcode_1382.TreeNode right = new leetcode_1382().new TreeNode(2);
//        leetcode_1382.TreeNode ll = new leetcode_1382().new TreeNode(3);
//        leetcode_1382.TreeNode lr = new leetcode_1382().new TreeNode(7);
//        leetcode_1382.TreeNode rl = null;
        leetcode_1382.TreeNode rr = new leetcode_1382().new TreeNode(3);
//        left.left = ll;
//        left.right = lr;
//        right.left = rl;
        right.right = rr;
//        root.left = left;
        root.right = right;
//        ll.left = new leetcode_1382().new TreeNode(0);
//        lr.left = new leetcode_1382().new TreeNode(3);
//        lr.left = new leetcode_1382().new TreeNode(5);
        rr.right = new leetcode_1382().new TreeNode(4);
        List<String> rootStr = solution.levelOrderStr(root);
        System.out.println(Arrays.toString(rootStr.toArray(String[]::new)));
        //root = [1,null,2,null,3,null,4,null,null]
        TreeNode newRoot = solution.balanceBST(root);
        List<String> newRootStr = solution.levelOrderStr(newRoot);
        System.out.println(Arrays.toString(newRootStr.toArray(String[]::new)));
        //result
        //[2,1,3,null,null,null,4]
    }
}
