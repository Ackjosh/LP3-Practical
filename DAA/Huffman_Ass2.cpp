
#include <iostream>
#include <queue>
#include <vector>
#include <string>
using namespace std;

// Node structure
class Node {
public:
    char data;
    int freq;
    Node *left, *right;

    Node(char c, int f) {
        data = c;
        freq = f;
        left = right = NULL;
    }
};

// Custom comparator for Min Heap
class Compare {
public:
    bool operator()(Node* a, Node* b) {
        return a->freq > b->freq;
    }
};

// Generate Huffman codes
void printCodes(Node* root, string code) {
    if (root == NULL)
        return;

    // Check whether the node is a leaf
    if (root->left == NULL && root->right == NULL) {
        cout << root->data << " : "
             << (code.empty() ? "0" : code) << endl;
        return;
    }

    printCodes(root->left, code + "0");
    printCodes(root->right, code + "1");
}

// Build Huffman Tree
void HuffmanCode(char data[], int freq[], int n) {

    if (n <= 0) {
        cout << "Invalid input";
        return;
    }

    priority_queue<Node*, vector<Node*>, Compare> pq;

    // Insert all characters into Min Heap
    for (int i = 0; i < n; i++) {
        if (freq[i] <= 0) {
            cout << "Invalid frequency";
            return;
        }

        pq.push(new Node(data[i], freq[i]));
    }

    // Construct Huffman Tree
    while (pq.size() > 1) {

        // Extract two minimum frequency nodes
        Node* left = pq.top();
        pq.pop();

        Node* right = pq.top();
        pq.pop();

        // Create new internal node
        Node* temp = new Node(
            '$', left->freq + right->freq
        );

        temp->left = left;
        temp->right = right;

        pq.push(temp);
    }

    // Remaining node is the root
    Node* root = pq.top();

    cout << "\nHuffman Codes:\n";
    printCodes(root, "");
    
    auto deleteTree = [&](auto&& self, Node* node) -> void {
        if (node == NULL) return;
        self(self, node->left);
        self(self, node->right);
        delete node;
    };

    deleteTree(deleteTree, root);
}

int main() {

    char data[] = {'a', 'b', 'c', 'd', 'e', 'f'};
    int freq[] = {5, 9, 12, 13, 16, 45};

    int n = sizeof(data) / sizeof(data[0]);

    cout << "Generated Huffman Codes:\n";

    HuffmanCode(data, freq, n);

    return 0;
}