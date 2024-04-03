#ifndef NODE
#define NODE

#include <vector>
#include <string>

class Node {
public:
    int id;
    int value;
    int n_children;
    std::vector<Node *> children;

    Node();
    Node(int id, int value, int n_children);
    ~Node();

    void addChild(Node* childNode);
    void deleteChild(int nodeId);
    void printTree();
    Node* searchLastNode();
    void recursiveDelete();
    int findNonChildNode();
    void changeId(int oldId, int newId);

};

#endif