import java.util.*;

public class leetcode_0752 {
    class Solution {
        public int openLock(String[] deadends, String target) {
            //思路：广度优先搜索BFS 每次将移动一个拨轮的一位数字所有列举出来入队 旋转次数+1
            //如果队列中出现target则 找到了返回旋转次数
            //如果队列中出现deadends则将其出队并不进行可能出现的下一个拨轮计算
            //直到队列为空，则返回
            Deque<String> dq = new LinkedList();
            dq.offerLast("0000");
            Set<String> deadSet = new HashSet();
            for(int i = 0;i < deadends.length;i++)
                deadSet.add(deadends[i]);
            //死亡数字包含target 直接返回-1
            if(deadSet.contains(target))
                return -1;
            //target等于初始值
            if(target.equals("0000"))
                return 0;
            rotate = 0;
            bfs(dq,deadSet,target);
            return rotate;
        }
        private int rotate;
        private void bfs(Deque<String> dq,Set<String> deadSet,String target){
            while(dq.size() > 0){
                int sz = dq.size();
                for(int i = 0;i < sz;i++){
                    String cur = dq.pollFirst();
                    //如果是死亡数字则跳过
                    if(deadSet.contains(cur))
                        continue;
                    else if(target.equals(cur))
                        return ;
                    else{
                        //需要计算拨轮的数字
                        List<String> lists = nextNums(cur,deadSet);
                        //入队
                        Iterator<String> iter = lists.iterator();
                        while(iter.hasNext())
                            dq.add(iter.next());
                        //将遍历过的元素放进deadSet 避免走回头路
                        deadSet.add(cur);
                    }
                }
                rotate += 1;
            }
            //队列为空,则不能解锁
            rotate = -1;
        }
        private List<String> nextNums(String num,Set<String> deadSet){
            List<String> res = new LinkedList();
            //正向转
            for(int i = 0;i < 4;i++){
                StringBuilder tmp = new StringBuilder(num);
                if(tmp.charAt(i) == '9')
                    tmp.setCharAt(i,'0');
                else
                    tmp.setCharAt(i,(char)(tmp.charAt(i)+1));
                if(!deadSet.contains(tmp.toString()))
                    res.add(tmp.toString());
            }
            //反向转
            for(int i = 0;i < 4;i++){
                StringBuilder tmp = new StringBuilder(num);
                if(tmp.charAt(i) == '0')
                    tmp.setCharAt(i,'9');
                else
                    tmp.setCharAt(i,(char)(tmp.charAt(i)-1));
                if(!deadSet.contains(tmp.toString()))
                    res.add(tmp.toString());
            }
            return res;
        }
    }
    public static void main(String[] args) {
//        Set<String> deadends = new HashSet<>(){{
//            add("0201");
//            add("0101");
//            add("0102");
//            add("1212");
//            add("2002");
//        }};
//        String[] deadends = {"0201","0101","0102","1212","2002"};
//        String target = "0202";
        //result
        //6
        //可能的移动序列为 "0000" -> "1000" -> "1100" -> "1200" -> "1201" -> "1202" -> "0202"
        String[] deadends = {"8887","8889","8878","8898","8788","8988","7888","9888"};
        String target = "8888";
        //result
        //-1
        leetcode_0752.Solution solution = new leetcode_0752().new Solution();
        int res = solution.openLock(deadends, target);
        System.out.println(res);
    }
}
