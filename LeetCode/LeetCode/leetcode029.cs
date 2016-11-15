using System;
using System.Collections.Generic;


/**
 * Error 
 * # 1 : -1, -1
 * # 2 : -2147483648 -1
 * # 3 : -2147483648 -2
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
				if (dividend == Int32.MinValue && divisor == -1) {
					return Int32.MaxValue;
				}
				if (divisor == 1) {
					return dividend;
				}

				bool minus = false;
				if ((dividend < 0 && divisor > 0) || (dividend > 0 && divisor < 0)) {
					minus = true;
				}
				if (dividend < 0) {
					dividend = Math.Abs (dividend);
				}
				if (divisor < 0) {
					divisor = Math.Abs (divisor);
				}

				if (dividend < divisor) {
					return 0;
				}


				int tmpDividend = dividend;
				int res = 0;
				while (tmpDividend >= divisor) {
					int t = twoMinPower (tmpDividend, divisor);
					int tmpRes = 1;
					if (t == 0) {
						if (tmpDividend == divisor) {
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

				return k;
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
//				int t5 = s.Divide (-2147483648, -1);
//				int t6 = s.Divide (12, 2);
//				int t7 = s.Divide (2147482645, 2);
//				int t8 = s.Divide (2147483647, 3);
//
//				int idx = s.Divide (1111, 2);
//				Console.WriteLine ("" + idx);
//			}
//		}
	}
}

