using System;
using System.Collections.Generic;


// # 1. [1, 1, 2] [1, 2] ; [1, 1]
// 返回无重复的数组元素长度n，修改nums，前n个数组为不重复的元素

namespace LeetCode
{
	public class leetcode029
	{
		public class Solution {
			public int Divide(int dividend, int divisor) {
				if (divisor == 0) {
					return Int32.MaxValue;
				}
				if (divisor == 1) {
					return dividend;
				}
				if (dividend < divisor) {
					return 0;
				}

//				int tmpHalfValue = Int32.MaxValue >> 1;
				int tmpDivisor = divisor;
				int tmpRes = 0;
				while (true) {
					tmpDivisor = tmpDivisor << tmpRes;
					if (dividend >= tmpDivisor) {
						break;
					}
					++tmpRes;
				}
				Console.WriteLine ("---34" + tmpRes);

				if (dividend > tmpRes) {
					
				}
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
				int k = 0;
				while (true) {
					small = small << k;
					if (big < small) {
						return k;
					}
					++k;
				}

				return k;
			}
		}

		class MainClass
		{
			public static void Main (string[] args)
			{
				Solution s = new Solution();

				int idx = s.Divide (1111, 2);
				Console.WriteLine ("" + idx);
			}
		}
	}
}

