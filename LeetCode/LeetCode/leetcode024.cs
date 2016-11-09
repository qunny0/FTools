using System;
using System.Collections.Generic;

namespace LeetCode
{
	public class leetcode024
	{
//		Definition for singly-linked list.
		public class ListNode {
 			public int val;
 			public ListNode next;
 			public ListNode(int x) { val = x; }

			public void print() {
				ListNode p = this;
				while (p != null) {
					Console.Write (p.val + ", ");
					p = p.next;
				}
				Console.WriteLine ("");
			}
 		}

 		public class Solution {
			public ListNode SwapPairs(ListNode head) {
				if (head == null || head.next == null) {
					return head;
				}

				ListNode root = null;
				ListNode pre = null, aft = null;
				ListNode p1 = head, p2 = head.next;
				if (p2 != null) {
					aft = p2.next;
				}

				while (true) {
					if (pre == null) {
						root = p2;
					} else {
						pre.next = p2;
					}

					p2.next = p1;
					p1.next = aft;
					pre = p1;

					if (pre != null) {
						p1 = pre.next;
					} else {
						break;
					}

					if (p1 != null) {
						p2 = p1.next;
					} else {
						break;
					}

					if (p2 != null) {
						aft = p2.next;
					} else {
						break;
					}
				}
			
				return root;
			}
		}

		class MainClass
		{
			public static ListNode createListByArray(int [] nums) {
				ListNode root = null;
				ListNode pTmp = null;
		
				for (int i = 0; i < nums.Length; ++i) {
					ListNode p = new ListNode (nums [i]);

					if (pTmp == null) {
						pTmp = p;
					} else {
						pTmp.next = p;
						pTmp = p;
					}

					if (root == null) {
						root = p;
					}
				}

				return root;
			}

//			public static void Main (string[] args)
//			{
//				Solution s = new Solution();
//
//				ListNode[] test1 = new ListNode[2];
//				int[] test1_0 = { 1, 3, 5, 7 };
//				int[] test1_1 = { 2 };
//				test1 [0] = createListByArray (test1_0);
//				test1 [1] = createListByArray (test1_1);
//
//				ListNode proot = s.SwapPairs (test1[1]);
//				if (proot != null) {
//					proot.print ();
//				}
//			}
		}
	}
}

