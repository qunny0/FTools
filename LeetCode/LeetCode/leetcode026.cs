using System;
using System.Collections.Generic;


// # 1. [1, 1, 2] [1, 2] ; [1, 1]
// 返回无重复的数组元素长度n，修改nums，前n个数组为不重复的元素

namespace LeetCode
{
	public class leetcode026
	{
		public class Solution {
			public int RemoveDuplicates(int[] nums) {
				if (nums == null || nums.Length == 0) {
					return 0;
				}

				int res = 1;
				int tIdx = 0;
				int guard = nums[0];
				for (int i = 1; i < nums.Length; ++i) {
					if (guard == nums [i]) {
						continue;
					} else {
						++res;
						++tIdx;
						guard = nums [i];
						nums [tIdx] = guard;
					}
				}

				return res;
			}
		}

//		class MainClass
//		{
//			public static void Main (string[] args)
//			{
//				Solution s = new Solution();
//
//				int[] test1_0 = { 1, 1, 2 };
//				int[] test1_1 = {  };
//
//				int res = s.RemoveDuplicates (test1_0);
//				Console.WriteLine ("" + res);
//			}
//		}
	}
}

