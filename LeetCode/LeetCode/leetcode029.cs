using System;
using System.Collections.Generic;


/**
 * Error 
 * # 1 : -1, -1
 * # 2 : -2147483648 -1
 * # 3 : -2147483648 -2
 * # 4 : -1010369383 -2147483648
 * # 5 : 1100540749 -1090366779
 * # 6 : -2147483648 -1109186033
 * 
 * 只考虑了dividend的临界值，没有考虑divisor的临界值
*/

namespace LeetCode
{
	public class leetcode029
	{
		public class Solution {
			public Solution(){
				_halfIntMax = Int32.MaxValue >> 1;
			}

			public int Divide(int dividend, int divisor) {
				if (divisor == 0) {
					return Int32.MaxValue;
				}
				if (divisor == 1) {
					return dividend;
				}

				bool minus = false;
				int res = 0;
				if ((dividend < 0 && divisor > 0) || (dividend > 0 && divisor < 0)) {
					minus = true;
				}
				if (divisor < 0) {
					if (divisor == Int32.MinValue) {
						if (dividend == Int32.MinValue) {
							return 1;
						} else {
							return 0;
						}
					}
					divisor = Math.Abs (divisor);
				}
				if (dividend < 0) {
					if (dividend == Int32.MinValue) {
						dividend = dividend + divisor;
						res = res + 1;
					} 

					dividend = Math.Abs (dividend);
				}

				int tmpDividend = dividend;
				while (tmpDividend >= divisor) {
					int t = twoMinPower (tmpDividend, divisor);
					int tmpRes = 1;
					if (t == 0) {
						if (tmpDividend >= divisor) {
							tmpRes = 1;
						} else {
							break;
						}
					} else {
						tmpRes = Convert.ToInt32(Math.Pow (2, t-1));
					}

					tmpDividend = tmpDividend - divisor * tmpRes;
					res += tmpRes;
				}

				if (res < 0) {
					return Int32.MaxValue;
				}

				if (minus) {
					return -res;
				}
				return res;
			}

			/**
			 * 2147483647
			 * test case：
			 * # 1: (0, 1)
			 * # 2: (1, 0)
			 * # 3: (0, 0)
			 * # 4: (1, 1)
			 * # 5: (10, 3)
			 * # 6: (12, 2)
			 * # 7: (2147482645, 2) 
			 * # 8: (2147483647, 3)
			*/
			public int twoMinPower(int big, int small) {
				if (small == 0) {
					return 0;
				}

				int k = 0;
				while (true) {
					if (big <= small || small >= _halfIntMax) {
						return k;
					}
					small = small << 1;
					++k;
				}
			}

			static private int _halfIntMax;
		}

//		class MainClass
//		{
//			public static void Main (string[] args)
//			{
//				Solution s = new Solution();
//
////				int t1 = s.twoMinPower (0, 1);
////				int t2 = s.twoMinPower (1, 0);
////				int t3 = s.twoMinPower (0, 0);
////				int t4 = s.twoMinPower (1, 1);
////				int t5 = s.twoMinPower (10, 3);
////				int t6 = s.twoMinPower (12, 2);
////				int t7 = s.twoMinPower (2147482645, 2);
////				int t8 = s.twoMinPower (2147483647, 3);
//
////				int t1 = s.Divide (0, 1);
////				int t2 = s.Divide (1, 0);
////				int t3 = s.Divide (0, 0);
////				int t4 = s.Divide (1, 1);
////				int t5 = s.Divide (-2147483648, -1109186033);
////				int t6 = s.Divide (12, 2);
////				int t7 = s.Divide (2147482645, 2);
////				int t8 = s.Divide (2147483647, 3);
//
//				int idx = s.Divide (1111, 2);
//				Console.WriteLine ("" + idx);
//			}
//		}
	}
}

