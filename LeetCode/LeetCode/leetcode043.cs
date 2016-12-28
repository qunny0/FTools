using System;
using System.Collections;
using System.Collections.Generic;

// #1 [5,4,1,2]

namespace LeetCode
{
	public class leetcode043
	{
		public class Solution {
			public string Multiply(string num1, string num2) {
				int n1l = num1.Length;
				int n2l = num2.Length;

				int resl = n1l * n2l;
				short[] arrRes = new short[resl];
				for (int i = 0; i < resl; ++i) {
					arrRes [i] = 0;
				}


				int n1i = n1l - 1, n2i = n2l - 1;

				string res = "";

				while (n2i >= 0) {
					int n2Digit = n2l - n2i - 1;
					Console.WriteLine (n2Digit);

					n1i = n1l - 1;
					carrayDigit = 0;
					while (n1i >= 0) {
						int tmpres = (num1 [n1i] - '0') * (num2 [n2i] - '0');

						int n1Digit = n1l - n1i - 1;
						int offsetDigit = n1Digit + n2Digit;
						arrRes [offsetDigit] += (short)tmpres;

						Console.WriteLine ("--" + n2Digit + ", " + n1Digit + ", " + tmpres + ", " + offsetDigit);

						--n1i;
					}

					--n2i;
				}

				return res;
			}
		}

		class MainClass
		{
			public static void Main (string[] args)
			{
				Solution s = new Solution();

				var res = s.Multiply ("98877", "3245");
				Console.WriteLine (res);
			}
		}
	}
}

