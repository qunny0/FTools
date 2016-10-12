#include <stdio.h>

class Solution {
public:
    int addDigits(int num) {
    	if (num <= 9)
    	{
    		return num;
    	}

    	int n = 0;
    	while(num > 0)
    	{
    		n += (num % 10);
    		num = num / 10;
    	}

    	return addDigits(n);
    }
};


int main()
{
	Solution s;
	printf("%d\n", s.addDigits(22222));

	return 0;
}