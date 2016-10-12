#include <stdio.h>

#define kMaxRemoveStones 3

class Solution {
public:
    bool canWinNim(int n) {
        if (n <= 0)
        {
        	return false;
        }

        if (n % (kMaxRemoveStones+1) == 0)
        {
        	return false;
        }

        return true;
    }
};

int main()
{
	Solution s;

	printf("%d\n", s.canWinNim(10));

	return 0;
}