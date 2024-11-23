#include <iostream>
#include <vector>
#include <queue>
#include <iomanip>
#include <concepts>
#include <format>

using namespace std;

// Concept to ensure the type is numeric
template<typename T>
concept Numeric = std::integral<T> || std::floating_point<T>;

// Node structure for the binary tree
template<Numeric T>
struct TreeNode {
    T value;
    TreeNode* left;
    TreeNode* right;

    TreeNode(T val) : value(val), left(nullptr), right(nullptr) {}
};

// Class for the binary tree
template<Numeric T>
class BinaryTree {
public:
    BinaryTree() : root(nullptr) {}

    // Function to add a value to the tree
    void add(T value) {
        root = addRecursive(root, value);
    }

    // Function to perform in-order traversal and return sorted elements
    vector<T> sort() {
        vector<T> sortedElements;
        inOrderTraversal(root, sortedElements);
        return sortedElements;
    }

    // Function to pretty print the tree
    void prettyPrint() {
        if (!root) {
            cout << "Tree is empty." << endl;
            return;
        }

        int depth = getDepth(root);
        int width = (1 << depth) - 1; // 2^depth - 1
        vector<vector<string>> levels(depth, vector<string>(width, " "));

        fillLevels(root, levels, 0, 0, width - 1);

        for (const auto& level : levels) {
            for (const auto& node : level) {
                cout << std::format("{:>6.4}", node);
            }
            cout << endl;
        }
    }

    // Function to optimize (balance) the tree
    void optimize() {
        auto sortedElements = sort();
        root = buildBalancedTree(sortedElements, 0, sortedElements.size() - 1);
    }

    // Function to get the depth of the tree
    int getDepth() {
        return getDepth(root);
    }

private:
    TreeNode<T>* root;

    // Helper function to add a value to the tree recursively
    TreeNode<T>* addRecursive(TreeNode<T>* node, T value) {
        if (!node) {
            return new TreeNode<T>(value);
        }

        if (value < node->value) {
            node->left = addRecursive(node->left, value);
        } else {
            node->right = addRecursive(node->right, value);
        }

        return node;
    }

    // Helper function for in-order traversal
    void inOrderTraversal(TreeNode<T>* node, vector<T>& sortedElements) {
        if (!node) {
            return;
        }

        inOrderTraversal(node->left, sortedElements);
        sortedElements.push_back(node->value);
        inOrderTraversal(node->right, sortedElements);
    }

    // Helper function to get the depth of the tree
    int getDepth(TreeNode<T>* node) {
        if (!node) {
            return 0;
        }

        return 1 + max(getDepth(node->left), getDepth(node->right));
    }

    // Helper function to fill levels for pretty printing
    void fillLevels(TreeNode<T>* node, vector<vector<string>>& levels, int depth, int left, int right) {
        if (!node) {
            return;
        }

        int mid = (left + right) / 2;
        levels[depth][mid] = to_string(node->value);

        fillLevels(node->left, levels, depth + 1, left, mid - 1);
        fillLevels(node->right, levels, depth + 1, mid + 1, right);
    }

    // Helper function to build a balanced tree from sorted elements
    TreeNode<T>* buildBalancedTree(const vector<T>& sortedElements, int start, int end) {
        if (start > end) {
            return nullptr;
        }

        int mid = (start + end) / 2;
        TreeNode<T>* node = new TreeNode<T>(sortedElements[mid]);
        node->left = buildBalancedTree(sortedElements, start, mid - 1);
        node->right = buildBalancedTree(sortedElements, mid + 1, end);

        return node;
    }
};

int main() {
    BinaryTree<int> intTree;
    intTree.add(3);
    intTree.add(2);
    intTree.add(1);
    intTree.add(5);
    intTree.add(4);
    intTree.add(7);
    intTree.add(6);

    cout << "Sorted elements (int): ";
    auto sortedIntElements = intTree.sort();
    for (int val : sortedIntElements) {
        cout << val << " ";
    }
    cout << endl;

    cout << "Pretty print of the int tree:" << endl;
    intTree.prettyPrint();

    cout << "Depth of the int tree: " << intTree.getDepth() << endl;

    cout << "Optimizing the int tree..." << endl;
    intTree.optimize();

    cout << "Depth of the optimized int tree: " << intTree.getDepth() << endl;

    cout << "Pretty print of the optimized int tree:" << endl;
    intTree.prettyPrint();

    BinaryTree<double> doubleTree;
    doubleTree.add(3.52);
    doubleTree.add(2.14);
    doubleTree.add(1.81);
    doubleTree.add(5.66);
    doubleTree.add(4.45);
    doubleTree.add(7.23);
    doubleTree.add(6.98);

    cout << "Sorted elements (double): ";
    auto sortedDoubleElements = doubleTree.sort();
    for (double val : sortedDoubleElements) {
        cout << val << " ";
    }
    cout << endl;

    cout << "Pretty print of the double tree:" << endl;
    doubleTree.prettyPrint();

    cout << "Depth of the double tree: " << doubleTree.getDepth() << endl;

    cout << "Optimizing the double tree..." << endl;
    doubleTree.optimize();

    cout << "Pretty print of the optimized double tree:" << endl;
    doubleTree.prettyPrint();

    cout << "Depth of the optimized double tree: " << doubleTree.getDepth() << endl;

    return 0;
}