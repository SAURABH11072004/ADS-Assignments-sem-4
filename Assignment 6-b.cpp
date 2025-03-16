#include <iostream>
#include <string>
using namespace std;

enum Color { RED, BLACK };

class Directory {
public:
    string name;
    Directory *left, *right, *parent;
    Color color;

    Directory(string a) {
        name = name;
        left = right = parent = nullptr;
        color = RED;
    }
};

class FileSystem {
private:
    Directory* root;
    Directory* NIL;

    void leftRotate(Directory* x) {
        Directory* y = x->right;
        x->right = y->left;
        if (y->left != NIL)
            y->left->parent = x;
        y->parent = x->parent;
        if (x->parent == nullptr)
            root = y;
        else if (x == x->parent->left)
            x->parent->left = y;
        else
            x->parent->right = y;
        y->left = x;
        x->parent = y;
    }

    void rightRotate(Directory* y) {
        Directory* x = y->left;
        y->left = x->right;
        if (x->right != NIL)
            x->right->parent = y;
        x->parent = y->parent;
        if (y->parent == nullptr)
            root = x;
        else if (y == y->parent->left)
            y->parent->left = x;
        else
            y->parent->right = x;
        x->right = y;
        y->parent = x;
    }

    void insertFixup(Directory* z) {
        while (z->parent && z->parent->color == RED) {
            if (z->parent == z->parent->parent->left) {
                Directory* y = z->parent->parent->right;
                if (y->color == RED) {
                    z->parent->color = BLACK;
                    y->color = BLACK;
                    z->parent->parent->color = RED;
                    z = z->parent->parent;
                } else {
                    if (z == z->parent->right) {
                        z = z->parent;
                        leftRotate(z);
                    }
                    z->parent->color = BLACK;
                    z->parent->parent->color = RED;
                    rightRotate(z->parent->parent);
                }
            } else {
                Directory* y = z->parent->parent->left;
                if (y->color == RED) {
                    z->parent->color = BLACK;
                    y->color = BLACK;
                    z->parent->parent->color = RED;
                    z = z->parent->parent;
                } else {
                    if (z == z->parent->left) {
                        z = z->parent;
                        rightRotate(z);
                    }
                    z->parent->color = BLACK;
                    z->parent->parent->color = RED;
                    leftRotate(z->parent->parent);
                }
            }
        }
        root->color = BLACK;
    }

    void inorder(Directory* node) {
        if (node != NIL) {
            inorder(node->left);
            cout << node->name << " ";
            inorder(node->right);
        }
    }

    Directory* minValueNode(Directory* node) {
        while (node->left != NIL)
            node = node->left;
        return node;
    }

    Directory* deleteNode(Directory* root, string name) {
        if (root == NIL)
            return root;

        if (name < root->name)
            root->left = deleteNode(root->left, name);
        else if (name > root->name)
            root->right = deleteNode(root->right, name);
        else {
            if (root->left == NIL || root->right == NIL) {
                Directory* temp = root->left ? root->left : root->right;
                if (temp == NIL) {
                    temp = root;
                    root = NIL;
                } else
                    *root = *temp;
                delete temp;
            } else {
                Directory* temp = minValueNode(root->right);
                root->name = temp->name;
                root->right = deleteNode(root->right, temp->name);
            }
        }
        return root;
    }

public:
    FileSystem() {
        NIL = new Directory("NIL");
        NIL->color = BLACK;
        root = NIL;
    }

    void insert(string name) {
        Directory* newDir = new Directory(name);
        newDir->left = newDir->right = NIL;

        Directory* y = nullptr;
        Directory* x = root;

        while (x != NIL) {
            y = x;
            if (newDir->name < x->name)
                x = x->left;
            else
                x = x->right;
        }

        newDir->parent = y;
        if (y == nullptr)
            root = newDir;
        else if (newDir->name < y->name)
            y->left = newDir;
        else
            y->right = newDir;

        newDir->color = RED;
        insertFixup(newDir);
    }

    void display() {
        if (root == NIL)
            cout << "File System is empty!\n";
        else {
            cout << "File System Structure: \n";
            inorder(root);
            cout << endl;
        }
    }

    void remove(string name) {
        root = deleteNode(root, name);
    }
};

int main() {
    FileSystem fs;
    int choice;
    string name;

    do {
        cout << "\nFile System Menu\n";
        cout << "1. Insert Directory\n";
        cout << "2. Delete Directory\n";
        cout << "3. Display File System\n";
        cout << "4. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter directory name: ";
                cin >> name;
                fs.insert(name);
                break;
            case 2:
                cout << "Enter directory name to delete: ";
                cin >> name;
                fs.remove(name);
                break;
            case 3:
                fs.display();
                break;
            case 4:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice, try again!\n";
        }
    } while (choice != 4);

    return 0;
}
