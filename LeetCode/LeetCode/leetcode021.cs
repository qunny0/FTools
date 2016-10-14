using System;

//01 Runtime Error [1] []

namespace LeetCode
{
	public class leetcode021
	{
		public class ListNode {
    		public int val;
     		public ListNode next;
     		public ListNode(int x) { val = x; }

			public void print() {
				ListNode p = this;
				while (p != null) {
					Console.WriteLine (p.val);
					p = p.next;
				}
			}
 		}
 		
		public class Solution {
			public ListNode MergeTwoLists(ListNode l1, ListNode l2) {
				ListNode retHead = null, retP = null;

				ListNode p1 = l1, p2 = l2;
				ListNode pTmp = null;
				while (p1 != null || p2 != null) {

					if (p1 == null) {
						pTmp = p2;
						p2 = null;
					} else if (p2 == null) {
						pTmp = p1;
						p1 = null;
					} else {
						if (p1.val > p2.val) {
							pTmp = p2;
							p2 = p2.next;
						} else {
							pTmp = p1;
							p1 = p1.next;
						}
					}

					if (retP != null) {
						retP.next = pTmp;
					}
					retP = pTmp;

					if (retHead == null) {
						retHead = retP;
					}
				}
				return retHead;
			}

			public ListNode createArray(int[] arr){
				ListNode head = null, p = null;
				for (int i = 0; i < arr.Length; ++i) {
					ListNode newNode = new ListNode (arr [i]);
					if (head == null) {
						head = newNode;
					}
					if (p == null) {
						p = newNode;
					} else {
						p.next = newNode;
					}

					p = newNode;
				}

				return head;
			}
		}

//		class MainClass
//		{
//			public static void Main (string[] args)
//			{
//				Solution s = new Solution();
//					
//				int[] arr1 = {5};
//				int[] arr2 = {1,2,4};
//				ListNode l1 = s.createArray (arr1);
//				ListNode l2 = s.createArray (arr2);
//
//				ListNode l = s.MergeTwoLists (l1, l2);
//				if (l != null) {
//					l.print ();
//				}
//			}
//		}
	}
}

