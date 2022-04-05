import java.util.ArrayList;
import java.util.Arrays;
import java.util.LinkedList;
import java.util.List;
public class interview_0406 {
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
        public TreeNode inorderSuccessor(TreeNode root, TreeNode p) {
            //思路：记录前一个节点，如果前一个节点就是制定的节点
            //则返回当前节点
            pre = null;
            return finder(root,p);
        }
        private TreeNode pre;
        private TreeNode finder(TreeNode root,TreeNode p){
            if(root != null){
                TreeNode lNode = finder(root.left,p);
                if(lNode != null)
                    return lNode;
                if(pre == null)
                    pre = root;
                else if(pre == p)
                    return root;
                else if(pre != p)
                    pre = root;
                TreeNode rNode = finder(root.right,p);
                if(rNode != null)
                    return rNode;
            }
            return null;
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
                    System.out.println(Arrays.toString(list.get(i).toArray(Integer[]::new)) + " ] ");
                } else {
                    if (i == 0)
                        System.out.printf("[ ");
                    System.out.printf(Arrays.toString(list.get(i).toArray(Integer[]::new)) + " , ");
                }
            }
        }
    }

    public static void main(String[] args) {
        interview_0406.Solution solution = new interview_0406().new Solution();
        interview_0406.TreeNode root = new interview_0406().new TreeNode(2);
        interview_0406.TreeNode left = new interview_0406().new TreeNode(1);
        interview_0406.TreeNode right = new interview_0406().new TreeNode(3);
//        interview_0406.TreeNode ll = null;
//        interview_0406.TreeNode lr = null;
//        interview_0406.TreeNode rl = new interview_0406().new TreeNode(3);
//        interview_0406.TreeNode rr = new interview_0406().new TreeNode(6);
//        left.left = ll;
//        left.right = lr;
//        right.left = rl;
//        right.right = rr;
        root.left = left;
        root.right = right;
//        root = [2,1,3], p = 1
        List<String> rootStr = solution.levelOrderStr(root);
        System.out.println(Arrays.toString(rootStr.toArray(String[]::new)));
        TreeNode nextNode = solution.inorderSuccessor(root, left);
        System.out.println(nextNode.val);
        //result
        //2
    }
}
