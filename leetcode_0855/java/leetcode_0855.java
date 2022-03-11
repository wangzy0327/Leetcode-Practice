import java.util.TreeSet;

public class leetcode_0855 {
    class ExamRoom {
        /**
         考场排座的位次本质是要保证 座次的有序集合在有离开后还要保证顺序，以方便有学生能进来坐
         这里有序集合能够保证顺序性，所以能够快速插入元素和删除元素 时间复杂度为O(logn),且通过遍历能够确定考生坐的位置
         需要注意考虑，左右边界
         */
        private int size;
        private TreeSet<Integer> tree;
        public ExamRoom(int n) {
            this.size = n;
            tree = new TreeSet();
        }

        public int seat() {
            int stud = 0;
            if(tree.size() > 0){
                //前一个线段边
                int prev = -1;
                //初始化距离, 注意左边
                int dist = tree.first();
                for(Integer i : tree){
                    if(prev != -1){
                        int d = (i - prev)/2;
                        if(d > dist){
                            dist = d;
                            stud = prev + d;
                        }
                    }
                    prev = i;
                }
                //判断右端
                if(size - 1 - prev > dist)
                    stud = size - 1;
            }
            tree.add(stud);
            return stud;
        }

        public void leave(int p) {
            tree.remove(p);
        }
    }

    public static void main(String[] args) {
        ExamRoom examRoom = new leetcode_0855().new ExamRoom(10);
        System.out.printf("%d,", examRoom.seat());
        System.out.printf("%d,", examRoom.seat());
        System.out.printf("%d,", examRoom.seat());
        System.out.printf("%d,", examRoom.seat());
        examRoom.leave(4);
        System.out.printf("%d\n", examRoom.seat());
        //result
        //[0,9,4,2,5]
    }
}
