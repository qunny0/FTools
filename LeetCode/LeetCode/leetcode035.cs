using System;
using System.Collections.Generic;


/**
 * Error 
 * # 1 TLE [1, 3] 0
 * # 2 {3, 1} 1
*/

namespace LeetCode
{
	public class leetcode035
	{
		public class Solution {
			public int SearchInsert(int[] nums, int target) {
				int start = 0;
				int end = nums.Length - 1;
				int idx = -1;
				while (start <= end) {
					int midIdx = (start + end) / 2;
					int midVle = nums [midIdx];

					if (midVle == target) {
						idx = midIdx;
						break;
					}

					if (midVle > target) {
						end = midIdx - 1;
					} else {
						start = midIdx + 1;
					}
				}

				if (idx == -1) {
					idx = start;
				}

				return idx;
			}
		}

//		class MainClass
//		{
//			public static void Main (string[] args)
//			{
//				Solution s = new Solution();
//				int[] tt = { 1, 3, 5, 6 };
//				int t = 0;
//
////				[1,3,5,6], 5 → 2
////				[1,3,5,6], 2 → 1
////				[1,3,5,6], 7 → 4
////				[1,3,5,6], 0 → 0
//
//				int res = s.SearchInsert (tt, t);
//				Console.WriteLine (res);
//			}
//		}
	}
}

