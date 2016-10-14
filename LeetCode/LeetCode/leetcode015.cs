using System;
using System.Collections.Generic;

// https://leetcode.com/problems/3sum/
// http://www.sigmainfy.com/blog/summary-of-ksum-problems.html

// 01 Time Limit Exceeded

namespace LeetCode015
{
	public class Solution {
		public Solution(){
			resList = new List<IList<int>> ();
		}

		public IList<IList<int>> ThreeSum(int[] nums) {
			Array.Sort (nums);
			Array.ForEach<int> (nums, (i) => Console.WriteLine (i));

			resList.Clear ();

			for (int i = 0; i < nums.Length - 2; ++i) {
				if (i > 0 && nums [i] == nums [i - 1]) {
					continue;
				}

				TwoSum (nums, i, 0 - nums [i]);
			}

			return resList;
		}

		void TwoSum(int[] nums, int start, int target) {
			int left = start+1, right = nums.Length-1;
			while (left < right) {
				if (nums [left] + nums [right] == target) {
					IList<int> cur = new List<int> ();
					cur.Add (nums [start]);
					cur.Add (nums [left]);
					cur.Add (nums [right]);
					resList.Add (cur);
					do {
						left++;
					}while(left < nums.Length && nums[left] == nums[left-1]);

					do {
						right--;
					} while(right >= 0 && nums[right] == nums[right+1]);

				} else if (nums [left] + nums [right] > target) {
					--right;
				} else {
					++left;
				}
			}
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

		public int _testNum = 1;
		public int[][] _inputTest = null;
		public List<IList<IList<int>>> _output = null;
	}

	class MainClass
	{
		public static void Main (string[] args)
		{
			Test test = new Test ();
			Solution s = new Solution ();
			test.runUnit (s);

			Console.WriteLine ("success !");
		}
	}
}

