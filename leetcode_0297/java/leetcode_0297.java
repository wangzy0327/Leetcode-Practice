import java.util.ArrayList;
import java.util.Arrays;
import java.util.LinkedList;
import java.util.List;

public class leetcode_0297 {
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
    public class Codec {
        // Encodes a tree to a single string.
        public String serialize(TreeNode root) {
            if(root == null)
                return "#";
            StringBuilder sb = new StringBuilder();
            sb.append(root.val);
            sb.append(" ");
            sb.append(serialize(root.left));
            sb.append(" ");
            sb.append(serialize(root.right));
            return sb.toString();
        }

        // Decodes your encoded data to tree.
        public TreeNode deserialize(String data) {
            String[] splits = data.split(" ");
            index = 0;
            TreeNode root = rebuild(splits);
            return root;
        }
        private int index = 0;
        private TreeNode rebuild(String[] splits){
            if(index >= splits.length)
                return null;
            if(splits[index].equals("#")){
                index+=1;
                return null;
            }
            TreeNode node = new TreeNode(Integer.parseInt(splits[index++]));
            node.left = rebuild(splits);
            node.right = rebuild(splits);
            return node;
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
    }
    public static void main(String[] args) {
        Codec codec = new leetcode_0297().new Codec();
        leetcode_0297.TreeNode root = new leetcode_0297().new TreeNode(1);
        leetcode_0297.TreeNode left = new leetcode_0297().new TreeNode(2);
        leetcode_0297.TreeNode right = new leetcode_0297().new TreeNode(3);
//        leetcode_0297.TreeNode ll = new leetcode_0297().new TreeNode(1);
//        leetcode_0297.TreeNode lr = new leetcode_0297().new TreeNode(3);
        leetcode_0297.TreeNode rl = new leetcode_0297().new TreeNode(4);
        leetcode_0297.TreeNode rr = new leetcode_0297().new TreeNode(5);
//        left.left = ll;
//        left.right = lr;
        right.left = rl;
        right.right = rr;
        root.left = left;
        root.right = right;
        List<String> rootStr = codec.levelOrderStr(root);
        System.out.println(Arrays.toString(rootStr.toArray(String[]::new)));
//        codec.printTree(root);
        //[1,2,3,null,null,4,5]
        String serializeStr = codec.serialize(root);
        TreeNode ano = codec.deserialize(serializeStr);
        List<String> anoStr = codec.levelOrderStr(ano);
        System.out.println(Arrays.toString(anoStr.toArray(String[]::new)));
        //result
        //[1,2,3,null,null,4,5]
    }
}
