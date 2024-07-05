#include<bits/stdc++.h>
using namespace std;

// Node structure for the tree
struct TreeNode {
    int value;
    int depth;
    int min_depth;
    bool is_root;
    TreeNode* left_child;
    TreeNode* right_child;
    TreeNode* parent;
};

// Global variable for the root of the tree
TreeNode* root;

// Function to display information 
void Display(TreeNode* root) {
    cout << "Value: " << root->value << "\nIs Root: " << (root->is_root ? "True" : "False") << endl;

    if (root->parent == nullptr) {
        cout << "Parent: NULL" << endl << endl;
    } else {
        cout << "Parent: " << root->parent->value << endl << endl;
    }

    if (root->left_child != nullptr) {
        Display(root->left_child);
    }
    if (root->right_child != nullptr) {
        Display(root->right_child);
    }
}

// Function to create a new node
TreeNode* CreateNode(int value, int depth, int min_depth, bool is_root) {
    TreeNode* node = new TreeNode;
    node->value = value;
    node->depth = depth;
    node->min_depth = min_depth;
    node->is_root = is_root;
    node->left_child = nullptr;
    node->right_child = nullptr;
    node->parent = nullptr;
    return node;
}

// Recursive function to build the tree
TreeNode* BuildTree(int start, int end, int depth, bool is_root) {
    if (start == end) {
        return nullptr;
    }

    int mid = (start + end) / 2;
    TreeNode* node = CreateNode(mid, depth, depth, is_root);
    node->left_child = BuildTree(start, mid, depth + 1, false);
    node->right_child = BuildTree(mid + 1, end, depth + 1, true);

    if (node->left_child != nullptr) {
        node->left_child->parent = node;
    }
    if (node->right_child != nullptr) {
        node->right_child->parent = node;
    }
    return node;
}

// Function to perform rotation
void Rotate(TreeNode* node) {
    TreeNode* parent = node->parent;
    if (parent->is_root) {
        parent->is_root = false;
        node->is_root = true;
    }
    if (root == parent) {
        root = node;
    }
    if (parent->parent != nullptr) {
        if (parent->parent->left_child == parent) {
            parent->parent->left_child = node;
        } else {
            parent->parent->right_child = node;
        }
    }
    node->parent = parent->parent;
    if (parent->right_child == node) {
        parent->right_child = node->left_child;
        if (node->left_child != nullptr) {
            node->left_child->parent = parent;
        }
        node->left_child = parent;
    } else {
        parent->left_child = node->right_child;
        if (node->right_child != nullptr) {
            node->right_child->parent = parent;
        }
        node->right_child = parent;
    }
    parent->parent = node;
    if (parent->left_child != nullptr) {
        parent->min_depth = min(parent->min_depth, parent->left_child->min_depth);
    }
    if (parent->right_child != nullptr) {
        parent->min_depth = min(parent->min_depth, parent->right_child->min_depth);
    }
}

// Splay function
void Splay(TreeNode* node, TreeNode* top) {
    TreeNode* parent;
    TreeNode* grandparent;
    while (!(node->is_root || node->parent == top)) {
        parent = node->parent;
        if (!(parent->is_root || parent->parent == top)) {
            grandparent = parent->parent;
            if ((grandparent->left_child == parent && parent->left_child == node) ||
                (grandparent->right_child == parent && parent->right_child == node)) {
                Rotate(parent);
            } else {
                Rotate(node);
            }
        }
        Rotate(node);
    }
}

// Reference parent function
TreeNode* ReferenceParent(TreeNode* node, bool flag) {
    TreeNode* temp = nullptr;
    if (!flag) {
        temp = node->left_child;
    } else {
        temp = node->right_child;
    }
    while (true) {
        if (!flag) {
            if (temp->right_child != nullptr && temp->right_child->min_depth < node->depth) {
                temp = temp->right_child;
            } else if (temp->left_child != nullptr && temp->left_child->min_depth < node->depth) {
                temp = temp->left_child;
            } else {
                break;
            }
        } else {
            if (temp->left_child && temp->left_child->min_depth < node->depth) {
                temp = temp->left_child;
            } else if (temp->right_child && temp->right_child->min_depth < node->depth) {
                temp = temp->right_child;
            } else {
                break;
            }
        }
    }
    return temp;
}

// Switch path function
void SwitchPath(TreeNode* node) {
    TreeNode* temp;
    if (node->left_child != nullptr) {
        if (node->left_child->min_depth > node->depth) {
            node->left_child->is_root = !(node->left_child->is_root);
        } else {
            temp = ReferenceParent(node, false);
            Splay(temp, node);
            if (temp->right_child != nullptr) {
                temp->right_child->is_root = !(temp->right_child->is_root);
            }
        }
    }
    if (node->right_child != nullptr) {
        if (node->right_child->min_depth > node->depth) {
            node->right_child->is_root = !(node->right_child->is_root);
        } else {
            temp = ReferenceParent(node, true);
            Splay(temp, node);
            if (temp->left_child != nullptr) {
                temp->left_child->is_root = !(temp->left_child->is_root);
            }
        }
    }
}

// Multi-splay algorithm
void MultiSplayAlgo(TreeNode* node) {
    TreeNode* temp = node;
    while (temp->parent != nullptr) {
        TreeNode* parent = temp->parent;
        if (temp->is_root) {
            Splay(parent, nullptr);
            SwitchPath(parent);
        }
        temp = parent;
    }
    Splay(node, nullptr);
}

// Search function
void Search(int key) {
    TreeNode* node = root;
    TreeNode* prev = root;
    
    while (node != nullptr && node->value != key) {
        prev = node;
        if (key < node->value) {
            node = node->left_child;
        } else {
            node = node->right_child;
        }
    }
    if (node == nullptr) {
        MultiSplayAlgo(prev);
    } else {
        MultiSplayAlgo(node);
    }
}

int main() {
    cout << "Enter the number of nodes you want in the tree: ";
    int n;
    cin >> n;
    cout << "\nMultiSplayTree is Created." << endl << endl;
    root = BuildTree(1, n + 1, 0, true);

    int choice = 0;
    while (choice != 3) {
        cout << "1 -> Display the Tree\n2 -> Search an Element\n3 -> Exit the Code\n\nEnter Your Choice: ";
        cin >> choice;

        if (choice == 1) {
            Display(root);
        } else if (choice == 2) {
            int key;
            cout << "What is the element you want to search: ";
            cin >> key;
            Search(key);
        } else if (choice == 3) {
            break;
        } else {
            cout << "Give valid Number Choice please\n";
        }
    }

    return 0;
}

