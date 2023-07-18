#include <iostream>
#include <string>
#include <vector>

enum NodeType { INT, STRING, FLOAT, UNKNOWN };

class Node {
public:
	virtual int UselessMethod() = 0;
	virtual NodeType GetType() = 0;
	void AddChild(Node* child);
	void Remove();
	std::string data;
	std::vector<Node*> children;
	Node* parent = nullptr;
	void DeleteChild(Node* child);

private:
};

class IntNode : public Node {
public:
	IntNode(int value);
	virtual int UselessMethod() override;
	virtual NodeType GetType() override;

private:
	int value;
};

class StringNode : public Node {
public:
	StringNode(const std::string& value);
	virtual int UselessMethod() override;
	virtual NodeType GetType() override;

private:
	std::string value;
};

class FloatNode : public Node {
public:
	FloatNode(float value);
	virtual int UselessMethod() override;
	virtual NodeType GetType() override;

private:
	float value;
};

class Graph {
public:
	void AddNode(Node* node);
	void Print();
	void DeleteNode(Node* node);

private:
	std::vector<Node*> nodes;
};