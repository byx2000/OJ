// https://leetcode-cn.com/problems/path-sum-ii/

#include "../common/common.h"

class Solution1
{
public:
    Solution1(TreeNode* root, int sum) : root(root), sum(sum) {}

    vector<vector<int>> solve()
    {
        path.clear();
        paths.clear();
        search(root, sum);
        return paths;
    }

private:
    TreeNode* root;
    int sum;
    vector<int> path;
    vector<vector<int>> paths;

    void search(TreeNode* root, int sum)
    {
        if (root == NULL) return;

        if (root->left == NULL && root->right == NULL)
        {
            if (sum == root->val)
            {
                path.push_back(root->val);
                paths.push_back(path);
                path.pop_back();
            }
            return;
        }

        path.push_back(root->val);
        search(root->left, sum - root->val);
        
        search(root->right, sum - root->val);
        path.pop_back();
    }
};

class Solution 
{
public:
    vector<vector<int>> pathSum(TreeNode* root, int sum) 
    {
        return Solution1(root, sum).solve();
    }
};

int main()
{
    Cases<TreeNode*, int, vector<vector<int>>> cases
    {
        {BuildTree({ 5,4,8,11,null,13,4,7,2,null,null,5,1 }), 22, { {5,4,11,2}, {5,8,4,5} }},
    };

    test(&Solution::pathSum, cases, equivalent);

	return 0;
}