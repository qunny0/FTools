using System;
using System.Collections.Generic;


namespace LeetCode
{
	public class leetcode023
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
			public ListNode MergeKLists(ListNode[] lists) {
				ListNode root = null;

				return root;
			}
		}

		class MainClass
		{
			public static void createNode(int val) {
				
			}

			public static ListNode createListByArray(int [] nums) {
				ListNode root = null;
	
//				Array.ForEach<int> (nums, (k) => Console.Write (k + ", "));


				Array.ForEach<int>(nums, (k) => new );

				return root;
			}

			public static void Main (string[] args)
			{
				Solution s = new Solution();

				ListNode[] test1 = new ListNode[2];
				int[] test1_0 = { 1, 2, 3, 4, 5 };
				test1[0] = createListByArray(test1_0);
				test1 [0].print ();


				s.MergeKLists (test1);
			}
		}
	}
}

