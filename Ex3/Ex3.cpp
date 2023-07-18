#include <iostream>
#include <string>
#include <vector>
#include "node_graph.h"

void Node::AddChild(Node* child) {
    children.push_back(child);
    child->parent = this;
}

void Node::Remove() {
    if (parent != nullptr) {
        parent->DeleteChild(this);
    }
}

void Node::DeleteChild(Node* child) {
    auto it = std::find(children.begin(), children.end(), child);
    if (it != children.end()) {
        children.erase(it);
        delete child;
    }
}

IntNode::IntNode(int value) : value(value) {}

int IntNode::UselessMethod() {
    return 2 * value;
}

NodeType IntNode::GetType() {
    return INT;
}

StringNode::StringNode(const std::string& value) : value(value) {}

int StringNode::UselessMethod() {
    return value.length();
}

NodeType StringNode::GetType() {
    return STRING;
}

FloatNode::FloatNode(float value) : value(value) {}

int FloatNode::UselessMethod() {
    return value / 2;
}

NodeType FloatNode::GetType() {
    return FLOAT;
}

void Graph::AddNode(Node* node) {
    nodes.push_back(node);
}

void Graph::Print() {
    for (Node* node : nodes) {
        std::cout << "Node type: ";
        switch (node->GetType()) {
        case INT:
            std::cout << "IntNode, value: " << static_cast<IntNode*>(node)->UselessMethod() << std::endl;
            break;
        case STRING:
            std::cout << "StringNode, length: " << static_cast<StringNode*>(node)->UselessMethod() << std::endl;
            break;
        case FLOAT:
            std::cout << "FloatNode, value: " << static_cast<FloatNode*>(node)->UselessMethod() << std::endl;
            break;
        default:
            std::cout << "Unknown node type" << std::endl;
        }
        std::cout << "Children: ";
        for (Node* child : node->children) {
            std::cout << child << " ";
        }
        std::cout << std::endl;
    }
}

void Graph::DeleteNode(Node* node) {
    auto it = std::find(nodes.begin(), nodes.end(), node);
    if (it != nodes.end()) {
        node->Remove();
        nodes.erase(it);
        delete node;
    }
}

int main() {
    Graph graph;
    auto rootNode = new IntNode(42);
    auto stringNode = new StringNode("Hello, world!");
    auto floatNode = new FloatNode(3.14);
    auto intChildNode = new IntNode(10);
    auto floatChildNode = new FloatNode(2.0);
    auto stringChildNode = new StringNode("This is a child node");

    rootNode->AddChild(intChildNode);
    rootNode->AddChild(floatChildNode);
    intChildNode->AddChild(stringChildNode);
    graph.AddNode(rootNode);
    graph.AddNode(stringNode);
    graph.AddNode(floatNode);

    std::cout << "Before delete:" << std::endl;
    graph.Print();
    std::cout << std::endl;

    graph.DeleteNode(floatNode);

    std::cout << "After delete:" << std::endl;
    graph.Print();
    std::cout << std::endl;

    return 0;
}