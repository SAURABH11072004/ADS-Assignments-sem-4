#include <iostream>
#include <string>
using namespace std;

class Node {
public:
    string key, value;
    int height;  // Track height of the node
    Node* left;
    Node* right;

    Node(string k, string v) {
        key = k;
        value = v;
        height = 1;  // New nodes start with height 1
        left = right = nullptr;
    }
};

class Dictionary {
private:
    Node* root;

    // Get the height of a node
    int getHeight(Node* node) {
        return (node == nullptr) ? 0 : node->height;
    }

    // Insert a word into the dictionary
    Node* insert(Node* node, string key, string value) {
        if (node == nullptr) return new Node(key, value);

        if (key < node->key)
            node->left = insert(node->left, key, value);
        else if (key > node->key)
            node->right = insert(node->right, key, value);
        else {
            node->value = value;  // Update meaning if word already exists
            return node;
        }

        // Update node height
        node->height = 1 + max(getHeight(node->left), getHeight(node->right));

        return node;
    }

    // Search for a word in the dictionary
    Node* search(Node* node, string key) {
        if (node == nullptr || node->key == key)
            return node;
        if (key < node->key)
            return search(node->left, key);
        return search(node->right, key);
    }

    // Find the node with the minimum value (used for deletion)
    Node* minValueNode(Node* node) {
        while (node->left != nullptr)
            node = node->left;
        return node;
    }

    // Delete a word from the dictionary
    Node* deleteNode(Node* node, string key) {
        if (node == nullptr) return node;

        if (key < node->key)
            node->left = deleteNode(node->left, key);
        else if (key > node->key)
            node->right = deleteNode(node->right, key);
        else {
            // Node with one or no child
            if (node->left == nullptr) {
                Node* temp = node->right;
                delete node;
                return temp;
            } else if (node->right == nullptr) {
                Node* temp = node->left;
                delete node;
                return temp;
            }
            // Node with two children: Get inorder successor
            Node* temp = minValueNode(node->right);
            node->key = temp->key;
            node->value = temp->value;
            node->right = deleteNode(node->right, temp->key);
        }

        // Update node height
        node->height = 1 + max(getHeight(node->left), getHeight(node->right));

        return node;
    }

    // Inorder traversal for displaying dictionary
    void inorder(Node* node) {
        if (node == nullptr) return;
        inorder(node->left);
        cout << node->key << " : " << node->value << endl;
        inorder(node->right);
    }

    // Mirror the BST (swap left and right)
    Node* mirror(Node* node) {
        if (node == nullptr) return nullptr;
        Node* temp = new Node(node->key, node->value);
        temp->left = mirror(node->right);
        temp->right = mirror(node->left);
        return temp;
    }

    // Copy the BST
    Node* copy(Node* node) {
        if (node == nullptr) return nullptr;
        Node* newNode = new Node(node->key, node->value);
        newNode->left = copy(node->left);
        newNode->right = copy(node->right);
        return newNode;
    }

    // Print nodes at a given level (used in level-wise traversal)
    void printLevel(Node* node, int level) {
        if (node == nullptr) return;
        if (level == 1)
            cout << node->key << " : " << node->value << endl;
        else {
            printLevel(node->left, level - 1);
            printLevel(node->right, level - 1);
        }
    }

    // Level-order traversal without queue
    void levelOrderTraversal(Node* node) {
        int h = getHeight(node);
        for (int i = 1; i <= h; i++) {
            printLevel(node, i);
        }
    }

public:
    Dictionary() { root = nullptr; }

    void insertWord(string key, string value) {
        root = insert(root, key, value);
        cout << "Word inserted successfully.\n";
    }

    void deleteWord(string key) {
        if (search(root, key) == nullptr) {
            cout << "Word not found! Cannot delete.\n";
            return;
        }
        root = deleteNode(root, key);
        cout << "Word deleted successfully.\n";
    }

    void searchWord(string key) {
        Node* result = search(root, key);
        if (result != nullptr) 
            cout << "Word Found! " << result->key << " : " << result->value << endl;
        else
            cout << "Word Not Found!\n";
    }

    void displayDictionary() {
        if (root == nullptr) {
            cout << "Dictionary is empty." << endl;
            return;
        }
        cout << "\nDictionary (Sorted Order):\n";
        inorder(root);
    }

    void displayMirrorDictionary() {
        if (root == nullptr) {
            cout << "Dictionary is empty." << endl;
            return;
        }
        Node* mirroredRoot = mirror(root);
        cout << "\nMirror Image of Dictionary:\n";
        inorder(mirroredRoot);
    }

    void createCopyDictionary() {
        if (root == nullptr) {
            cout << "Dictionary is empty. Can't show a copy of the dictionary." << endl;
            return;
        }
        Node* copiedRoot = copy(root);
        cout << "\nCopy of Dictionary:\n";
        inorder(copiedRoot);
    }

    void displayLevelWise() {
        if (root == nullptr) {
            cout << "Dictionary is empty. Can't Show Level-wise Dictionary." << endl;
            return;
        }
        cout << "\nDictionary (Level Wise):\n";
        levelOrderTraversal(root);
    }
};

// Main function with menu-driven program
int main() {
    Dictionary dict;
    int choice;
    string word, meaning;

    do {
        cout << "\nMenu:\n";
        cout << "1. Insert Word\n";
        cout << "2. Delete Word\n";
        cout << "3. Search Word\n";
        cout << "4. Display Dictionary\n";
        cout << "5. Mirror Image of Dictionary\n";
        cout << "6. Create a Copy of Dictionary\n";
        cout << "7. Display Dictionary Level-wise\n";
        cout << "8. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter Word: ";
                cin >> word;
                cout << "Enter Meaning: ";
                cin.ignore();
                getline(cin, meaning);
                dict.insertWord(word, meaning);
                break;

            case 2:
                cout << "Enter Word to Delete: ";
                cin >> word;
                dict.deleteWord(word);
                break;

            case 3:
                cout << "Enter Word to Search: ";
                cin >> word;
                dict.searchWord(word);
                break;

            case 4:
                dict.displayDictionary();
                break;

            case 5:
                dict.displayMirrorDictionary();
                break;

            case 6:
                dict.createCopyDictionary();
                break;

            case 7:
                dict.displayLevelWise();
                break;

            case 8:
                cout << "Exiting...\n";
                break;

            default:
                cout << "Invalid choice! Try again.\n";
        }
    } while (choice != 8);

    return 0;
}
