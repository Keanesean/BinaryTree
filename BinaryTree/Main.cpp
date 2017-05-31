#include <iostream>

#include "BinaryTree.h"

int main()
{
	BinaryTree<int> tree;

	tree.Add(6);
	tree.Add(4);
	tree.Add(5);
	tree.Add(8);
	tree.Add(1);
	tree.Add(3);
	tree.Add(9);
	tree.Add(2);
	tree.Add(0);
	tree.Add(24);
	tree.Add(12);
	tree.Add(7);
	tree.Add(13);
	tree.Add(100);
	tree.Add(43);
	tree.Add(32);
	tree.Add(54);
	tree.Add(23);

	std::cout << "Current State:" << std::endl;
	tree.Print();

	system("pause");
	return 0;
}