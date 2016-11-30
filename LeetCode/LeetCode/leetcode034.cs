using System;
using System.Collections.Generic;


/**
 * Error 
 * # 1 TLE [1, 3] 0
 * # 2 {3, 1} 1
*/

namespace LeetCode
{
	public class leetcode034
	{
		public class Solution {
			public int[] SearchRange(int[] nums, int target) {
				int []res = {-1, -1};

				int start = 0;
				int end = nums.Length - 1;
				int lIdx = -1;
				while (start <= end) {
					int midIdx = (start + end) / 2;
					int mid = nums [midIdx];

					if (mid == target) {
						if (midIdx == 0) {
							lIdx = midIdx;
							break;
						} else if (midIdx > 0 && nums [midIdx - 1] < target) {
							lIdx = midIdx;
							break;
						}
					}

					bool moveLeft = false;
					if (mid > target) {
						moveLeft = true;
					} else if (mid == target && nums [midIdx - 1] == target) {
						moveLeft = true;
					}

					if (moveLeft) {
						end = midIdx - 1;
					} else {
						start = midIdx + 1;
					}
				}
				res [0] = lIdx;

				start = 0;
				end = nums.Length - 1;
				int rIdx = -1;
				while (start <= end) {
					int midIdx = (start + end) / 2;
					int mid = nums [midIdx];

					if (mid == target) {
						if (midIdx == nums.Length - 1) {
							rIdx = midIdx;
							break;
						} else if (nums [midIdx + 1] > target) {
							rIdx = midIdx;
							break;
						}
					}

					bool moveRight = false;
					if (mid < target) {
						moveRight = true;
					} else if (mid == target && nums [midIdx + 1] == target) {
						moveRight = true;
					}

					if (moveRight) {
						start = midIdx + 1;
					} else {
						end = midIdx - 1;
					}
				}
				res [1] = rIdx;

				return res;
			}
		}

//		class MainClass
//		{
//			public static void Main (string[] args)
//			{
//				Solution s = new Solution();
////				int [] test = {5, 7, 7, 8, 8, 10};
////				int tt = 8;
//				int [] test = {1, 1, 2, 2};
//				int tt = 1;
//
//				// 0,0 	1
//				// 0	1
//				// 		1
//				// 1, 1, 2, 2	1
//				// 1, 1, 2, 2	2
//				// 1, 2			1
//				// 1, 2			2
//
//
//				var res = s.SearchRange (test, tt);
//				Array.ForEach<int> (res, (k) => Console.Write (k + ","));
//			}
//		}
	}
}

