// https://leetcode.com/problems/string-to-integer-atoi/

#include <iostream>
#include <string>
#include <math.h>

using namespace std;

// 01 Wrong Answer Input:"-1"  Output:1  Expected:-1
// 02 Wrong Answer Input:"  -0012a42" Output:0 Expected:-12

class Solution {
public:
    int myAtoi(string str) {
        int len = str.length();

        int bindex = 0;
        while(str[bindex] == ' ' || str[bindex] == '\t')
        {
            ++bindex;
        }

        bool negative = false;
        if (str[bindex] == '-')
        {
            negative = true;
            ++bindex;
        }
        else if (str[bindex] == '+')
        {
            ++bindex;
        }

        int res = 0, preRes = 0;
        for (int i = bindex; i < len; ++i)
        {
            char ch = str[i];
            if (ch >= '0' && ch <= '9')
            {
                res = res*10 + (ch-'0');
                if (res/10 != preRes)
                {
                    if (negative)
                    {
                        return INT_MIN;
                    }
                    else
                    {
                        return INT_MAX;
                    }
                }
                preRes = res;
            }
            else
            {
                break;
            }
        }

        if (negative)
        {
            return -1*res;
        }
        return res;
    }
};

int main()
{
    Solution s;

    cout << s.myAtoi("  -0012a42") << endl;
    return 0;
}

