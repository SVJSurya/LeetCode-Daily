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
    TreeNode* mergeTrees(TreeNode* root1, TreeNode* root2) {
        if(!root1) return root2;
        if(!root2) return root1;

        stack<pair<TreeNode* , TreeNode*>> st;

        st.push({root1,root2});

        while(!st.empty()) {
            pair<TreeNode*, TreeNode*> n = st.top();
            st.pop();

            if(n.first == nullptr || n.second == nullptr) continue;

            n.first->val += n.second->val;

            if(!n.first->left) n.first->left = n.second->left;
            else {
                st.push({n.first->left, n.second->left});
            }
            if(!n.first->right) n.first->right = n.second->right;
            else {
                st.push({n.first->right, n.second->right});
            }
        }

        return root1;
    }
};