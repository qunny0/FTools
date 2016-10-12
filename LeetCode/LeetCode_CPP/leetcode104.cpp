#include <stdio.h>

// Maximum Depth of Binary Tree

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    int maxDepth(TreeNode* root) {
    	if (root == NULL)
    	{
    		return 0;
    	}

    	int leftDepth, rightDepth;
    	if (root->left)
    	{
	        int leftDepth = maxDepth(root->left);
    	}
    	if (root->right)
    	{
    		int rightDepth = maxDepth(root->right);
    	}
		
		int depth = leftDepth > rightDepth ? leftDepth + 1 : rightDepth + 1;
		return depth;   	
    }
};

int main()
{
	// Solution s;
	printf("Hello\n");
	// printf("%d\n", s.maxDepth(NULL));

	return 0;
}