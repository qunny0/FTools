// https://leetcode.com/problems/palindrome-number/

#include <iostream>
#include <string>
#include <math.h>

using namespace std;

// 01 Wrong Answer Input:-2147447412 Output:true Expected:false

// 负数的时候直接为false，理清需求。

class Solution {
public:
    bool isPalindrome(int x) {
        if (x < 0)
        {
            return false;
        }

        int digit = 0;
        int tmpx = x;
        while(tmpx)
        {
            digit++;
            tmpx = tmpx/10;
        }
        // cout << "19 - " << digit << " " << endl;

        for (int i = 0; i < digit/2; ++i)
        {
            int pre = getDigit(x, i+1);
            int aft = getDigit(x, digit-i);
            if (pre != aft)
            {
                return false;
            }
        }
        return true;
    }

    int getDigit(int x, int dig)
    {
        int tx = x;
        if (dig > 1)
        {
            tx = x/(pow(10, (dig-1)));
        }
        int re = tx%10;

        // cout << "32 " << x << "," << dig << " - " << tx << "," << re << endl;

        return re;
    }
};

int main()
{
    Solution s;

    cout << s.isPalindrome(-2147447412) << endl;
    return 0;
}

