#include <iostream>
#include <queue>
#include <vector>
#include <unordered_map>

using namespace std;

// Definición de la estructura del nodo del árbol binario
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};

class Solution {
private:
    // Función para encontrar el ancestro común más bajo (LCA) de dos nodos en el árbol
    TreeNode* lca(TreeNode* root, TreeNode* a, TreeNode* b) {
        if (!root || root == a || root == b) return root;
        auto l = lca(root->left, a, b);
        auto r = lca(root->right, a, b);
        return l && r ? root : l ? l : r;
    }

public:
    // Función para encontrar el ancestro común más bajo (LCA) de las hojas más profundas del árbol
    TreeNode* lcaDeepestLeaves(TreeNode* root) {
        queue<TreeNode*> q;
        q.push(root);

        vector<TreeNode*> deepest_leaves;

        while (!q.empty()) {
            int n = q.size();
            deepest_leaves.clear();  // Reiniciar el vector para almacenar las hojas más profundas
            for (int i = 0; i < n; ++i) {
                TreeNode* temp = q.front();
                q.pop();
                deepest_leaves.push_back(temp);

                if (temp->left) q.push(temp->left);
                if (temp->right) q.push(temp->right);
            }
        }

        // Encontrar el LCA de las hojas más profundas (primer y último elemento del vector)
        return lca(root, deepest_leaves[0], deepest_leaves[deepest_leaves.size() - 1]);
    }
};

// Función auxiliar para crear un árbol binario a partir de una representación de vector
TreeNode* createTree(vector<int>& nodes, int idx) {
    if (idx >= nodes.size() || nodes[idx] == -1) {
        return nullptr;
    }

    TreeNode* root = new TreeNode(nodes[idx]);
    root->left = createTree(nodes, 2 * idx + 1);
    root->right = createTree(nodes, 2 * idx + 2);

    return root;
}

// Función para imprimir el árbol en formato de nivel
void printLevelOrder(TreeNode* root) {
    if (!root) return;

    queue<TreeNode*> q;
    q.push(root);

    while (!q.empty()) {
        int n = q.size();
        for (int i = 0; i < n; ++i) {
            TreeNode* node = q.front();
            q.pop();
            if (node) {
                cout << node->val << " ";
                q.push(node->left);
                q.push(node->right);
            } else {
                cout << "null ";
            }
        }
    }
}

int main() {
    // Entrada de ejemplo: root = [3,5,1,6,2,0,8,null,null,7,4]
    vector<int> nodes = {3, 5, 1, 6, 2, 0, 8, -1, -1, 7, 4};
    TreeNode* root = createTree(nodes, 0);

    Solution solution;
    TreeNode* result = solution.lcaDeepestLeaves(root);

    cout << "Output: ";
    printLevelOrder(result);  // Imprimir el resultado en formato de nivel

    return 0;
}
