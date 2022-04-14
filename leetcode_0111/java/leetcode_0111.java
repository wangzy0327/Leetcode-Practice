import java.util.*;

public class leetcode_0111 {
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
        public int minDepth(TreeNode root) {
            //这里找寻左右子树中最小的深度返回,注意 如果 左右子树有一个为null,则返回另一个子树深度+1
            //两种方式求解，一种递归 DFS
            //一种 BFS(更快) BFS 对求解最短路径和最小深度有优势
            if(root == null)
                return 0;
            //这里采用双端队列
            Deque<TreeNode> dq = new LinkedList();
            depth = 0;
            dq.offerLast(root);
            int res = bfs(dq);
            return res;
        }
        private int depth;
        private int bfs(Deque<TreeNode> dq){
            while(dq.size() > 0){
                int sz = dq.size();
                for(int i = 0;i < sz;i++){
                    TreeNode cur = dq.pollFirst();
                    //如果左右子树均为null，说明遇到叶子结点，返回depth+1
                    if(cur.left == null && cur.right == null)
                        return depth + 1;
                    if(cur.left != null)
                        dq.offerLast(cur.left);
                    if(cur.right != null)
                        dq.offerLast(cur.right);
                }
                //当前层遍历完深度+1
                depth += 1;
            }
            return depth;
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
        leetcode_0111.Solution solution = new leetcode_0111().new Solution();
        leetcode_0111.TreeNode root = new leetcode_0111().new TreeNode(2);
//        leetcode_0111.TreeNode left = new leetcode_0111().new TreeNode(9);
        leetcode_0111.TreeNode right = new leetcode_0111().new TreeNode(3);
//        leetcode_0111.TreeNode ll = null;
//        leetcode_0111.TreeNode lr = null;
        leetcode_0111.TreeNode rl = null;
        leetcode_0111.TreeNode rr = new leetcode_0111().new TreeNode(4);
        leetcode_0111.TreeNode rrr = new leetcode_0111().new TreeNode(5);
//        left.left = ll;
//        left.right = lr;
        right.left = rl;
        right.right = rr;
//        root.left = left;
        root.right = right;
        rr.right = rrr;
        rrr.right = new leetcode_0111().new TreeNode(6);
//        ll.left = new leetcode_0111().new TreeNode(0);
//        lr.left = new leetcode_0111().new TreeNode(3);
//        lr.left = new leetcode_0111().new TreeNode(7);
//        lr.right = new leetcode_0111().new TreeNode(4);
        List<String> rootStr = solution.levelOrderStr(root);
        System.out.println(Arrays.toString(rootStr.toArray(String[]::new)));
        int res = solution.minDepth(root);
        System.out.println(res);
        //result
        //5
    }
}
