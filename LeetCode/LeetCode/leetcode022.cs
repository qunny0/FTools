using System;
using System.Collections.Generic;


namespace LeetCode
{
	public class leetcode022
	{
		public class Solution {
			public Solution() {
				_resList = new List<string>();
				_nMaxLevel = 0;
			}

			public IList<string> GenerateParenthesis(int n) {
				_nMaxLevel = n * 2;
				_resPath = new char [_nMaxLevel];

				dfs (1, n, 0);

				return _resList;
			}

			protected void dfs(int level, int leftBracketRemain, int leftBracketNum){

//				Console.WriteLine ("----" + level + ", " + leftBracketRemain + ", " + leftBracketNum);

				if (level > _nMaxLevel) {
//					Console.WriteLine (_resPath);
					_resList.Add (new string(_resPath));
					return;
				}

				// left
				if (leftBracketRemain >= 1) {
					_resPath [level - 1] = kLeftBracket;
					dfs (level + 1, leftBracketRemain - 1, leftBracketNum + 1);
				}

				// right
				if (level > 1 && leftBracketNum >= 1) {
					_resPath [level - 1] = kRightBracket;
					dfs (level + 1, leftBracketRemain, leftBracketNum - 1);
				}

			}

			private IList<string> _resList;
			private char[] _resPath;
			private int _nMaxLevel;
			private static char kLeftBracket = '(';
			private static char kRightBracket = ')';
		}

//		class MainClass
//		{
//			public static void Main (string[] args)
//			{
//				Solution s = new Solution();
//				s.GenerateParenthesis (0);					
//			}
//		}
	}
}

