import java.util.ArrayList;
import java.util.Arrays;
import java.util.LinkedList;
import java.util.List;
public class leetcode_1305 {
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
        public List<Integer> getAllElements(TreeNode root1, TreeNode root2) {
            //思路：1、利用中序遍历将BST的节点以从小到大顺序排列
            //2、再利用数组排序的方式排序两个列表
            List<Integer> list1 = new ArrayList();
            List<Integer> list2 = new ArrayList();
            List<Integer> res = new LinkedList();
            inOrder(root1,list1);
            inOrder(root2,list2);
            sortArrHelper(list1,list2,res);
            return res;
        }
        private void inOrder(TreeNode root,List<Integer> list){
            if(root != null){
                inOrder(root.left,list);
                list.add(root.val);
                inOrder(root.right,list);
            }
        }
        private void sortArrHelper(List<Integer> list1,List<Integer> list2,List<Integer> res){
            int idx1 = 0,idx2 = 0;
            while(idx1 < list1.size() && idx2 < list2.size()){
                if(list1.get(idx1).compareTo(list2.get(idx2)) <= 0)
                    res.add(new Integer(list1.get(idx1++)));
                else //list1.get(idx1).compareTo(list2.get(idx2)) > 0
                    res.add(new Integer(list2.get(idx2++)));
            }
            if(idx1 == list1.size()){
                while(idx2 < list2.size())
                    res.add(new Integer(list2.get(idx2++)));
            }else{
                //idx2 == list2.size()
                while(idx1 < list1.size())
                    res.add(new Integer(list1.get(idx1++)));
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
    }
    public static void main(String[] args) {
        leetcode_1305.Solution solution = new leetcode_1305().new Solution();
        leetcode_1305.TreeNode root1 = new leetcode_1305().new TreeNode(2);
        leetcode_1305.TreeNode left1 = new leetcode_1305().new TreeNode(1);
        leetcode_1305.TreeNode right1 = new leetcode_1305().new TreeNode(4);
        //root1 = [2,1,4]
        root1.left = left1;
        root1.right = right1;
        leetcode_1305.TreeNode root2 = new leetcode_1305().new TreeNode(1);
        leetcode_1305.TreeNode left2 = new leetcode_1305().new TreeNode(0);
        leetcode_1305.TreeNode right2 = new leetcode_1305().new TreeNode(3);
        //root2 = [1,0,3]
        root2.left = left2;
        root2.right = right2;
        List<String> root1Str = solution.levelOrderStr(root1);
        System.out.println(Arrays.toString(root1Str.toArray(String[]::new)));
        List<String> root2Str = solution.levelOrderStr(root2);
        System.out.println(Arrays.toString(root2Str.toArray(String[]::new)));
        List<Integer> allElements = solution.getAllElements(root1, root2);
        System.out.println(Arrays.toString(allElements.toArray((T[]) new Object[0])));
        //[0,1,1,2,3,4]
    }
}
