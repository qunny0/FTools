using System;
using System.Collections.Generic;

namespace LeetCode
{
	public class leetcode0365
	{
		public class Solution {
			public bool IsValidSudoku(char[,] board) {
				IDictionary<char, bool> dic = new Dictionary<char, bool> ();

				for (int i = 0; i < board.GetLength (0); ++i) {
					// row
					dic.Clear();
					for (int j = 0; j < board.GetLength (1); ++j) {
						if (board [i, j] == '.') {
							continue;
						}
						if (dic.ContainsKey (board [i, j])) {
							return false;
						} else {
							dic[board[i, j]] = true;
						}
					}

					// col
					dic.Clear();
					for (int j = 0; j < board.GetLength (1); ++j) {
						if (board [j, i] == '.') {
							continue;
						}
						if (dic.ContainsKey (board [j, i])) {
							return false;
						} else {
							dic[board[j, i]] = true;
						}
					}
				}

				// part
				for (int i = 0; i < board.GetLength (0); i += 3) {
					for (int j = 0; j < board.GetLength (1); j += 3) {
						dic.Clear ();
						for (int ii = 0; ii < 3; ++ii) {
							for (int jj = 0; jj < 3; ++jj) {
								char c = board [i + ii, j + jj];
								if (c == '.') {
									continue;
								}

								if (dic.ContainsKey (c)) {
									return false;
								} else {
									dic[c] = true;
								}
							}
						}
					}
				}

				return true;
			}
		}

		class MainClass
		{
			public static void Main (string[] args)
			{
				Solution s = new Solution();
//				char[,] tt = {".87654321","2........","3........","4........","5........","6........","7........","8........","9........"};
				char[,] tt = {
					{'.', '8', '7', '6', '5', '4', '3', '2', '1'},
					{'2', '.', '.', '.', '.', '.', '.', '.', '.'},
					{'3', '.', '.', '.', '.', '.', '.', '.', '.'},
					{'4', '.', '.', '.', '.', '.', '.', '.', '.'},
					{'5', '.', '.', '.', '.', '.', '.', '.', '.'},
					{'6', '.', '.', '.', '.', '.', '.', '.', '.'},
					{'7', '.', '.', '.', '.', '.', '.', '.', '.'},
					{'8', '.', '.', '.', '.', '.', '.', '.', '.'},
					{'9', '.', '.', '.', '.', '.', '.', '.', '.'},
				};

				bool res = s.IsValidSudoku (tt);
				Console.WriteLine (res);
			}
		}
	}
}

