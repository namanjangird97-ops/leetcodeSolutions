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
    bool pathSum(TreeNode* root, int sum, int curr) {
        if(!root)
            return false;
        
        if(!root->left && !root->right)
            return ((curr+root->val) == sum);
        
        bool l = pathSum(root->left,  sum, curr+root->val);
        bool r = pathSum(root->right, sum, curr+root->val);
        return l||r;
    }
    bool hasPathSum(TreeNode* root, int sum) {
        return pathSum(root, sum, 0);
    }
};