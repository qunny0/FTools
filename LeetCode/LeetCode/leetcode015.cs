using System;
using System.Collections.Generic;

// https://leetcode.com/problems/3sum/
// http://www.sigmainfy.com/blog/summary-of-ksum-problems.html
// http://blog.csdn.net/puqutogether/article/details/45558445

// 01 Time Limit Exceeded

namespace LeetCode015
{
	public class Solution {
		public Solution(){
			resList = new List<IList<int>> ();
		}

		public IList<IList<int>> ThreeSum(int[] nums) {
			Array.Sort (nums);
//			Array.ForEach<int> (nums, (i) => Console.Write (i + ", "));

			resList.Clear ();

			for (int i = 0; i < nums.Length - 2;) {
				TwoSum(nums, i, 0-nums[i]);
				do {
					++i;
				} while(i < nums.Length && nums [i] == nums [i - 1]);
			}

			return resList;
		}
			
		int TwoSum(int[] nums, int start, int target)
		{			
//			Console.WriteLine ("\ntwo sum result : " + start + ", " + target);
			int resCount = 0;

			// check length
			if (nums.Length < 2) {
				return resCount;
			}

			int first = start;
			start += 1;

			// nums is valid
			int end = nums.Length - 1;
			while (start < end) {
				int tmpSum = nums [start] + nums [end];
				if (tmpSum == target) {
//					Console.WriteLine ("\t" + nums [first] + ", " + nums [start] + ", " + nums [end]);
					IList<int> res = new List<int> ();
					res.Add (nums[first]);
					res.Add (nums[start]);
					res.Add (nums[end]);
					resList.Add (res);
					++resCount;
					do {
						++start;
					} while( start < end && nums [start] == nums [start - 1]);

					do {
						--end;
					} while(end > start && nums [end] == nums [end + 1]);
				} else if (tmpSum > target) {
					--end;
				} else {
					++start;
				}
			}

			return resCount;
		}

		public List<IList<int>> resList;
	}

	public class Test {
		public Test() {
			const int testUnitNum = 4;
			_testNum = testUnitNum;
			_inputTest = new int[testUnitNum][];
			_output = new List<IList<IList<int>>>();

			// 01
			_inputTest[0] = new int[]{-1, 0, 1, 2, -1, -4};
			{
				List<IList<int>> r = new List<IList<int>> ();
				
				IList<int> r1 = new List<int> ();
				r1.Add (-1);
				r1.Add (0);
				r1.Add (1);
				r.Add (r1);

				IList<int> r2 = new List<int> ();
				r2.Add (-1);
				r2.Add (-1);
				r2.Add (2);
				r.Add (r2);

				_output.Add (r);
			}

			// 02
			_inputTest[1] = new int[]{-1, 0, 1};
			{
				List<IList<int>> r = new List<IList<int>> ();

				IList<int> r1 = new List<int> ();
				r1.Add (-1);
				r1.Add (0);
				r1.Add (1);
				r.Add (r1);

				_output.Add (r);
			}

			// 03
			_inputTest[2] = new int[]{0, 0, 0};
			{
				List<IList<int>> r = new List<IList<int>> ();

				IList<int> r1 = new List<int> ();
				r1.Add (0);
				r1.Add (0);
				r1.Add (0);
				r.Add (r1);

				_output.Add (r);
			}

			// 04
			_inputTest[3] = new int[]{2, 2, -4, -5, -3};
			{
				List<IList<int>> r = new List<IList<int>> ();

				IList<int> r1 = new List<int> ();
				r1.Add (-4);
				r1.Add (2);
				r1.Add (2);
				r.Add (r1);

				IList<int> r2 = new List<int> ();
				r2.Add (-4);
				r2.Add (2);
				r2.Add (2);
				r.Add (r2);

				_output.Add (r);
			}

		}

		public void runUnit(Solution s) {
			for (int i = 0; i < _testNum; ++i) {
				IList<IList<int>> list = s.ThreeSum (_inputTest [i]);
				IList<IList<int>> result = _output[i];

				if (list.Count != result.Count) {
					throw new Exception ("failed ---- " + i);
				}

				for(int j = 0; j < list.Count; ++j){
					IList<int> l = list[j];
					IList<int> r = result[j];

					for(int k = 0; k < 3; ++k){
						int lv = l.IndexOf (k), rv = r.IndexOf (k);
						if (lv != rv) {
							throw new Exception ("failed ---- " + i);
						}
					}
				}
			}

		}

		public void runTwoSumTest(Solution s) {
			// 1
//			int[] rray = { };
//			int res = 0;

			// 2
//			int[] rray = {1,1};
//			int res = 2;

			// 3
//			int[] rray = {1,1,2,2};
//			int res = 3;

			// 4
//			int[] rray = {1,1,1};
//			int res = 2;

			// 5
//			int[] rray = {1,2,4,3,5,6};
//			int res = 7;

			// 6
//			int[] rray = {1,2,4,3,5,6,1,2,4,3,5,6};
//			int res = 7;

//			int arrlen = rray.Length;
//			s.TwoSumTest (rray, 0, res);
		}

		public int _testNum = 1;
		public int[][] _inputTest = null;
		public List<IList<IList<int>>> _output = null;
	}

//	class MainClass
//	{
//		public static void Main (string[] args)
//		{
//			Solution s = new Solution ();
//			int[] inputTest = {0, 0, 0};
////			int[] inputTest = {-1, 0, 1, 2, -1, -4};
//			s.ThreeSum(inputTest);
//
//			Console.WriteLine ("success !");
//		}
//	}
}

