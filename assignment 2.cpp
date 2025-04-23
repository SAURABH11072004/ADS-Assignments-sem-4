#include <iostream>
using namespace std;

// Player class (Node of AVL Tree)
class Player {
public:
    int player_id;
    int score;
    Player* left;
    Player* right;
    int height;

    Player(int id, int sc) {
        player_id = id;
        score = sc;
        left = right = nullptr;
        height = 1;
    }
};

// Multiplayer Game class (AVL Tree Implementation)
class MultiplayerGame {
private:
    Player* root;

    // Get height of a node
    int getHeight(Player* node) {
        return (node == nullptr) ? 0 : node->height;
    }

    // Get balance factor of a node
    int getBalanceFactor(Player* node) {
        return (node == nullptr) ? 0 : getHeight(node->left) - getHeight(node->right);
    }

    // Right Rotation
    Player* rotateRight(Player* y) {
        Player* x = y->left;
        y->left = x->right;
        x->right = y;

        y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
        x->height = max(getHeight(x->left), getHeight(x->right)) + 1;

        return x;
    }

    // Left Rotation
    Player* rotateLeft(Player* x) {
        Player* y = x->right;
        x->right = y->left;
        y->left = x;

        x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
        y->height = max(getHeight(y->left), getHeight(y->right)) + 1;

        return y;
    }

    // Insert a player into the AVL tree
    Player* insertPlayer(Player* node, int id, int score) {
        if (node == nullptr)
            return new Player(id, score);

        if (score < node->score)
            node->left = insertPlayer(node->left, id, score);
        else
            node->right = insertPlayer(node->right, id, score);

        node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
        int balance = getBalanceFactor(node);

        if (balance > 1 && score < node->left->score)
            return rotateRight(node);
        if (balance < -1 && score > node->right->score)
            return rotateLeft(node);
        if (balance > 1 && score > node->left->score) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }
        if (balance < -1 && score < node->right->score) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        return node;
    }

    // Check for duplicate ID before insertion
    bool isDuplicateID(Player* node, int id) {
        if (node == nullptr) return false;
        if (node->player_id == id) return true;
        return isDuplicateID(node->left, id) || isDuplicateID(node->right, id);
    }

    // Find the node with minimum value
    Player* minValueNode(Player* node) {
        Player* current = node;
        while (current->left != nullptr)
            current = current->left;
        return current;
    }

    // Remove a player from the AVL tree
    Player* removePlayer(Player* root, int id) {
        if (root == nullptr) return root;

        if (id < root->player_id)
            root->left = removePlayer(root->left, id);
        else if (id > root->player_id)
            root->right = removePlayer(root->right, id);
        else {
         
            if (root->left == nullptr) {
                Player* temp = root->right;
                delete root;
                return temp;
            }
            else if (root->right == nullptr) {
                Player* temp = root->left;
                delete root;
                return temp;
            }
            Player* temp = minValueNode(root->right);
            root->player_id = temp->player_id;
            root->score = temp->score;
            root->right = removePlayer(root->right, temp->player_id);
        }

        root->height = max(getHeight(root->left), getHeight(root->right)) + 1;
        int balance = getBalanceFactor(root);

        if (balance > 1 && getBalanceFactor(root->left) >= 0)
            return rotateRight(root);
        if (balance > 1 && getBalanceFactor(root->left) < 0) {
            root->left = rotateLeft(root->left);
            return rotateRight(root);
        }
        if (balance < -1 && getBalanceFactor(root->right) <= 0)
            return rotateLeft(root);
        if (balance < -1 && getBalanceFactor(root->right) > 0) {
            root->right = rotateRight(root->right);
            return rotateLeft(root);
        }

        return root;
    }

    // Display leaderboard in descending order (reverse inorder)
    void displayLeaderboard(Player* node) {
        if (node == nullptr) return;
        displayLeaderboard(node->right);
        cout << "Player ID: " << node->player_id << " | Score: " << node->score << endl;
        displayLeaderboard(node->left);
    }

public:
    MultiplayerGame() {
        root = nullptr;
    }

    void registerPlayer(int id, int score) {
        if (isDuplicateID(root, id)) {
            cout << "Player ID already exists! Try again.\n";
            return;
        }
        root = insertPlayer(root, id, score);
        cout << "Player registered successfully.\n";
    }

    void showLeaderboard() {
        cout << "\nLeaderboard (Sorted by Score Descending):\n";
        displayLeaderboard(root);
    }

    void removePlayerByID(int id) {
        root = removePlayer(root, id);
        cout << "Player removed successfully.\n";
    }
};

// Main function
int main() {
    MultiplayerGame game;
    int choice, player_id, score;

    do {
        cout << "\n1. Register Player\n2. Display Leaderboard\n3. Remove Player\n4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter Player ID: ";
                cin >> player_id;
                cout << "Enter Player Score: ";
                cin >> score;
                game.registerPlayer(player_id, score);
                break;
            case 2:
                game.showLeaderboard();
                break;
            case 3:
                cout << "Enter Player ID to remove: ";
                cin >> player_id;
                game.removePlayerByID(player_id);
                break;
            case 4:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice! Try again.\n";
        }
    } while (choice != 4);

    return 0;
}
