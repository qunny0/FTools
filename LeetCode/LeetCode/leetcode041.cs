using System;
using System.Collections;
using System.Collections.Generic;

/*
 * # 1. [1, 1] Time Limit Exceeded  TLE
*/

namespace LeetCode
{
	public class leetcode041
	{
		public class Solution {
			public int FirstMissingPositive(int[] nums) {
				int len = nums.Length;
				int i = 0;
				while (i < len) {
					if (nums [i] > 0 && nums [i] <= len && (nums[i]-1) != i && nums[nums[i]-1] != nums[i]) {
						int tmpi = nums [i] - 1;
						int tmp = nums [i];
						nums [i] = nums [tmpi];
						nums [tmpi] = tmp;
					} else {
						++i;
					}
				}

				Array.ForEach<int> (nums, (k) => Console.Write (k + ", "));
				Console.WriteLine ("");

				for (int j = 0; j < len; ++j) {
					if (nums [j] != (j + 1)) {
						return (j + 1);
					}
				}

				return len+1;
			}
		}

//		class MainClass
//		{
//			public static void Main (string[] args)
//			{
//				Solution s = new Solution();
//				int[] t1 = {1, 1};
//
//				int res = s.FirstMissingPositive (t1);
//				Console.WriteLine (res);
//			}
//		}
	}
}

