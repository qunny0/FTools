using System;
using System.Collections;
using System.Collections.Generic;

// #1 "9", "9"
// #2 "6", "501"

namespace LeetCode
{
	public class leetcode043
	{
		public class Solution {
			public string Multiply(string num1, string num2) {
				int n1l = num1.Length;
				int n2l = num2.Length;

				int resl = n1l + n2l;
				short[] arrRes = new short[resl];
				for (int i = 0; i < resl; ++i) {
					arrRes [i] = 0;
				}

				int n1i = n1l - 1, n2i = n2l - 1;
				string res = "";

				while (n2i >= 0) {
					int n2Digit = n2l - n2i - 1;

					n1i = n1l - 1;
					while (n1i >= 0) {
						int tmpres = (num1 [n1i] - '0') * (num2 [n2i] - '0');

						int n1Digit = n1l - n1i - 1;
						int offsetDigit = n1Digit + n2Digit;
						arrRes [offsetDigit] += (short)tmpres;
						--n1i;
					}

					--n2i;
				}

				int carray = 0;
				for (int i = 0; i < resl; ++i) {
					int tmpSum = arrRes [i] + carray;
					int digit = tmpSum % 10;
					carray = tmpSum / 10;

					res += digit;
				}

				char[] charArr = res.ToCharArray ();
				Array.Reverse (charArr);
				int s = charArr.Length;
				for (int i = 0; i < charArr.Length; ++i) {
					if (charArr [i] != '0') {
						s = i;
						break;
					}
				}

				res = new string (charArr).Substring(s);

				if (res.Length == 0) {
					res = "0";
				}

				return res;
			}
		}

		class MainClass
		{
			public static void Main (string[] args)
			{
				Solution s = new Solution();

				var res = s.Multiply ("0", "501");
				Console.WriteLine (res);
			}
		}
	}
}

