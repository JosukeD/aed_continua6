class Solution {
    TreeNode* findLCA(TreeNode* root, TreeNode* node1, TreeNode* node2) {
        if (!root || root == node1 || root == node2) 
            return root;
        
        TreeNode* left = findLCA(root->left, node1, node2);
        TreeNode* right = findLCA(root->right, node1, node2);
        
        if (left && right) 
            return root;
        else if (left) 
            return left;
        else if (right) 
            return right;
        else 
            return NULL;
    }
    
public:
    TreeNode* lcaDeepestLeaves(TreeNode* root) {
        queue<TreeNode*> q;
        q.push(root);
        vector<TreeNode*> deepestNodes;

        while (!q.empty()) {
            int n = q.size();
            deepestNodes.clear();
            
            while (n--) {
                TreeNode* temp = q.front(); 
                q.pop();
                deepestNodes.push_back(temp);
                
                if (temp->left) 
                    q.push(temp->left);
                if (temp->right) 
                    q.push(temp->right);
            }
        }
        
        return findLCA(root, deepestNodes[0], deepestNodes[deepestNodes.size() - 1]);
    }
};