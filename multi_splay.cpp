#include<bits/stdc++.h>
using namespace std;

// node structure for the tree
struct node {
    int key;
    int depth;
    int min_depth;
    bool is_root;
    node* lchild;
    node* rchild;
    node* parent;
};

// Function to find the minimum of two numbers
int min(int a, int b) {
    return (a < b) ? a : b;
}

// Global variable for the root of the tree
node* root;

// Function to display information about nodes in the tree
void Display(node* root) {
    cout << "Value: " << root->key << "\nis it the root: " << (root->is_root ? "True" : "False") << endl;

    if (root->parent == nullptr) {
        cout << "Parent: NULL" << endl << endl;
    } else {
        cout << "Parent: " << root->parent->key << endl << endl;
    }

    if (root->lchild != nullptr) {
        Display(root->lchild);
    }
    if (root->rchild != nullptr) {
        Display(root->rchild);
    }
}

// Function to create a new node
node* Createnode(int key, int depth, int min_depth, bool is_root) {
    node* ptr = new node;
    ptr->key = key;
    ptr->depth = depth;
    ptr->min_depth = min_depth;
    ptr->is_root = is_root;
    return ptr;
}

// Recursive function to build the tree
node* BuildTree(int start, int end, int depth, bool is_root) {
    if (start == end) {
        return nullptr;
    }

    int mid = (start + end) / 2;
    node* temp = Createnode(mid, depth, depth, is_root);
    temp->lchild = BuildTree(start, mid, depth + 1, false);
    temp->rchild = BuildTree(mid + 1, end, depth + 1, true);

    if (temp->lchild != nullptr) {
        temp->lchild->parent = temp;
    }
    if (temp->rchild != nullptr) {
        temp->rchild->parent = temp;
    }
    return temp;
}








int main() {
    cout << "Enter the number of nodes you want in the tree: ";
    int n;
    cin >> n;
    cout << "\nMultiSplayTree is Created !!!!" << endl << endl;
    root = BuildTree(1, n + 1, 0, true);

    int s = 0;
    while (s != 2) {
        cout << "1 -> Display the Tree\n2 -> Exit the Code\n\nEnter Your Choice: ";
        cin >> s;

        if (s == 1) {
            Display(root);
        } 
        else if (s == 2) {
            break;
        } else {
            cout << "Enter a valid Number Choice\n";
        }
    }

    return 0;
}
