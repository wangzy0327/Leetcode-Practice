import java.util.*;

public class leetcode_0341 {

    /**
     * // This is the interface that allows for creating nested lists.
     * // You should not implement it, or speculate about its implementation
     * public interface NestedInteger {
     *
     *     // @return true if this NestedInteger holds a single integer, rather than a nested list.
     *     public boolean isInteger();
     *
     *     // @return the single integer that this NestedInteger holds, if it holds a single integer
     *     // Return null if this NestedInteger holds a nested list
     *     public Integer getInteger();
     *
     *     // @return the nested list that this NestedInteger holds, if it holds a nested list
     *     // Return empty list if this NestedInteger holds a single integer
     *     public List<NestedInteger> getList();
     * }
     */
    public interface NestedInteger{
        public boolean isInteger();
        public Integer getInteger();
        public List<NestedInteger> getList();
    }
    public class NestedIntegerImpl implements NestedInteger{
        private Integer value;
        private List<NestedInteger> sub;

        public NestedIntegerImpl(){}

        public NestedIntegerImpl(Integer _value){
            this.value = _value;
        }

        public NestedIntegerImpl(List<NestedInteger> _sub){
            this.value = Integer.MIN_VALUE;
            sub = new ArrayList<>();
            for(NestedInteger nestedInteger : _sub)
                sub.add(nestedInteger);
        }


        @Override
        public boolean isInteger() {
            return Integer.MIN_VALUE < value;
        }

        @Override
        public Integer getInteger() {
            return value;
        }

        @Override
        public List<NestedInteger> getList() {
            return sub;
        }
    }
    public class NestedIterator implements Iterator<Integer> {

        private Deque<Integer> deq;

        private void append(List<NestedInteger> nestedList){
            for(NestedInteger nestedInteger : nestedList){
                if(nestedInteger.isInteger()){
                    deq.offerLast(nestedInteger.getInteger());
                }else{
                    append(nestedInteger.getList());
                }
            }
        }

        public NestedIterator(List<NestedInteger> nestedList) {
            deq = new LinkedList();
            append(nestedList);
        }

        @Override
        public Integer next() {
            return deq.pollFirst();
        }

        @Override
        public boolean hasNext() {
            return !deq.isEmpty();
        }
    }

    public class NestedIterator2 implements Iterator<Integer> {
        private List<Integer> vals;
        private Iterator<Integer> cur;

        public NestedIterator2(List<NestedInteger> nestedList) {
            vals = new ArrayList<Integer>();
            dfs(nestedList);
            cur = vals.iterator();
        }

        @Override
        public Integer next() {
            return cur.next();
        }

        @Override
        public boolean hasNext() {
            return cur.hasNext();
        }

        private void dfs(List<NestedInteger> nestedList) {
            for (NestedInteger nest : nestedList) {
                if (nest.isInteger()) {
                    vals.add(nest.getInteger());
                } else {
                    dfs(nest.getList());
                }
            }
        }
    }

    public static void main(String[] args) {
        NestedInteger n1 = new leetcode_0341().new NestedIntegerImpl(new ArrayList<NestedInteger>(){{
            add(new leetcode_0341().new NestedIntegerImpl(1));
            add(new leetcode_0341().new NestedIntegerImpl(1));
        }});
        NestedInteger n2 = new leetcode_0341().new NestedIntegerImpl(2);
        NestedInteger n3 = new leetcode_0341().new NestedIntegerImpl(new ArrayList<NestedInteger>(){{
            add(new leetcode_0341().new NestedIntegerImpl(1));
            add(new leetcode_0341().new NestedIntegerImpl(1));
        }});
        List<NestedInteger> narr = new ArrayList<>(){{
            add(n1);
            add(n2);
            add(n3);
        }};
//        NestedInteger arr = new leetcode_0341().new NestedIntegerImpl(narr);
        NestedIterator iterator = new leetcode_0341().new NestedIterator(narr);
        List<Integer> res = new ArrayList<>();
        while(iterator.hasNext()){
            res.add(iterator.next());
        }
        System.out.println(Arrays.toString(res.toArray(Integer[]::new)));
    }
}
