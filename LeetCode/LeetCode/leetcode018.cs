using System;
using System.Collections;
using System.Collections.Generic;


namespace leetcode018 {
	public class Solution {
		public Solution(){
			_res = new List<IList<int>> ();
			_ontRes = new int[4];
		}

		public IList<IList<int>> FourSum(int[] nums, int target) {
			if (nums.Length < 4) {
				return _res;
			}

			Array.Sort (nums);
			Array.ForEach<int> (nums, (k) => Console.Write (k + ", "));
			Console.WriteLine ("");

			int ts = 0;
			int len = nums.Length;
			do {
				int tmpsum = target - nums [ts];
				_ontRes[0] = nums [ts];
				Console.WriteLine(" ----- " + nums[ts]);
				ThreeSum (nums, ts + 1, tmpsum);
				do {
					++ts;
				}while(ts < len-2 && nums[ts] == nums[ts-1]);
			} while(ts < len - 2);

			return _res;
		}

		public void ThreeSum (int[] nums, int start, int target) {
			int ts = start;
			int len = nums.Length;
			do {
				int tmpsum = target - nums [ts];
				Console.WriteLine("\t ----- " + nums[ts]);
				_ontRes[1] = nums [ts];
				TwoSum (nums, ts + 1, tmpsum);
				do {
					++ts;
				}while(ts < len-1 && nums[ts] == nums[ts-1]);
			} while(ts < len - 1);
		}

		public void TwoSum(int[] nums, int start, int target) {
			int ts = start;
			int te = nums.Length - 1;

			while (ts < te) {
				int tsum = nums [ts] + nums [te];
				if (tsum == target) {
					_ontRes [2] = nums [ts];
					_ontRes [3] = nums [te];
					IList<int> tmpRes = new List<int> (_ontRes);
//					tmpRes.Add (nums [ts]);
//					tmpRes.Add (nums [te]);
					Console.WriteLine (" \t\t-- " + nums [ts] + " , " + nums [te]);
					_res.Add (tmpRes);

					do {
						++ts;	
					} while(ts < te && nums [ts] == nums [ts - 1]);
					do {
						--te;
					} while(te > ts && nums [te] == nums [te + 1]);

//					Console.WriteLine (" -48- " + ts + " , " + te);

				} else if (tsum > target) {
					do {
						--te;
					} while(te > ts && nums [te] == nums [te + 1]);
				} else {
					do {
						++ts;	
					} while(ts < te && nums [ts] == nums [ts - 1]);
				}
			}
		}

		public void printout(){
			foreach (var one in _res) {
				foreach (var num in one) {
					Console.Write (num + ", ");
				}
				Console.WriteLine ("");
			}
		}

		IList<IList<int>> _res;
		int[] _ontRes;
	}

//	class MainClass
//	{
//		public static void Main (string[] args)
//		{
//			Solution s = new Solution ();
//			int[] intest = {1, 0, -1, 0, -2, 2};
//			int target = 0;
//			s.FourSum (intest, target);
//			s.printout ();
//		}
//	}

}	