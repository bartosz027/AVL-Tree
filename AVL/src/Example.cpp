#include <iostream>
#include <string>

#include "AVL/AVL.h"

int main() {
	AVL<int> AVL_Tree;
	std::vector<Node<int>*> preorder;

	// Insert elements
	AVL_Tree.Insert(21);
	AVL_Tree.Insert(98);
	AVL_Tree.Insert(86);
	AVL_Tree.Insert(36);
	AVL_Tree.Insert(27);
	AVL_Tree.Insert(53);
	AVL_Tree.Insert(48);
	AVL_Tree.Insert(55);
	AVL_Tree.Insert(52);
	AVL_Tree.Insert(40);
	AVL_Tree.Insert(22);
	AVL_Tree.Insert(1);
	AVL_Tree.Insert(9);
	AVL_Tree.Insert(7);
	AVL_Tree.Insert(2);

	// Print elements
	std::cout << "AVL tree nodes:\n";
	std::cout << "> ";

	preorder = AVL_Tree.GetPreorderTraversal();

	for (const auto& data : preorder) {
		std::cout << data->Key << " [" << data->Balance << "] ";
	}

	std::cout << '\n';

	// Delete elements
	AVL_Tree.Delete(2);
	AVL_Tree.Delete(48);
	AVL_Tree.Delete(98);
	AVL_Tree.Delete(22);
	AVL_Tree.Delete(1);

	// Print elements
	std::cout << "AVL tree nodes:\n";
	std::cout << "> ";

	preorder = AVL_Tree.GetPreorderTraversal();

	for (const auto& data : preorder) {
		std::cout << data->Key << " [" << data->Balance << "] ";
	}

	std::cout << '\n';

	// Search for Node1
	const auto& node1 = AVL_Tree.Search(55);
	std::cout << "Node1 Key:\n";

	if (node1) {
		std::cout << "> " << node1->Key << '\n';
	}
	else {
		std::cout << "> Node1 not found!\n";
	}

	// Search for Node2
	const auto& node2 = AVL_Tree.Search(96);
	std::cout << "Node2 Key:\n";

	if (node2) {
		std::cout << "> " << node2->Key << '\n';
	}
	else {
		std::cout << "> Node2 not found!\n";
	}

	return 0;
}