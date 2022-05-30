import java.util.ArrayList;
import java.util.Arrays;
import java.util.Comparator;
import java.util.List;

public class leetcode_0406 {
    class Solution {
        //lambda expression
        public int[][] reconstructQueue(int[][] people) {
            //首先对数对进行排序，按照数对的元素 1 降序排序，按照数对的元素 2 升序排序。原因是，按照元素 1 进行降序排序，对于每个元素，在其之前的元素的个数，就是大于等于他的元素的数量，而按照第二个元素正向排序，我们希望 k 大的尽量在后面，减少插入操作的次数
            //按照排完序后的顺序，依次将每个人放入队列中，那么当我们放入第 i 个人时
            // 1. 第0,...,i-1个人已经站在队列中，只要他们站在第i个人前面，就会对i个人产生影响，因为他们都比第i个人高或等于
            // 2. 第i+1,...,n-1个人还没有在队列中，无论他们放在哪里都不会对第i个人产生影响，因为他们都比第i个人矮
            Arrays.sort(people,(int[] u,int[] v) -> (u[0]==v[0]?u[1]-v[1]:v[0]-u[0]));
            List<int[]> res = new ArrayList<>();
            for(int[] person:people){
                if(res.size() > person[1]){
                    res.add(person[1],person);
                }else{
                    //res.size() <= person[1]
                    res.add(person);
                }
            }
            return res.toArray(new int[0][0]);
        }
        public int[][] reconstructQueue2(int[][] people) {
            Arrays.sort(people, new Comparator<int[]>() {
                @Override
                public int compare(int[] u, int[] v) {
                    return (u[0]==v[0]?u[1]-v[1]:v[0]-u[0]);
                }
            });
            List<int[]> res = new ArrayList<>();
            for(int[] person:people){
                if(res.size() > person[1]){
                    res.add(person[1],person);
                }else{
                    //res.size() <= person[1]
                    res.add(person);
                }
            }
            return res.toArray(new int[0][0]);
        }
        public <T> void printArr(T[][] arr) {
            System.out.print("[ ");
            String res = "";
            for (int i = 0; i < arr.length; i++)
                res += Arrays.toString(arr[i])+",";
            res = res.substring(0,res.length()-1);
            System.out.print(res);
            System.out.println(" ]");
        }
    }
    public static void main(String[] args) {
        leetcode_0406.Solution solution = new leetcode_0406().new Solution();
        int[][] people = {
                {7,0},{4,4},{7,1},{5,0},{6,1},{5,2}
        };
        //result
        //[[5,0],[7,0],[5,2],[6,1],[4,4],[7,1]]
        /**
         * 编号为 0 的人身高为 5 ，没有身高更高或者相同的人排在他前面。
         * 编号为 1 的人身高为 7 ，没有身高更高或者相同的人排在他前面。
         * 编号为 2 的人身高为 5 ，有 2 个身高更高或者相同的人排在他前面，即编号为 0 和 1 的人。
         * 编号为 3 的人身高为 6 ，有 1 个身高更高或者相同的人排在他前面，即编号为 1 的人。
         * 编号为 4 的人身高为 4 ，有 4 个身高更高或者相同的人排在他前面，即编号为 0、1、2、3 的人。
         * 编号为 5 的人身高为 7 ，有 1 个身高更高或者相同的人排在他前面，即编号为 1 的人。
         * 因此 [[5,0],[7,0],[5,2],[6,1],[4,4],[7,1]] 是重新构造后的队列。
         */
        int[][] res = solution.reconstructQueue2(people);
        Integer[][] anoRes = new Integer[res.length][res[0].length];
        for(int i = 0;i < res.length;i++){
            Integer[] ano = Arrays.stream(res[i]).boxed().toArray(Integer[]::new);
            anoRes[i] = ano;
        }
        solution.printArr(anoRes);
    }
}
