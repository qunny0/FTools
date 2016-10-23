using System;
using System.Collections;

namespace leetcode001 {
	public class Solution {
		
		//		Hash Table
		/*
		 * hash 中存储不重复的元素。遍历数组保证了遍历到所有元素。
		 * 时间复杂度为nlogn
		 * 空间复杂度为n
		*/
		public int[] TwoSum(int[] nums, int target) {
			Hashtable ht = new Hashtable();

			for (int i = 0; i < nums.Length; ++i) {
//				if (!ht.ContainsKey (nums [i])) {
//					ht.Add (nums [i], i);
//				} else {
					ht [nums [i]] = i;
//				}
				Console.WriteLine ("--13--" + nums [i] + "," + i);
			}

			int[] retArray = new int[2];
			for (int i = 0; i < nums.Length; ++i) {
				int tgt = target - nums [i];
				if (ht.ContainsKey (tgt) && i != (int)ht[tgt]) {
					retArray [0] = i;
					retArray [1] = (int)ht[tgt];
					break;
				}
			}

			Console.WriteLine (" -- " + retArray [0] + ", " + retArray [1]);

			return retArray;
		}

		/*
		 * 2SUM的算法。获取和为target的两个值，而不是下标。
		 * 不适用于本题目
		 * 空间复杂度为 1
		 * 时间复杂度为 nlogn+n = nlogn
		 */
		public int[] TwoSum1(int[] nums, int target)
		{
			Array.Sort (nums);
			int i = 0, j = nums.Length - 1;
			int[] ret = new int[2];
			while (i < j) {
				var sum = nums [i] + nums [j];
				if (sum == target) {
					ret [0] = nums [i];
					ret [1] = nums [j];
					break;
				}
				if (sum > target) {
					--j;
				} else if (sum < target) {
					++i;
				}
			}

			Console.WriteLine ("~~" + ret [0] + ", " + ret [1]);
			return ret;
		}
	}

//	class MainClass
//	{
//		public static void Main (string[] args)
//		{
//			int[] nums = {0,4,3,0};
//			int target = 5;
//	
//			Solution s = new Solution ();
//			s.TwoSum1(nums, target);
//		}
//	}

}