// https://leetcode.com/problems/reverse-integer/

#include <iostream>

using namespace std;

// 01[Wrong Answer] 1534236469
// 02[Wrong Answer] -2147483412 -2143847412

// 由于INT_MAX = 2147483647, INT_MIN = -21474836478
// 2147483648

// ! 计算 除以10 之后是否与 之前 相同。如果不同则越界

class Solution1 {
public:
    int reverse(int x) {
        int rst = 0;
        while(x != 0){
            int next_rst = rst * 10 + x % 10;
            x = x / 10;
            if(next_rst/10 != rst) {
                rst  = 0;
                break;
            }
            rst = next_rst;
        }
        return rst;
    }
};

class Solution {
public:
    int reverse(int x) {
        int ret = 0;
        while (x != 0) {
        // handle overflow/underflow
            if (abs(ret) > 214748364) return 0;
            ret = ret * 10 + x % 10;
            x /= 10;
        }
        return ret;
    }
};

int main()
{
    Solution s;

    cout << s.reverse(-2147483412) << endl;
    return 0;
}

