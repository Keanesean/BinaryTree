#include <chrono>
#include <iostream>
#include <vector>
#include <time.h>
#include "BinaryTree.h"

std::vector<int> getRandomList(int size);

int main()
{
	BinaryTree<int> tree;
	std::vector<int> list;	
	
	unsigned int step = 10000;
	unsigned int minSize = 20000;
	unsigned int maxSize = 1000000;

	for (unsigned int i = minSize; i <= maxSize; i += step)
	{
		//Get a random list or unordered elements.
		list = getRandomList(i);
		
		auto timeStart = std::chrono::high_resolution_clock::now();

		//Add elements into the binaryTree
		for (unsigned int j = 0; j < list.size(); j++)
		{
			tree.Add(list[j]);
		}

		//End timer.
		auto timeEnd = std::chrono::high_resolution_clock::now();

		//Time.
		__int64 time = std::chrono::duration_cast<std::chrono::milliseconds>(timeEnd - timeStart).count();

		std::cout.imbue(std::locale(""));
		std::cout << "Size (Nodes): " << i << std::endl;		
		std::cout << "Time (ms): " << time << std::endl;

		int depth = tree.GetDepth();
		std::cout << "Depth: " << depth << std::endl;

		std::cout << std::endl;

		//Reset
		tree.DeleteTree();
		list.clear();
	}

	system("pause");
	return 0;
}
std::vector<int> getRandomList(int size)
{
	std::vector<int> list;
	for (int i = 0; i < size; i++)
	{
		unsigned int number = rand() % UINT_MAX - INT_MAX;

		list.push_back((int)number);

		for (int j = 0; i < list.size() - 1; j++)
		{
			if (number = list[j])
			{
				break;
				list.pop_back();
				i--;
			}
		}
	}

	return list;
}