#pragma once

template <class T>
class Node
{
public:
	Node(T data);

	T data;
	Node* parent;
	Node* left;
	Node* right;

	int leftWeight;
	int rightWeight;
};

template <class T>
Node<T>::Node(T data)
{
	this->data = data;
	this->parent = nullptr;
	this->left = nullptr;
	this->right = nullptr;
	this->leftWeight = 0;
	this->rightWeight = 0;
}