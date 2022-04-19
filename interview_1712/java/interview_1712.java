import java.util.ArrayList;
import java.util.Arrays;
import java.util.LinkedList;
import java.util.List;
public class interview_1712 {
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
        public TreeNode convertBiNode(TreeNode root) {
            //按照BST中序遍历，保证从小到大顺序,保存pre前一个节点,来改动链表
            pre = null;
            head = null;
            inOrderHelper(root);
            return head;
        }
        private TreeNode head;
        private TreeNode pre;
        private void inOrderHelper(TreeNode root){
            if(root != null){
                inOrderHelper(root.left);
                if(pre == null){
                    pre = root;
                    head = root;
                }else{
                    pre.right = root;
                    //注意将root的左边节点置为null
                    root.left = null;
                    pre = root;
                }
                inOrderHelper(root.right);
            }
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
        public void printDoublyList(TreeNode head){
            TreeNode cur = head;
            if(cur == null){
                System.out.println("[]");
                return ;
            }
            System.out.printf("[");
            while(cur.right != null){
                System.out.printf("%d,",cur.val);
                if(cur.left != null)
                    cur = cur.left;
                else
                    System.out.printf("null,");
                cur = cur.right;
            }
            System.out.println(cur.val+"]");
        }
    }
    public static void main(String[] args) {
        interview_1712.Solution solution = new interview_1712().new Solution();
        interview_1712.TreeNode root = new interview_1712().new TreeNode(4);
        interview_1712.TreeNode left = new interview_1712().new TreeNode(2);
        interview_1712.TreeNode right = new interview_1712().new TreeNode(5);
        interview_1712.TreeNode ll = new interview_1712().new TreeNode(1);
        interview_1712.TreeNode lr = new interview_1712().new TreeNode(3);
        interview_1712.TreeNode rl = null;
        interview_1712.TreeNode rr = new interview_1712().new TreeNode(6);
        left.left = ll;
        left.right = lr;
        right.left = rl;
        right.right = rr;
        root.left = left;
        root.right = right;
        ll.left = new interview_1712().new TreeNode(0);
//        lr.left = new interview_1712().new TreeNode(3);
//        lr.left = new interview_1712().new TreeNode(5);
        List<String> rootStr = solution.levelOrderStr(root);
        System.out.println(Arrays.toString(rootStr.toArray(String[]::new)));
        //[4,2,5,1,3,null,6,0]
        //[4, 2, 5, 1, 3, null, 6, 0, null, null, null, null, null]
        TreeNode head = solution.convertBiNode(root);
        solution.printDoublyList(head);
        //[0,null,1,null,2,null,3,null,4,null,5,null,6]
    }
}
