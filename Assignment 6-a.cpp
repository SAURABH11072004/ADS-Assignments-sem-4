#include <iostream>
#include <queue>
using namespace std;

class BTreeNode {
public:
    int *keys;
    BTreeNode **children;
    int n;
    bool leaf;

    BTreeNode(bool isLeaf) {
        keys = new int[3];
        children = new BTreeNode*[4];
        n = 0;
        leaf = isLeaf;
        for (int i = 0; i < 4; i++) {
            children[i] = nullptr;
        }
    }

    ~BTreeNode() {
        delete[] keys;
        delete[] children;
    }
};

struct SplitResult {
    bool hasSplit;
    int promotedKey;
    BTreeNode* rightChild;

    SplitResult() : hasSplit(false), promotedKey(0), rightChild(nullptr) {}
};

class BTree {
    BTreeNode *root;
    int order;

public:
    BTree() {
        root = nullptr;
        order = 3;
    }

    void insert(int key) {
        if (root == nullptr) {
            root = new BTreeNode(true);
            root->keys[0] = key;
            root->n = 1;
        } else {
            SplitResult result = insertHelper(root, key);
            if (result.hasSplit) {
                BTreeNode* newRoot = new BTreeNode(false);
                newRoot->children[0] = root;
                newRoot->keys[0] = result.promotedKey;
                newRoot->children[1] = result.rightChild;
                newRoot->n = 1;
                root = newRoot;
            }
        }
    }

    void deleteKey(int key) {
        if (root == nullptr) {
            cout << "Tree is empty\n";
            return;
        }

        deleteHelper(root, key);

        if (root->n == 0) {
            BTreeNode* tmp = root;
            if (root->leaf) {
                root = nullptr;
            } else {
                root = root->children[0];
            }
            delete tmp;
        }
    }

    void levelOrderDisplay() {
        if (root == nullptr) {
            cout << "Tree is empty\n";
            return;
        }

        queue<BTreeNode*> q;
        q.push(root);

        while (!q.empty()) {
            int levelSize = q.size();

            for (int i = 0; i < levelSize; i++) {
                BTreeNode* current = q.front();
                q.pop();

                cout << "[";
                for (int j = 0; j < current->n; j++) {
                    cout << current->keys[j];
                    if (j < current->n - 1) {
                        cout << ", ";
                    }
                }
                cout << "] ";

                if (!current->leaf) {
                    for (int j = 0; j <= current->n; j++) {
                        if (current->children[j] != nullptr) {
                            q.push(current->children[j]);
                        }
                    }
                }
            }
            cout << endl;
        }
    }

private:
    SplitResult insertHelper(BTreeNode* node, int key) {
        SplitResult result;

        if (node->leaf) {
            int i = node->n - 1;
            while (i >= 0 && key < node->keys[i]) {
                node->keys[i + 1] = node->keys[i];
                i--;
            }
            node->keys[i + 1] = key;
            node->n += 1;

            if (node->n == order) {
                BTreeNode* rightNode = new BTreeNode(true);
                int promoteKey = node->keys[1];
                node->n = 1;
                rightNode->keys[0] = node->keys[2];
                rightNode->n = 1;
                result.hasSplit = true;
                result.promotedKey = promoteKey;
                result.rightChild = rightNode;
            }
        } else {
            int i = 0;
            while (i < node->n && key >= node->keys[i]) {
                i++;
            }

            SplitResult childResult = insertHelper(node->children[i], key);

            if (childResult.hasSplit) {
                int j = node->n - 1;
                while (j >= i) {
                    node->keys[j + 1] = node->keys[j];
                    j--;
                }
                node->keys[i] = childResult.promotedKey;

                for (int j = node->n; j >= i + 1; j--) {
                    node->children[j + 1] = node->children[j];
                }
                node->children[i + 1] = childResult.rightChild;
                node->n += 1;

                if (node->n == order) {
                    BTreeNode* rightNode = new BTreeNode(false);
                    int promoteKey = node->keys[1];
                    rightNode->keys[0] = node->keys[2];
                    rightNode->n = 1;
                    rightNode->children[0] = node->children[2];
                    rightNode->children[1] = node->children[3];
                    node->n = 1;
                    result.hasSplit = true;
                    result.promotedKey = promoteKey;
                    result.rightChild = rightNode;
                }
            }
        }

        return result;
    }

    void deleteHelper(BTreeNode* node, int key) {
        int idx = 0;
        while (idx < node->n && node->keys[idx] < key) {
            idx++;
        }

        if (idx < node->n && node->keys[idx] == key) {
            if (node->leaf) {
                removeFromLeaf(node, idx);
            } else {
                removeFromInternal(node, idx);
            }
        } else {
            if (node->leaf) {
                cout << "Key " << key << " not found.\n";
                return;
            }

            bool flag = (idx == node->n);

            if (node->children[idx]->n < 1) {
                fill(node, idx);
                if (flag && idx > node->n) {
                    idx--;
                }
            }

            if (flag && idx > node->n) {
                deleteHelper(node->children[idx - 1], key);
            } else {
                deleteHelper(node->children[idx], key);
            }

            if (node->children[idx]->n < 1) {
                fill(node, idx);
            }
        }
    }

    void removeFromLeaf(BTreeNode* node, int idx) {
        for (int i = idx + 1; i < node->n; i++) {
            node->keys[i - 1] = node->keys[i];
        }
        node->n--;
    }

    void removeFromInternal(BTreeNode* node, int idx) {
        int key = node->keys[idx];

        if (node->children[idx]->n >= 1) {
            int predecessor = getPredecessor(node, idx);
            node->keys[idx] = predecessor;
            deleteHelper(node->children[idx], predecessor);
        } else if (node->children[idx + 1]->n >= 1) {
            int successor = getSuccessor(node, idx);
            node->keys[idx] = successor;
            deleteHelper(node->children[idx + 1], successor);
        } else {
            merge(node, idx);
            deleteHelper(node->children[idx], key);
        }
    }

    int getPredecessor(BTreeNode* node, int idx) {
        BTreeNode* current = node->children[idx];
        while (!current->leaf) {
            current = current->children[current->n];
        }
        return current->keys[current->n - 1];
    }

    int getSuccessor(BTreeNode* node, int idx) {
        BTreeNode* current = node->children[idx + 1];
        while (!current->leaf) {
            current = current->children[0];
        }
        return current->keys[0];
    }

    void fill(BTreeNode* node, int idx) {
        if (idx != 0 && node->children[idx - 1]->n > 1) {
            borrowFromPrev(node, idx);
        } else if (idx != node->n && node->children[idx + 1]->n > 1) {
            borrowFromNext(node, idx);
        } else {
            if (idx != node->n) {
                merge(node, idx);
            } else {
                merge(node, idx - 1);
            }
        }
    }

    void borrowFromPrev(BTreeNode* node, int idx) {
        BTreeNode* child = node->children[idx];
        BTreeNode* sibling = node->children[idx - 1];

        for (int i = child->n - 1; i >= 0; i--) {
            child->keys[i + 1] = child->keys[i];
        }

        if (!child->leaf) {
            for (int i = child->n; i >= 0; i--) {
                child->children[i + 1] = child->children[i];
            }
        }

        child->keys[0] = node->keys[idx - 1];

        if (!child->leaf) {
            child->children[0] = sibling->children[sibling->n];
        }

        node->keys[idx - 1] = sibling->keys[sibling->n - 1];

        child->n += 1;
        sibling->n -= 1;
    }

    void borrowFromNext(BTreeNode* node, int idx) {
        BTreeNode* child = node->children[idx];
        BTreeNode* sibling = node->children[idx + 1];

        child->keys[child->n] = node->keys[idx];

        if (!child->leaf) {
            child->children[child->n + 1] = sibling->children[0];
        }

        node->keys[idx] = sibling->keys[0];

        for (int i = 1; i < sibling->n; i++) {
            sibling->keys[i - 1] = sibling->keys[i];
        }

        if (!sibling->leaf) {
            for (int i = 1; i <= sibling->n; i++) {
                sibling->children[i - 1] = sibling->children[i];
            }
        }

        child->n += 1;
        sibling->n -= 1;
    }

    void merge(BTreeNode* node, int idx) {
        BTreeNode* child = node->children[idx];
        BTreeNode* sibling = node->children[idx + 1];

        child->keys[child->n] = node->keys[idx];
        child->n++;

        for (int i = 0; i < sibling->n; i++) {
            child->keys[child->n + i] = sibling->keys[i];
        }

        if (!child->leaf) {
            for (int i = 0; i <= sibling->n; i++) {
                child->children[child->n + i] = sibling->children[i];
            }
        }

        child->n += sibling->n;

        for (int i = idx + 1; i < node->n; i++) {
            node->keys[i - 1] = node->keys[i];
        }

        for (int i = idx + 2; i <= node->n; i++) {
            node->children[i - 1] = node->children[i];
        }

        node->n--;

        delete sibling;
    }
};

int main() {
    BTree t;
    int choice, key;

    do {
        cout << "\n1. Insert\n2. Delete\n3. Level Order Display\n4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter key to insert: ";
                cin >> key;
                t.insert(key);
                break;
            case 2:
                cout << "Enter key to delete: ";
                cin >> key;
                t.deleteKey(key);
                break;
            case 3:
                cout << "Level order display:\n";
                t.levelOrderDisplay();
                break;
            case 4:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice\n";
        }
    } while (choice != 4);

    return 0;
}
