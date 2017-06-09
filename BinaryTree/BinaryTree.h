#pragma once
#include <iostream>
#include <stack>
#include <queue>

#include "Node.h"

template <class T>
class BinaryTree
{
public:
	BinaryTree();
	~BinaryTree();

	void DeleteTree();

	bool Add(T data);
	bool Remove(T data);
	bool Empty() const;

	int GetDepth();

	void Print() const;
private:
	bool Add(Node<T>* start, T data);
	bool Remove(Node<T> * start, T data);

	void CalculateWeight();	
	int CalculateWeight(Node<T>* current);	
	void Balance();

	void CalculateDepth();	

	Node<T>* root;
	int depth;
};


/**********************\
*****Public Methods*****
\**********************/

template <class T>
BinaryTree<T>::BinaryTree()
{
	this->root = nullptr;
}
template <class T>
BinaryTree<T>::~BinaryTree()
{
	this->DeleteTree();
}
template <class T>
void BinaryTree<T>::DeleteTree()
{
	if (this->root == nullptr)
	{
		return;
	}
	else
	{
		std::queue<Node<T>*> queue;
		queue.push(this->root);

		Node<T>* current;

		while (!queue.empty())
		{
			current = queue.front();
			queue.pop();

			if (current->left != nullptr)
			{
				queue.push(current->left);
			}
			if (current->right != nullptr)
			{
				queue.push(current->right);
			}

			current->left = nullptr;
			current->right = nullptr;
			current->parent = nullptr;
			delete current;
		}
	}
}
template <class T>
bool BinaryTree<T>::Add(T data)
{
	//Check if we sucessfully add the node.
	bool success = this->Add(this->root, data);

	//If the node is added, rebalance the binary tree.
	if (success)
	{
		this->CalculateWeight();
		this->Balance();
	}

	return success;
}
template <class T>
bool BinaryTree<T>::Remove(T data)
{
	//Check if we sucessfully remove the node.
	bool success = this->Remove(this->root, data);

	//If the node is removed, rebalance the binary tree.
	if (success)
	{
		this->CalculateWeight();
		this->Balance();
	}

	return success;
}
template <class T>
bool BinaryTree<T>::Empty() const
{
	return this->root == nullptr;
}
template <class T>

int BinaryTree<T>::GetDepth()
{
	this->CalculateDepth();

	return this->depth;
}
template <class T>
void BinaryTree<T>::Print() const
{
	std::queue<Node<T>*> queue;
	Node<T>* current;
	Node<T>* nullNode = nullptr;
	bool end = false;
	int count = 0;

	queue.push(this->root);
	count = 1;

	while (!queue.empty() && !end)
	{
		end = true;

		for (int i = 0; i < count; i++)
		{
			current = queue.front();
			queue.pop();

			if (current != nullNode)
			{
				std::cout << current->data << " ";
			}
			else
			{
				std::cout << "- ";
			}
			
			if (current == nullNode)
			{
				queue.push(nullNode);
				queue.push(nullNode);
			}
			else
			{
				if (current->left != nullptr)
				{
					queue.push(current->left);
					end = false;
				}
				else
				{
					queue.push(nullNode);
				}

				if (current->right != nullptr)
				{
					queue.push(current->right);
					end = false;
				}
				else
				{
					queue.push(nullNode);
				}
			}
		}
		
		count = queue.size();
		std::cout << std::endl;
	}
}

/**********************\
****Private Methods*****
\**********************/

template <class T>
bool BinaryTree<T>::Add(Node<T>* start, T data)
{
	//Create new node to add to the tree.
	Node<T>* newNode = new Node<T>(data);

	//If there are no nodes in the tree, make the newNode the root.
	if (this->Empty())
	{
		this->root = newNode;
		newNode = nullptr;
		delete newNode;
	}
	//Else if there is at least one node in the tree.
	else
	{
		Node<T>* current = start;
		Node<T>* trail = current;

		//Cycle through the tree until a nuullptr is found.
		while (current != nullptr)
		{
			//Go left if data is less than current data.
			if (data < current->data)
			{
				trail = current;
				current = current->left;
			}
			//Go right if data is greater than current data.
			else if (data > current->data)
			{
				trail = current;
				current = current->right;
			}
			//If neither less than or greater than, then it must be equal.  Clean up and return false.  Data already exists.
			else
			{
				current = nullptr;
				trail = nullptr;
				newNode = nullptr;
				delete current;
				delete trail;
				delete newNode;

				return false;
			}
		}

		//Found node that contains a nullptr link.  Check which link of that node we are suppose to link to.
		//Left link.
		if (data < trail->data)
		{
			newNode->parent = trail;
			trail->left = newNode;
		}
		//Right link.
		else
		{
			newNode->parent = trail;
			trail->right = newNode;
		}

		//Cleanup.
		current = nullptr;
		trail = nullptr;
		newNode = nullptr;
		delete current;
		delete trail;
		delete newNode;
	}

	return true;
}
template <class T>
bool BinaryTree<T>::Remove(Node<T>* start, T data)
{
	Node<T>* current = start;
	Node<T>* trail = start;

	while (true)
	{
		//Search left.
		if (data < current->data)
		{
			trail = current;
			current = current->left;
		}
		//Search right.
		else if (data > current->data)
		{
			trail = current;
			current = current->right;
		}
		//Found.
		else
		{
			break;
		}

		//Data to delete does not exist.  Return failure.
		if (current == nullptr)
		{
			current = nullptr;
			trail = nullptr;
			delete current;
			delete trail;
			return false;
		}
	}

	while (true)
	{
		//If both left and right are null links.
		if (current->left == nullptr && current->right == nullptr)
		{
			if (this->root == current)
			{
				this->root = nullptr;
			}
			//If the left link is the link to current, set as null.
			else if (trail->left == current)
			{
				trail->left = nullptr;
			}
			//If the right link is the link to current, set as null.
			else
			{
				trail->right = nullptr;
			}

			break;
		}
		//If either left xor the right links are not null.
		else if (current->left == nullptr || current->right == nullptr)
		{
			if (current == this->root)
			{
				if (current->left == nullptr)
				{
					this->root = current->right;
					current->right->parent = nullptr;
				}
				else
				{
					this->root = current->left;
					current->left->parent = nullptr;
				}
			}
			//Check if it is the left link that is null.
			else if (current->left == nullptr)
			{
				//If the left link of trail is equal to the current node, set the left link of trail to the right link of current.
				if (trail->left == current)
				{
					trail->left = current->right;
				}
				//If the right link of trail is equal to the current node, set the right link of trail to the right link of current.
				else
				{
					trail->right = current->right;
				}

				//Set the parent of the right link of current to trail.
				current->right->parent = trail;

				//Remove the right link on current.
				current->right = nullptr;
			}
			//Check if it is the right link that is null.
			else
			{
				//If the left link of trail is equal to the current node, set the left link of trail to the left link of current.
				if (trail->left == current)
				{
					trail->left = current->left;
				}
				//If the right link of trail is equal to the current node, set the right link of trail to the left link of current.
				else
				{
					trail->right = current->left;
				}

				//Set the parent of the left link of current to trail.
				current->left->parent = trail;

				//Remove the left link on current.
				current->left = nullptr;
			}

			break;
		}
		//If both left and right links are not null.
		else
		{
			Node<T>* pivot = current;

			//Determine which side to remove a node on and replace with pivot.  Pivot will then boil down to case 1-3 above in order to be deleted.
			//If the left side is heavier than the right side.
			if (current->leftWeight > current->rightWeight)
			{
				//Go left once.
				trail = current;
				current = current->left;

				//Go right until we find the largest node on the left side.
				while (current->right != nullptr)
				{
					trail = current;
					current = current->right;
				}

				//Exchange the data.
				pivot->data = current->data;
				continue;
			}
			//If the right side is heavier than the left side.
			else
			{
				//Go right once.
				trail = current;
				current = current->right;

				//Go left until we find the smallest node on the right side.
				while (current->left != nullptr)
				{
					trail = current;
					current = current->left;
				}

				//Set pivot data to current data.
				pivot->data = current->data;

				//Current is now set as the largest left node or the smallest right node.  Reloop and delete this node, which will be part of case 1-3.
				continue;
			}
		}
	}


	//Cleanup.
	current = nullptr;
	trail = nullptr;
	delete current;
	delete trail;

	return true;
}
template <class T>

void BinaryTree<T>::CalculateWeight()
{
	this->CalculateWeight(this->root);
}
template <class T>
int BinaryTree<T>::CalculateWeight(Node<T>* current)
{
	if (current == nullptr)
	{
		return 0;
	}
	else
	{
		current->leftWeight = this->CalculateWeight(current->left);
		current->rightWeight = this->CalculateWeight(current->right);
	}
		
	return 1 + current->leftWeight + current->rightWeight;	
}
template <class T>
void BinaryTree<T>::Balance()
{
	Node<T>* current;

	std::queue<Node<T>*> queue;

	queue.push(this->root);

	while(!queue.empty())
	{
		current = queue.front();
		queue.pop();

		if (abs(current->leftWeight - current->rightWeight) <= 1)
		{
			if (current->left != nullptr)
			{
				queue.push(current->left);
			}
			if (current->right != nullptr)
			{
				queue.push(current->right);
			}
			
		}
		else
		{
			T data = current->data;

			this->Remove(this->root, data);
			this->Add(this->root, data);

			std::queue<Node<T>*> empty;
			std::swap(queue, empty);
		}
	}

	current = nullptr;
	delete current;
}
template <class T>
void BinaryTree<T>::CalculateDepth()
{	
	struct depthStruct
	{
		Node<T>* current;
		int depth;
	} tempStruct;
	std::queue<depthStruct> queue;
	this->depth = 0;

	tempStruct.current = this->root;
	tempStruct.depth = 1;
	queue.push(tempStruct);

	while (!queue.empty())
	{
		if (queue.front().depth > this->depth)
		{
			this->depth = queue.front().depth;
		}

		if (queue.front().current->left != nullptr)
		{
			tempStruct.current = queue.front().current->left;
			tempStruct.depth = queue.front().depth + 1;

			queue.push(tempStruct);
		}
		if (queue.front().current->right != nullptr)
		{
			tempStruct.current = queue.front().current->right;
			tempStruct.depth = queue.front().depth + 1;

			queue.push(tempStruct);
		}

		queue.pop();
	}
}