using System;
using System.Collections;
using System.Collections.Generic;

//https://leetcode.com/problems/integer-to-roman/

// I（1）、V（5）、X（10）、L（50）、C（100）、D（500）、M（1000）

//	重复数次：一个罗马数字重复几次，就表示这个数的几倍。

//右加左减：
//	在较大的罗马数字的右边记上较小的罗马数字，表示大数字加小数字。
//	在较大的罗马数字的左边记上较小的罗马数字，表示大数字减小数字。
//	左减的数字有限制，仅限于I、X、C。比如45不可以写成VL，只能是XLV
//	但是，左减时不可跨越一个位数。比如，99不可以用IC（）表示，而是用XCIX（）表示。（等同于阿拉伯数字每位数字分别表示。）
//	左减数字必须为一位，比如8写成VIII，而非IIX。
//	右加数字不可连续超过三位，比如14写成XIV，而非XIIII。（见下方“数码限制”一项。）

//加线乘千：
//	在罗马数字的上方加上一条横线或者加上下标的Ⅿ，表示将这个数乘以1000，即是原数的1000倍。
//	同理，如果上方有两条横线，即是原数的1000000（）倍。

//数码限制：
//	同一数码最多只能出现三次，如40不可表示为XXXX，而要表示为XL。
//	例外：由于IV是古罗马神话主神朱庇特（即IVPITER，古罗马字母里没有J和U）的首字，因此有时用IIII代替IV。

namespace leetcode012 {
	public class Solution {
		
		public string IntToRoman(int num) {
			char[] romans = {'M', 'D', 'C', 'L', 'X', 'V', 'I'};
			int[] nums = { 1000, 500, 100, 50, 10, 5, 1 };

			string strRet = "";
			for (int i = 0; i < nums.Length; i += 2) {
				int bitnum = num / nums[i];
				num = num % nums [i];

				if (bitnum == 0) {
					continue;
				}
				if (bitnum <= 3) {
					for (int j = 0; j < bitnum; ++j) {
						strRet += romans [i];
					}
				} else if (bitnum <= 5) {
					for (int j = 0; j < 5 - bitnum; ++j) {
						strRet += romans [i];
					}
					strRet += romans [i - 1];
				} else if (bitnum <= 8) {
					strRet += romans [i - 1];
					for (int j = 0; j < bitnum - 5; ++j) {
						strRet += romans [i];
					}
				} else {
					strRet += romans [i];
					strRet += romans [i - 2];
				}
			}

			return strRet;
		}
	}

//	class MainClass
//	{
//		public static void Main (string[] args)
//		{
//			Dictionary<int, string> dictTests = new Dictionary<int, string>();
//			dictTests.Add (14, "XIV");
//			dictTests.Add (1, "I");
//			dictTests.Add (4, "IV");
//			dictTests.Add (8, "VIII");
//			dictTests.Add (16, "XVI");
//			dictTests.Add (45, "XLV");
//			dictTests.Add (99, "XCIX");
//			dictTests.Add (1666, "MDCLXVI");
//			dictTests.Add (3999, "MMMCMXCIX");
//
//			Solution s = new Solution ();
//
//			foreach (KeyValuePair<int, string> kvp in dictTests) {
//				string strRes = s.IntToRoman (kvp.Key);
//				if (strRes != kvp.Value) {
//					throw new Exception ("error " + kvp + " --> " + strRes);
//				}
//			}
//
//			Console.WriteLine (s.IntToRoman(3999));
//		}
//	}
}