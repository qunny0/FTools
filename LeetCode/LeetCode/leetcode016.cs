using System;
using System.Collections.Generic;

// https://leetcode.com/problems/3sum-closest/

// 3Sum Closest

namespace LeetCode016
{
	public class Solution {
		public Solution(){
			_target = 0;
			_offset = 0;
			_resSum = 0;
		}

		public int ThreeSumClosest(int[] nums, int target) {
			if (nums.Length < 3) {
				return 0;
			}

			Array.Sort (nums);
			_target = target;
			_resSum = nums [0] + nums [1] + nums [2];
			_offset = Math.Abs (_resSum - target);
			Array.ForEach<int> (nums, (j) => Console.Write (j + ", "));

			int i = 0;
			while(i < nums.Length) {
				TwoSumClosest(nums, i+1, target);

				do {
					++i;
				} while(i < nums.Length && nums[i] == nums[i-1]);
			}

			return _resSum;
		}
			
		public int TwoSumClosest(int[] nums, int start, int target)
		{			
//			Console.WriteLine ("");

			int resCount = 0;
			if (nums.Length < 2) {
				return resCount;
			}
			int first = start-1;

			// nums is valid
			int end = nums.Length - 1;
			while (start < end) {
				int tmpSum = nums[first] + nums [start] + nums [end];

				int offset = Math.Abs(tmpSum - _target);
				Console.WriteLine ("(" + first + ", " + start + "-" + end + ") : " + tmpSum + ", -- " +  offset + ", " + _offset);
				if (offset < _offset) {
					_offset = offset;
					_resSum = tmpSum;
					Console.WriteLine ("\t" + _resSum);
				}

				if (tmpSum > target) {
					--end;
				} else if (tmpSum < target) {
					++start;
				} else {
					break;
				}
			}

			return resCount;
		}

		int _target;
		int _offset;
		int _resSum;
	}

//	class MainClass
//	{
//		public static void Main (string[] args)
//		{
//			Solution s = new Solution ();
//			int[] inputTest = {0, 0, 0};
//			int target = 1;
//			int resSum = s.ThreeSumClosest(inputTest, target);
//
//			Console.WriteLine ("success ! - " + resSum);
//		}
//	}
}

