using System;
using System.Collections;
using System.Collections.Generic;

namespace LeetCode
{
	public class leetcode037
	{
		public class Solution {
			const char KEMPTY_CHAR = '.';

			public void SolveSudoku(char[,] board) {
				_sudokuBoard = board;

				bool ret = guessSudoku (0, 0);
			}

			/*
			* 从x，y开始
			*/
			protected bool guessSudoku(int x, int y) {
				// 空位置
				int ex, ey;
				bool haveEmpty = getNextEmptyPos (x, y, out ex, out ey);
				if (!haveEmpty) {
					return true;
				}

				ArrayList possibleList = getPossibleValue (ex, ey);
				if (possibleList.Count == 0) {
					_sudokuBoard [ex, ey] = KEMPTY_CHAR;
					return false;
				}

				foreach (char va in possibleList) {
					_sudokuBoard [ex, ey] = va;

					bool right = guessSudoku (ex, ey + 1);
					if (right) {
						return true;
					}
				}

				_sudokuBoard [ex, ey] = KEMPTY_CHAR;
				return false;
			}

			// 获取该位置可能的值
			protected ArrayList getPossibleValue(int x, int y) {
				ArrayList array = new ArrayList();

				Dictionary<char, short> dic = new Dictionary<char, short> ();

				// line
				for (int i = 0; i < _sudokuBoard.GetLength (1); ++i) {
					if (_sudokuBoard [x, i] != KEMPTY_CHAR) {
						dic[_sudokuBoard[x,i]] = 1;
					}
				}

				// column
				for (int i = 0; i < _sudokuBoard.GetLength (0); ++i) {
					if (_sudokuBoard [i, y] != KEMPTY_CHAR) {
						dic [_sudokuBoard [i, y]] = 1;
					}
				}

				// little cell
				int cx = x / 3;
				int cy = y / 3;
				for (int i = 0; i < 3; ++i) {
					for (int j = 0; j < 3; ++j) {
						char c = _sudokuBoard [cx * 3 + i, cy * 3 + j];
						if (c != KEMPTY_CHAR) {
							dic [c] = 1;
						}
					}
				}

				for (int i = 0; i < 9; ++i) {
					char v = (char)('1' + i);
					if (!dic.ContainsKey (v)) {
						array.Add (v);
					}
				}

				return array;
			}

			// 是否有为空的位置
			protected bool getNextEmptyPos(int cx, int cy, out int nx, out int ny) {
				int xl = _sudokuBoard.GetLength (0);
				int yl = _sudokuBoard.GetLength (1);

				nx = -1;
				ny = -1;

				if (cx >= xl) {
					return false;
				}

				int j = cy;
				for (int i = cx; i < xl; ++i) {
					for (; j < yl; ++j) {
						if (_sudokuBoard [i, j] == KEMPTY_CHAR) {
							nx = i;
							ny = j;
							return true;
						}
					}
					j = 0;
				}

				return false;
			}

			private char[,] _sudokuBoard;
		}

		class MainClass
		{
			public static void Main (string[] args)
			{
				Solution s = new Solution();

				char[,] tt = {
					{'5', '3', '.', '.', '7', '.', '.', '.', '.'},
					{'6', '.', '.', '1', '9', '5', '.', '.', '.'},
					{'.', '9', '8', '.', '.', '.', '.', '6', '.'},
					{'8', '.', '.', '.', '6', '.', '.', '.', '3'},
					{'4', '.', '.', '8', '.', '3', '.', '.', '1'},
					{'7', '.', '.', '.', '2', '.', '.', '.', '.'},
					{'.', '6', '.', '.', '.', '.', '2', '8', '.'},
					{'.', '.', '.', '4', '1', '9', '.', '.', '5'},
					{'.', '.', '.', '.', '8', '.', '.', '7', '9'},
				};

				s.SolveSudoku (tt);
				for (int i = 0; i < tt.GetLength (0); ++i) {
					for (int j = 0; j < tt.GetLength (1); ++j) {
						Console.Write (tt [i, j] + "\t");
					}
					Console.WriteLine ("");
				}
			}
		}
	}
}

