import java.util.HashSet;
import java.util.LinkedList;
import java.util.Set;

public class leetcode_0773 {
    class Solution {
        public int slidingPuzzle(int[][] board) {
            //最少移动次数
            //最小深度    最小旋转 可以联想到BFS来解决
            // target = [[1,2,3],[4,5,0]]
            //设置一个遍历过的 无重复集合 来去重走过的路
            //队列用来存放每次BFS的所有可能结果
            String target_s = new String("123450");
            StringBuilder board_sb = new StringBuilder();
            for(int i = 0;i < board.length;i++)
                for(int j = 0;j < board[i].length;j++)
                    board_sb.append(board[i][j]);
            if(target_s.equals(board_sb.toString()))
                return 0;
            LinkedList<String> queue = new LinkedList();
            queue.offerLast(board_sb.toString());
            move = 0;
            Set<String> visited = new HashSet();
            bfs(queue,visited,target_s);
            return move;
        }
        private int move;
        private void bfs(LinkedList<String> queue,Set<String> visited,String target){
            while(queue.size() > 0){
                int sz = queue.size();
                for(int i = 0;i < sz;i++){
                    String board = queue.pollFirst();
                    if(board.equals(target))
                        return ;
                    else{
                        //计算 变换后的谜板
                        LinkedList<String> vec = nextVec(board,visited);
                        while(vec.size() > 0)
                            queue.offerLast(vec.pollFirst());
                        visited.add(board);
                    }
                }
                move += 1;
            }
            //队列为空 不可达
            move = -1;
        }
        private LinkedList<String> nextVec(String board, Set<String> visited){
            LinkedList<String> res = new LinkedList();
            char[] temp = board.toCharArray();
            int idx_x = 0;int idx_y = 0;
            int m = 2;int n = 3;
            int i = 0;
            for(;i < board.length() ;i++)
                if(board.charAt(i) == '0')
                    break;
            idx_x = i/n;idx_y = i%n;
            //向上向下向左向右判断
            if(idx_x > 0){
                swap(temp,i,(idx_x-1)*n+idx_y);
                if(!visited.contains(new String(temp)))
                    res.add(new String(temp));
                temp = board.toCharArray();
            }
            if(idx_x < m - 1){
                swap(temp,i,(idx_x+1)*n+idx_y);
                if(!visited.contains(new String(temp)))
                    res.add(new String(temp));
                temp = board.toCharArray();
            }
            if(idx_y > 0){
                swap(temp,i,idx_x*n+idx_y - 1);
                if(!visited.contains(new String(temp)))
                    res.add(new String(temp));
                temp = board.toCharArray();
            }
            if(idx_y < n - 1){
                swap(temp,i,idx_x*n+idx_y + 1);
                if(!visited.contains(new String(temp)))
                    res.add(new String(temp));
                temp = board.toCharArray();
            }
            return res;
        }
        private void swap(char[] temp,int x,int y){
            char tmp = temp[x];
            temp[x] = temp[y];
            temp[y] = tmp;
        }
    }
    public static void main(String[] args) {
        leetcode_0773.Solution solution = new leetcode_0773().new Solution();
        int[][] board = {{1,2,3},{4,0,5}};
        //board = [[1,2,3],[4,0,5]]
        int res = solution.slidingPuzzle(board);
        System.out.println(res);
        //result
        //1
        //交换 0 和 5 ，1 步完成
    }
}
