public class leetcode_0449 {
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
        leetcode_0449.Codec codec = new leetcode_0449().new Codec();
        leetcode_0449.TreeNode root = new leetcode_0449().new TreeNode(2);
        leetcode_0449.TreeNode left = new leetcode_0449().new TreeNode(1);
        leetcode_0449.TreeNode right = new leetcode_0449().new TreeNode(3);
//        leetcode_0449.TreeNode ll = new leetcode_0449().new TreeNode(1);
//        leetcode_0449.TreeNode lr = new leetcode_0449().new TreeNode(3);
//        leetcode_0449.TreeNode rl = new leetcode_0449().new TreeNode(6);
//        leetcode_0449.TreeNode rr = new leetcode_0449().new TreeNode(9);
//        left.left = ll;
//        left.right = lr;
//        right.left = rl;
//        right.right = rr;
        root.left = left;
        root.right = right;
        codec.printTree(root);
        //[2,1,3]
        String serializeStr = codec.serialize(root);
        leetcode_0449.TreeNode ano = codec.deserialize(serializeStr);
        codec.printTree(ano);
        //result
        //[2,1,3]
    }
}
