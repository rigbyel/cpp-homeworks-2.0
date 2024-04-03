#include <iostream>
#include "node.h"

Node::Node() {
    id = 0;
    value = 0;
    n_children = 2;
    children = std::vector<Node *>();
}

Node::Node(int new_id, int new_value, int num_children) {
    id = new_id;
    value = new_value;
    n_children = num_children;
    children = std::vector<Node *>();
}

void Node::addChild(Node* childNodePtr) {

    if (children.size() < n_children) {
        children.push_back(childNodePtr);
        return;
    }
    
    Node* parentNodePtr = searchLastNode();
    parentNodePtr->addChild(childNodePtr);
}

Node::~Node() {
    
}

void Node::recursiveDelete()
{
    if (children.size() != 0){
        int j = 0;
        for (j = 0; j < children.size(); j++){
            children[j]->recursiveDelete();
        }   
    }
    delete this;
}

void Node::deleteChild(int nodeId) {
    if (id == nodeId) {
        std::cout << "cannot delete root element" << std::endl;
    }
    int j = 0;
    for (j = 0; j < children.size(); j++) {
        if (children[j]->id == nodeId) {
            std::vector<Node*> updateChildren;
            delete children[j];

            int i;
            for (i = 0; i < children.size(); i++) {
                if (i!=j) {
                    updateChildren.push_back(children[i]);
                }
            }
            children = updateChildren;
            return;
        }

        children[j]->deleteChild(nodeId);
    }

    return;
}


Node* Node::searchLastNode() {
    if (children.size() == 0) {
        return this;
    }

    std::vector<std::vector<Node*>> nodesToCheck;
    std::vector<Node*> firstRow;
    firstRow.push_back(this);
    nodesToCheck.push_back(firstRow);

    int i = 0;
    while (i < nodesToCheck.size()) {
        int j = 0;
        for (j = 0; j < nodesToCheck[i].size(); j++) {
            if (nodesToCheck[i][j]->children.size() < n_children) {
                return nodesToCheck[i][j];
            }

            if (nodesToCheck[i][j]->children.size() != 0) {
                int k;
                for (k = 0; k < nodesToCheck[i][j]->children.size(); k++) {
                    if (nodesToCheck.size() < i+2) {
                        nodesToCheck.push_back({});
                    }
                    nodesToCheck[i+1].push_back(nodesToCheck[i][j]->children[k]);
                }
            }
        }
        i++;
    }
}
