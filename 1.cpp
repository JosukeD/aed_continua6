#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// Definición de un nodo de árbol binario
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// Función para insertar un nodo en un árbol binario desde un vector de enteros (usando BFS)
TreeNode* insertLevelOrder(vector<int>& vec, TreeNode* root, int i, int n) {
    // Base case para finalizar la inserción
    if (i < n && vec[i] != NULL) {
        TreeNode* temp = new TreeNode(vec[i]);
        root = temp;

        // Inserta nodos izquierdos
        root->left = insertLevelOrder(vec, root->left, 2 * i + 1, n);

        // Inserta nodos derechos
        root->right = insertLevelOrder(vec, root->right, 2 * i + 2, n);
    }
    return root;
}

// Función para recorrer el árbol en orden de nivel y devolver los valores por nivel
vector<vector<int>> levelOrder(TreeNode* root) {
    vector<vector<int>> result;
    
    if (root == nullptr) return result;
    
    queue<TreeNode*> q;
    q.push(root);
    
    while (!q.empty()) {
        int levelSize = q.size();
        vector<int> currentLevel;
        
        for (int i = 0; i < levelSize; ++i) {
            TreeNode* node = q.front();
            q.pop();
            
            currentLevel.push_back(node->val);
            
            if (node->left) q.push(node->left);
            if (node->right) q.push(node->right);
        }
        
        result.push_back(currentLevel);
    }
    
    return result;
}

// Función para imprimir el resultado en un formato adecuado
void printLevelOrderResult(const vector<vector<int>>& result) {
    cout << "[";
    for (int i = 0; i < result.size(); ++i) {
        cout << "[";
        for (int j = 0; j < result[i].size(); ++j) {
            cout << result[i][j];
            if (j < result[i].size() - 1) cout << ",";
        }
        cout << "]";
        if (i < result.size() - 1) cout << ",";
    }
    cout << "]" << endl;
}

// Función main para probar el código
int main() {
    // Ejemplo de entrada: [3,9,20,null,null,15,7]
    vector<int> nodes = {3, 9, 20, NULL, NULL, 15, 7};
    
    TreeNode* root = nullptr;
    int n = nodes.size();
    
    // Construye el árbol binario desde el vector de enteros
    root = insertLevelOrder(nodes, root, 0, n);
    
    // Obtiene el recorrido en orden de nivel
    vector<vector<int>> result = levelOrder(root);
    
    // Imprime el resultado utilizando la función de impresión
    printLevelOrderResult(result);
    
    return 0;
}
