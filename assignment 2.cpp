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

    // Constructor
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

        // Update heights
        y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
        x->height = max(getHeight(x->left), getHeight(x->right)) + 1;

        return x;
    }

    // Left Rotation
    Player* rotateLeft(Player* x) {
        Player* y = x->right;
        x->right = y->left;
        y->left = x;

        // Update heights
        x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
        y->height = max(getHeight(y->left), getHeight(y->right)) + 1;

        return y;
    }

    // Insert a player into the AVL tree
    Player* insertPlayer(Player* node, int id, int score) {
        if (node == nullptr)
            return new Player(id, score);

        if (id < node->player_id)
            node->left = insertPlayer(node->left, id, score);
        else if (id > node->player_id)
            node->right = insertPlayer(node->right, id, score);
        else {
            cout << "Player ID already exists! Try again.\n";
            return node; // Duplicate IDs not allowed
        }

        // Update height
        node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
        int balance = getBalanceFactor(node);

        // Perform rotations if unbalanced
        if (balance > 1 && id < node->left->player_id) // Left Left Case
            return rotateRight(node);
        if (balance < -1 && id > node->right->player_id) // Right Right Case
            return rotateLeft(node);
        if (balance > 1 && id > node->left->player_id) { // Left Right Case
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }
        if (balance < -1 && id < node->right->player_id) { // Right Left Case
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        return node;
    }

    // Find the node with the minimum value
    Player* minValueNode(Player* node) {
        Player* current = node;
        while (current->left != nullptr)
            current = current->left;
        return current;
    }

    // Remove a player from the AVL tree
    Player* removePlayer(Player* root, int id) {
        if (root == nullptr) return root;

        // Traverse to find the node to delete
        if (id < root->player_id)
            root->left = removePlayer(root->left, id);
        else if (id > root->player_id)
            root->right = removePlayer(root->right, id);
        else {
            // Case 1: No child (leaf node)
            if (root->left == nullptr && root->right == nullptr) {
                delete root;
                return nullptr;
            }
            // Case 2: One child
            if (root->left == nullptr) {
                Player* temp = root->right;
                delete root;
                return temp;
            } else if (root->right == nullptr) {
                Player* temp = root->left;
                delete root;
                return temp;
            }
            // Case 3: Two children
            Player* temp = minValueNode(root->right);
            root->player_id = temp->player_id;
            root->score = temp->score;
            root->right = removePlayer(root->right, temp->player_id);
        }

        // Update height
        root->height = max(getHeight(root->left), getHeight(root->right)) + 1;
        int balance = getBalanceFactor(root);

        // Perform rotations if unbalanced
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

    // Display players in descending order of scores (Leaderboard)(Reverse Inorder Traversal)
    void displayLeaderboard(Player* node) {
        if (node == nullptr)
            return;
        displayLeaderboard(node->right);
        cout << "Player ID: " << node->player_id << " | Score: " << node->score << endl;
        displayLeaderboard(node->left);
    }

public:
    // Constructor
    MultiplayerGame() {
        root = nullptr;
    }

    // Register a new player
    void registerPlayer(int id, int score) {
        root = insertPlayer(root, id, score);
        cout << "Player registered successfully.\n";
    }

    // Display the leaderboard
    void showLeaderboard() {
        cout << "\nLeaderboard (Sorted by Score):\n";
        displayLeaderboard(root);
    }

    // Remove a player by ID
    void removePlayerByID(int id) {
        root = removePlayer(root, id);
        cout << "Player removed successfully.\n";
    }
};

// Main Function
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
    } while (choice != 4);  // Loop until user chooses to exit

    return 0;
}
