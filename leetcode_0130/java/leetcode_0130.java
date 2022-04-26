import java.util.Arrays;
import java.util.Collections;

public class leetcode_0130 {
    class Solution {
        public void solve(char[][] board) {
            //思路：由于边界上的'O'不会被围绕，可以通过边界上的'O'为起点进行dfs遍历
            //将连接到的节点字符改为'#',剩下所有的'O'都是被围绕的，设置为'X'即可
            //然后再将'#'设置为'O'即可
            int m = board.length;int n = board[0].length;
            //首行
            for(int i = 0;i < n;i++)
                dfs(board,0,i);
            //首列
            for(int i = 0;i < m;i++)
                dfs(board,i,0);
            //尾行
            for(int i = 0;i < n;i++)
                dfs(board,m-1,i);
            //尾列
            for(int i = 0;i < m;i++)
                dfs(board,i,n-1);
            for(int i = 0;i < m;i++){
                for(int j = 0;j < n;j++){
                    if(board[i][j] == '#')
                        board[i][j] = 'O';
                    else if(board[i][j] == 'O')
                        board[i][j] = 'X';
                }
            }
        }
        private void dfs(char[][] board,int i,int j){
            if(i >= 0 && i < board.length && j >= 0 && j < board[0].length && board[i][j]=='O'){
                board[i][j] = '#';
                dfs(board,i-1,j);
                dfs(board,i+1,j);
                dfs(board,i,j-1);
                dfs(board,i,j+1);
            }
        }
    }
    public static void main(String[] args) {
        leetcode_0130.Solution solution = new leetcode_0130().new Solution();
        char[][] board = {
                {'X','X','X','X'},
                {'X','O','O','X'},
                {'X','X','O','X'},
                {'X','O','X','X'}
        };
        for(int i = 0;i < board.length;i++)
            System.out.println(Arrays.toString(board[i]));
        solution.solve(board);
        System.out.println("--------------------------------------------");
        for(int i = 0;i < board.length;i++)
            System.out.println(Arrays.toString(board[i]));
        /**
         *
         * [X, X, X, X]
         * [X, X, X, X]
         * [X, X, X, X]
         * [X, O, X, X]
         *
         */
    }
}
