import java.util.*;
public class offer_1_0054 {
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
        public int kthLargest(TreeNode root, int k) {
            //求最大的k个节点 采用先右根左的顺序 保证从大到小
            target = 0;
            TreeNode targetNode = findKthLarge(root,k);
            if(targetNode == null)
                return Integer.MIN_VALUE;
            return targetNode.val;
        }
        private int target;
        private TreeNode findKthLarge(TreeNode root,int k){
            if(root != null){
                TreeNode rNode = findKthLarge(root.right,k);
                if(rNode != null)
                    return rNode;
                target++;
                if(k == target)
                    return root;
                TreeNode lNode = findKthLarge(root.left,k);
                if(lNode != null)
                    return lNode;
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
        offer_1_0054.Solution solution = new offer_1_0054().new Solution();
        offer_1_0054.TreeNode root = new offer_1_0054().new TreeNode(3);
        offer_1_0054.TreeNode left = new offer_1_0054().new TreeNode(1);
        offer_1_0054.TreeNode right = new offer_1_0054().new TreeNode(4);
//        offer_1_0054.TreeNode ll = null;
        offer_1_0054.TreeNode lr = new offer_1_0054().new TreeNode(2);
//        offer_1_0054.TreeNode rl = new offer_1_0054().new TreeNode(3);
//        offer_1_0054.TreeNode rr = new offer_1_0054().new TreeNode(6);
//        left.left = ll;
        left.right = lr;
//        right.left = rl;
//        right.right = rr;
        root.left = left;
        root.right = right;
//        root = [2,1,3], p = 1
        List<String> rootStr = solution.levelOrderStr(root);
        System.out.println(Arrays.toString(rootStr.toArray(String[]::new)));
        //root = [3,1,4,null,2], k = 1
        int k = 1;
        int res = solution.kthLargest(root,k);
        System.out.println(res);
        //result
        //4
    }
}
