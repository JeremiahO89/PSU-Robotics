
struct Node {
    int data;
    Node* left;
    Node * right;
};

Node* createNode(int data) {
    Node* newNode = new Node();
    newNode->data = data;
    newNode->left = nullptr;
    newNode ->right = nullptr;
};