// https://leetcode-cn.com/problems/shu-de-zi-jie-gou-lcof/

#include "../common/common.h"

class Solution1
{
public:
	Solution1(TreeNode* A, TreeNode* B) : A(A), B(B) {}

	bool solve()
	{
		return dfs(A, B);
	}

private:
	TreeNode *A, *B;

	bool same(TreeNode* A, TreeNode* B)
	{
		if (B == NULL) return true;
		if (A == NULL) return false;
		if (A->val != B->val) return false;
		return same(A->left, B->left) && same(A->right, B->right);
	}

	bool dfs(TreeNode* A, TreeNode* B) 
	{
		if (A == NULL || B == NULL) return false;
		if (same(A, B)) return true;
		return dfs(A->left, B) || dfs(A->right, B);
	}
};

class Solution 
{
public:
	bool isSubStructure(TreeNode* A, TreeNode* B) 
	{
		return Solution1(A, B).solve();
	}
};

int main()
{
	Cases<TreeNode*, TreeNode*, bool> cases
	{
		{BuildTree({1,2,3}), BuildTree({3,1}), false},
		{BuildTree({3,4,5,1,2}), BuildTree({4,1}), true},
	};

	test(&Solution::isSubStructure, cases);

	return 0;
}