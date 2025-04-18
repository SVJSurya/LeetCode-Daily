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
    vector<TreeNode*> generateTrees(int n) {
        vector<vector<TreeNode*>> dp(n+1);
        dp[0].push_back(NULL);

        for(int i = 1;i<=n;i++) {
            for(int j=1;j<=i;j++) {
                int k = i-j;
                for(auto left : dp[j-1]) {
                    for(auto right : dp[k]) {
                        TreeNode* root = new TreeNode(j,left,clone(right,j));
                        dp[i].push_back(root);
                    }
                }
            }
        }
        return dp[n];
    }

private:
    TreeNode* clone(TreeNode* node, int rew) {
        if(node == NULL) {
            return NULL;
        }
        TreeNode* cloned = new TreeNode(node->val + rew);
        cloned->left = clone(node->left,rew);
        cloned->right = clone(node->right,rew);
        return cloned;
    }
};