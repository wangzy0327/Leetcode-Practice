import java.util.Arrays;
import java.util.List;

public class leetcode_0037 {
    class Solution {
        public void solveSudoku(char[][] board) {
            //思路：回溯
            //每个进入到每个需要填充的位置是需要传入i,j来进行定位
            //如果dfs找到了返回true,不需要返回重置，否则如果为false，重置接着找下一个满足的
            dfs(board,0,0);
        }
        private boolean dfs(char[][] board,int idxX,int idxY){
            //超过边界值 说明找到了 返回true
            if(idxX >= board.length || idxY >= board[idxX].length)
                return true;
            int[] pos = nextPos(board,idxX,idxY);
            if(board[idxX][idxY] == '.'){
                for(int i = 1;i <= 9;i++){
                    char ch = (char)('0'+i);
                    if(valid(board,idxX,idxY,ch)){
                        board[idxX][idxY] = ch;
                        //如果不满足回溯重置 接着找
                        if(!dfs(board,idxX,idxY))
                            board[idxX][idxY] = '.';
                    }
                }
                //如果1-9都不满足 则 返回false
                if(board[idxX][idxY] == '.')
                    return false;
            }else{
                return dfs(board,pos[0],pos[1]);
            }
            return true;
        }
        private boolean valid(char[][] board,int idxX,int idxY,char ch){
            //判断行
            for(int i = 0;i < board.length;i++)
                if(board[i][idxY] == ch)
                    return false;
            //判断列
            for(int i = 0;i < board[idxX].length;i++)
                if(board[idxX][i] == ch)
                    return false;
            //判断宫格
            //求宫格左上角索引
            int leftX = (idxX/3)*3;
            int leftY = (idxY/3)*3;
            for(int i = leftX;i < leftX + 3;i++)
                for(int j = leftY;j < leftY + 3;j++)
                    if(board[i][j] == ch)
                        return false;
            return true;
        }
        private int[] nextPos(char[][] board,int idxX,int idxY){
            int i = idxX;int j = idxY;
            for(;i < board.length;i++){
                for(;j < board[i].length;j++){
                    if(board[i][j] == '.')
                        return new int[]{i,j};
                }
                //寻找下一个元素时换行需要将列索引置为0
                j = 0;
            }
            return new int[]{i,j};
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
        leetcode_0037.Solution solution = new leetcode_0037().new Solution();
        char[][] board = {
                {'5','3','.','.','7','.','.','.','.'},
                {'6','.','.','1','9','5','.','.','.'},
                {'.','9','8','.','.','.','.','6','.'},
                {'8','.','.','.','6','.','.','.','3'},
                {'4','.','.','8','.','3','.','.','1'},
                {'7','.','.','.','2','.','.','.','6'},
                {'.','6','.','.','.','.','2','8','.'},
                {'.','.','.','4','1','9','.','.','5'},
                {'.','.','.','.','8','.','.','7','9'}
        };
        solution.solveSudoku(board);
        for(int i = 0;i < board.length;i++)
            System.out.println(Arrays.toString(board[i]));
        //result
        /**
         * [5, 3, 4, 6, 7, 8, 9, 1, 2]
         * [6, 7, 2, 1, 9, 5, 3, 4, 8]
         * [1, 9, 8, 3, 4, 2, 5, 6, 7]
         * [8, 5, 9, 7, 6, 1, 4, 2, 3]
         * [4, 2, 6, 8, 5, 3, 7, 9, 1]
         * [7, 1, 3, 9, 2, 4, 8, 5, 6]
         * [9, 6, 1, 5, 3, 7, 2, 8, 4]
         * [2, 8, 7, 4, 1, 9, 6, 3, 5]
         * [3, 4, 5, 2, 8, 6, 1, 7, 9]
         *
         *
         */
    }
}
