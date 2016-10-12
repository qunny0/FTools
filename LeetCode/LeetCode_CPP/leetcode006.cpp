// https://leetcode.com/problems/zigzag-conversion/

#include <iostream>
#include <string>

using namespace std;

// 01 Time Limit Exceeded. "A" 1
// 当只有一个元素的时候，死循环

class Solution {
public:
    string convert(string s, int numRows) {
        if (numRows == 1)
        {
            return s;
        }

        int len = s.length();
        int *seq = new int[numRows];
        string res = "";

        for (int i = 0; i < numRows; ++i)
        {
            if (i == numRows-1)
            {
                seq[i] = (numRows-1)*2;
            }
            else
            {
                seq[i] = (numRows-i-1)*2;
            }
        }

        for (int i = 0; i < numRows; ++i)
        {
            int bindex = i;
            int rowSearchTime = 0;
            while(bindex < len)
            {
                res += s[bindex];
                ++rowSearchTime;
                if (rowSearchTime%2==1)
                {
                    bindex += seq[i];
                }
                else
                {
                    bindex += seq[numRows-i-1];
                }
            }
        }

        delete []seq;
        return res;
    }
};

int main()
{
    Solution s;

    cout << s.convert("A", 1) << endl;
    return 0;
}




