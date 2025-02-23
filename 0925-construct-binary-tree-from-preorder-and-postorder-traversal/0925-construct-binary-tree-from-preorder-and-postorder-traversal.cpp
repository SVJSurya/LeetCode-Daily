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
private:
    TreeNode* construct(int &pre,int &post,vector<int>& preorder, vector<int>& postorder) {
        TreeNode* root = new TreeNode(preorder[pre]);
        pre++;

        if(root->val != postorder[post]) {
            root->left = construct(pre, post, preorder , postorder);
        }
        if(root->val != postorder[post]) {
            root->right = construct(pre,post,preorder,postorder);
        }
        post++;

        return root;
    }
public:
    TreeNode* constructFromPrePost(vector<int>& preorder, vector<int>& postorder) {
        int pre = 0;
        int post = 0;
        return construct(pre,post,preorder,postorder);
    }
};