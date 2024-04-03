#include "node.h"
#include <iostream>

void printTree(Node* root) {
    std::vector<std::vector<Node*>> nodesToCheck;
    std::vector<Node*> firstRow;
    firstRow.push_back(root);
    nodesToCheck.push_back(firstRow);

    int i = 0;
    while (i < nodesToCheck.size()) {
        if (i != 0) {
            std::cout << std::endl;
        }
        int j;
        for (j = 0; j < nodesToCheck[i].size(); j++) {
            if (nodesToCheck[i][j] != nullptr) {
                std::cout << nodesToCheck[i][j]->id << " ";
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
        }
        i++;
    }
    std::cout << std::endl;
}

int main() {
    // создаем узлы и добавляем их в дерево
    int i;
    Node* node1 = new Node(0,100,3);
    std::vector<Node *> nodes;
    for (i = 1; i < 15; i++) {
        Node* node = new Node(i,i,3);
        nodes.push_back(node);
        (*node1).addChild(node);
    }


    std::cout << "Трехлистное дерево с корнем 0" << std::endl;
    printTree(node1);
    std::cout << std::endl;

    //удаляем узел с id 14
    (*node1).deleteChild(14);

    std::cout << "Дерево после удаления узла с id 14" << std::endl;
    printTree(node1);
    std::cout << std::endl;

    //удаляем узел с id 5
    (*node1).deleteChild(5);

    std::cout << "Дерево после удаления узла с id 5" << std::endl;
    printTree(node1);

    delete node1;
    node1 = nullptr;
}
