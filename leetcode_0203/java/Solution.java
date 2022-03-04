package leetcode_0203;


import java.util.LinkedList;
import java.util.List;

class ListNode {
     int val;
     ListNode next;
     ListNode() {}
     ListNode(int val) { this.val = val; }
     ListNode(int val, ListNode next) { this.val = val; this.next = next; }
};

public class Solution {
    public static ListNode removeElements(ListNode head, int val) {
        ListNode dummyHead = new ListNode();
        dummyHead.next = head;
        ListNode node = dummyHead;
        while(node.next != null){
            if(node.next.val == val){
                ListNode next = node.next;
                node.next = next.next;
                next = null;
            }else{
                node = node.next;
            }
        }
        return dummyHead.next;
    }


    public static <T> void printVec(List<T> list){
        String res = "";
        res += "[";
        for(T ele : list){
            res += ele+",";
        }
        res = res.substring(0,res.length()-1);
        res += "]";
        System.out.println(res);
    }

    public static void main(String args[]){
        ListNode head = new ListNode(1,new ListNode(2,new ListNode(6,new ListNode(3,new ListNode(4,new ListNode(5,new ListNode(6)))))));
        List<Integer> list = new LinkedList<Integer>();
        int target = 6;
        removeElements(head,target);
        ListNode node = head;
        while(node!=null){
            list.add(node.val);
            node = node.next;
        }
        printVec(list);
    }
}
