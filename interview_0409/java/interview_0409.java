import java.util.ArrayList;
import java.util.Arrays;
import java.util.LinkedList;
import java.util.List;

public class interview_0409 {
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
        public List<List<Integer>> BSTSequences(TreeNode root) {
            //输出所有可能的组合 可以想到用回溯来解决问题
            //组合的特殊性，首选需要保证根节点先入数组，然后才是左右子树
            //该组合的特性满足 层次遍历
            //回溯的结束条件是 数组path为空
            if(root == null)
                return new LinkedList<List<Integer>>(){{add(new LinkedList());}};
            List<List<Integer>> res = new LinkedList<List<Integer>>();
            List<TreeNode> path = new ArrayList();
            List<Integer> sub = new LinkedList();
            path.add(root);
            dfs(res,path,sub);
            return res;
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
        private void dfs(List<List<Integer>> res,List<TreeNode> path,List<Integer> sub){
            if(path.size() == 0){
                res.add(new LinkedList(sub));
                return ;
            }
            for(int i = 0;i < path.size();i++){
                TreeNode cur = path.get(i);
                path.remove(i);
                sub.add(cur.val);
                if(cur.left != null)
                    path.add(cur.left);
                if(cur.right != null)
                    path.add(cur.right);
                dfs(res,path,sub);
                //恢复状态
                if(cur.left != null)
                    path.remove(path.size()-1);
                if(cur.right != null)
                    path.remove(path.size()-1);
                sub.remove(sub.size()-1);
                path.add(i,cur);
            }
        }
    }
    public static void main(String[] args) {
        interview_0409.Solution solution = new interview_0409().new Solution();
        interview_0409.TreeNode root = new interview_0409().new TreeNode(2);
        interview_0409.TreeNode left = new interview_0409().new TreeNode(1);
        interview_0409.TreeNode right = new interview_0409().new TreeNode(3);
//        interview_0409.TreeNode ll = new interview_0409().new TreeNode(1);
//        interview_0409.TreeNode lr = new interview_0409().new TreeNode(3);
//        interview_0409.TreeNode rl = null;
//        interview_0409.TreeNode rr = new interview_0409().new TreeNode(6);
//        left.left = ll;
//        left.right = lr;
//        right.left = rl;
//        right.right = rr;
        root.left = left;
        root.right = right;
//        ll.left = new interview_0409().new TreeNode(0);
//        lr.left = new interview_0409().new TreeNode(3);
//        lr.left = new interview_0409().new TreeNode(5);
        List<String> rootStr = solution.levelOrderStr(root);
        System.out.println(Arrays.toString(rootStr.toArray(String[]::new)));
        //[2, 1, 3]
        List<List<Integer>> lists = solution.BSTSequences(root);
        solution.printListArr(lists);
        //[ [2, 1, 3] , [2, 3, 1] ]
    }
}
