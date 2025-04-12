/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    int maxpdown(TreeNode* root , int& maxpath) {
        if(!root) return 0;
        int l = max(0, maxpdown(root->left, maxpath));
        int r = max(0, maxpdown(root->right, maxpath));
        maxpath = max(maxpath, l+r+root->val);
        return max(l,r) + root->val;
    }

    int maxPathSum(TreeNode* root) {
        int maxpath = INT_MIN;
        maxpdown(root,maxpath);
        return maxpath;
    }
};