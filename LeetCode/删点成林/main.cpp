// https://leetcode-cn.com/problems/delete-nodes-and-return-forest/

#include "../common/common.h"

class Solution1
{
public:
	Solution1(TreeNode* root, const vector<int>& nums)
		: root(root), nums(nums) {}

	vector<TreeNode*> solve()
	{
		unordered_set<int> s(nums.begin(), nums.end());
		return delNodes(root, s);
	}

private:
	TreeNode* root;
	vector<int> nums;

	void append(vector<TreeNode*>& a, const vector<TreeNode*>& b)
	{
		a.insert(a.end(), b.begin(), b.end());
	}

	vector<TreeNode*> delNodes(TreeNode* p, unordered_set<int>& s)
	{
		if (p == NULL) return {};

		vector<TreeNode*> res;
		vector<TreeNode*> left = delNodes(p->left, s);
		vector<TreeNode*> right = delNodes(p->right, s);

		if (s.count(p->val) > 0)
		{
			s.erase(p->val);
			append(res, left);
			append(res, right);
			return res;
		}

		res.push_back(p);

		// 处理左子树
		if (left.size() == 0)
		{
			p->left = NULL;
		}
		else if (left.size() == 1)
		{
			if (left[0] != p->left)
			{
				p->left = NULL;
				append(res, left);
			}
		}
		else
		{
			auto pos = find(left.begin(), left.end(), p->left);
			if (pos == left.end()) p->left = NULL;
			else
			{
				left.erase(pos);
			}
			append(res, left);
		}

		// 处理右子树
		if (right.size() == 0)
		{
			p->right = NULL;
		}
		else if (right.size() == 1)
		{
			if (right[0] != p->right)
			{
				p->right = NULL;
				append(res, right);
			}
		}
		else
		{
			auto pos = find(right.begin(), right.end(), p->right);
			if (pos == right.end()) p->right = NULL;
			else
			{
				right.erase(pos);
			}
			append(res, right);
		}

		return res;
	}
};

class Solution2
{
public:
	Solution2(TreeNode* root, const vector<int>& nums)
		: root(root), nums(nums) {}

	vector<TreeNode*> solve()
	{
		result.clear();
		set = unordered_set<int>(nums.begin(), nums.end());
		dfs(root, true);
		return result;
	}

private:
	TreeNode* root;
	vector<int> nums;
	unordered_set<int> set;
	vector<TreeNode*> result;

	void dfs(TreeNode*& p, bool isParentDeleted)
	{
		if (p == NULL) return;
		bool found = set.count(p->val) > 0;
		dfs(p->left, found);
		dfs(p->right, found);
		if (found) p = NULL;
		if (!found && isParentDeleted) result.push_back(p);
	}
};

class Solution 
{
public:
	vector<TreeNode*> delNodes(TreeNode* root, vector<int>& nums) 
	{
		//return Solution1(root, nums).solve();
		return Solution2(root, nums).solve();
	}
};

bool check(vector<TreeNode*> a, vector<TreeNode*> b) 
{
	if (a.size() != b.size()) return false;
	for (TreeNode* p1 : a)
	{
		bool flag = false;
		for (TreeNode* p2 : b)
		{
			if (TreeEqual(p1, p2))
			{
				flag = true;
				break;
			}
		}
		if (!flag) return false;
	}
	return true;
}

int main()
{
	Cases<TreeNode*, vector<int>, vector<TreeNode*>> cases
	{
		{BuildTree({1,2,3,4,5,6,7}), {3,5}, {BuildTree({1,2,null,4}), BuildTree({6}), BuildTree({7})}},
		{BuildTree({1,null,2,null,3,null,4}), {3}, {BuildTree({1, null, 2}), BuildTree({4})}},
	};

	test(&Solution::delNodes, cases, check);

	return 0;
}