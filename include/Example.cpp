#include "AVL/AVL.h"

#include <iostream>
#include <string>

int main() {
	AVL<int> AVL_Tree;

	// Insert elements
	AVL_Tree.Insert(9);
	AVL_Tree.Insert(21);
	AVL_Tree.Insert(98);
	AVL_Tree.Insert(86);
	AVL_Tree.Insert(36);
	AVL_Tree.Insert(1);
	AVL_Tree.Insert(27);
	AVL_Tree.Insert(53);
	AVL_Tree.Insert(48);
	AVL_Tree.Insert(7);
	AVL_Tree.Insert(55);
	AVL_Tree.Insert(52);
	AVL_Tree.Insert(40);
	AVL_Tree.Insert(22);
	AVL_Tree.Insert(2);

	// Print elements
	std::cout << "AVL tree nodes (after insert):\n";
	std::cout << "> ";

	for (const auto& data : AVL_Tree.GetPreorderTraversal()) {
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
	std::cout << "AVL tree nodes (after delete):\n";
	std::cout << "> ";

	for (const auto& data : AVL_Tree.GetPreorderTraversal()) {
		std::cout << data->Key << " [" << data->Balance << "] ";
	}

	std::cout << '\n';

	// Search for number 55
	const auto& node1 = AVL_Tree.Search(55);
	std::cout << "Search result:\n";

	if (node1) {
		std::cout << "> " << node1->Key << '\n';
	}
	else {
		std::cout << "> Node not found!\n";
	}

	// Search for number 98
	const auto& node2 = AVL_Tree.Search(98);
	std::cout << "Search result:\n";

	if (node2) {
		std::cout << "> " << node2->Key << '\n';
	}
	else {
		std::cout << "> Node not found!\n";
	}

	return 0;
}