#pragma once
#include <vector>

template<typename T>
struct Node {
	T Key;

	int Height;
	int Balance;

	Node* Left;
	Node* Right;
};

template<typename T>
class AVL {
public:
	AVL() :
		m_Root(nullptr), m_AllowTreeModifications(true) {
	}

	void Insert(T value);
	void Delete(T value);

	Node<T>* Search(T value) const;
	std::vector<Node<T>*> GetPreorderTraversal() const;
private:
	Node<T>* Create(T value);

	void Insert(Node<T>*& node, T value);
	void Delete(Node<T>*& node, T value);

	Node<T>* Search(Node<T>* node, T value) const;
	void PreorderTraversal(Node<T>* node, std::vector<Node<T>*>& traversal) const;

	Node<T>* LR(Node<T>* node) const;
	Node<T>* RL(Node<T>* node) const;

	Node<T>* LL(Node<T>* node) const;
	Node<T>* RR(Node<T>* node) const;

	void CalculateHeight(Node<T>* node) const;
	void CalculateBalance(Node<T>* node) const;
private:
	Node<T>* m_Root;
	bool m_AllowTreeModifications;
};


template<typename T>
inline void AVL<T>::Insert(T value) {
	m_AllowTreeModifications = true;
	Insert(m_Root, value);
}

template<typename T>
inline void AVL<T>::Insert(Node<T>*& node, T value) {
	if(!node) {
		node = Create(value);
		return;
	}
	else if (value < node->Key) {
		Insert(node->Left, value);
	}
	else if (value > node->Key) {
		Insert(node->Right, value);
	}

	if (m_AllowTreeModifications) {
		CalculateHeight(node);
		CalculateBalance(node);

		if (node->Balance == -2) {
			if (node->Right->Balance == -1) {
				node = LL(node);
			}
			else {
				node = RL(node);
			}

			m_AllowTreeModifications = false;
		}

		if (node->Balance == 2) {
			if (node->Left->Balance == 1) {
				node = RR(node);
			}
			else {
				node = LR(node);
			}

			m_AllowTreeModifications = false;
		}

		if (node->Balance == 0) {
			m_AllowTreeModifications = false;
		}
	}
}

template<typename T>
inline Node<T>* AVL<T>::Create(T value) {
	Node<T>* node = new Node<T>();
	node->Key = value;

	node->Height = 0;
	node->Balance = 0;

	node->Left = nullptr;
	node->Right = nullptr;

	return node;
}


template<typename T>
inline void AVL<T>::Delete(T value) {
	m_AllowTreeModifications = true;
	Delete(m_Root, value);
}

template<typename T>
inline void AVL<T>::Delete(Node<T>*& node, T value) {
	if (!node) {
		return;
	}
	
	if (value == node->Key) {
		if (node->Left && node->Right) {
			Node<T>* iterator = node->Left;

			while (iterator->Right) {
				iterator = iterator->Right;
			}

			node->Key = iterator->Key;
			Delete(node->Left, iterator->Key);
		}
		else if (node->Left) {
			node = node->Left;
		}
		else if (node->Right) {
			node = node->Right;
		}
		else {
			node = nullptr;
			return;
		}
	}
	else if (value < node->Key) {
		Delete(node->Left, value);
	}
	else if (value > node->Key) {
		Delete(node->Right, value);
	}

	if (m_AllowTreeModifications) {
		CalculateHeight(node);
		CalculateBalance(node);

		if (node->Balance == -2) {
			if (node->Right->Balance == -1 || node->Right->Balance == 0) {
				node = LL(node);
			}
			else {
				node = RL(node);
			}
		}

		if (node->Balance == 2) {
			if (node->Left->Balance == 1 || node->Left->Balance == 0) {
				node = RR(node);
			}
			else {
				node = LR(node);
			}
		}

		if (node->Balance == -1 || node->Balance == 1) {
			m_AllowTreeModifications = false;
		}
	}
}


template<typename T>
inline Node<T>* AVL<T>::Search(T value) const {
	return Search(m_Root, value);
}

template<typename T>
inline Node<T>* AVL<T>::Search(Node<T>* node, T value) const {
	if (!node) {
		return nullptr;
	}
	else if (value < node->Key) {
		return Search(node->Left, value);
	}
	else if (value > node->Key) {
		return Search(node->Right, value);
	}
	else {
		return node;
	}
}


template<typename T>
std::vector<Node<T>*> AVL<T>::GetPreorderTraversal() const {
	if (m_Root) {
		std::vector<Node<T>*> result;
		PreorderTraversal(m_Root, result);

		return result;
	}

	return std::vector<Node<T>*>();
}

template<typename T>
void AVL<T>::PreorderTraversal(Node<T>* node, std::vector<Node<T>*>& traversal) const {
	if (node) {
		traversal.push_back(node);
		PreorderTraversal(node->Left,  traversal);
		PreorderTraversal(node->Right, traversal);
	}
}


template<typename T>
inline Node<T>* AVL<T>::LR(Node<T>* node) const {
	node->Left = LL(node->Left);
	return RR(node);
}

template<typename T>
inline Node<T>* AVL<T>::RL(Node<T>* node) const {
	node->Right = RR(node->Right);
	return LL(node);
}

template<typename T>
inline Node<T>* AVL<T>::LL(Node<T>* node) const {
	Node<T>* A = node;
	Node<T>* B = node->Right;
	Node<T>* II = B->Left;

	B->Left = A;
	A->Right = II;

	CalculateHeight(A);
	CalculateBalance(A);

	CalculateHeight(B);
	CalculateBalance(B);

	return B;
}

template<typename T>
inline Node<T>* AVL<T>::RR(Node<T>* node) const {
	Node<T>* A = node;
	Node<T>* B = node->Left;
	Node<T>* II = B->Right;

	A->Left = II;
	B->Right = A;

	CalculateHeight(A);
	CalculateBalance(A);

	CalculateHeight(B);
	CalculateBalance(B);

	return B;
}


template<typename T>
inline void AVL<T>::CalculateHeight(Node<T>* node) const {
	if (node->Left && node->Right) {
		node->Height = std::max(node->Left->Height, node->Right->Height) + 1;
	}
	else if (node->Left) {
		node->Height = node->Left->Height + 1;
	}
	else if (node->Right) {
		node->Height = node->Right->Height + 1;
	}
	else {
		node->Height = 0;
	}
}

template<typename T>
inline void AVL<T>::CalculateBalance(Node<T>* node) const {
	if (node->Left && node->Right) {
		node->Balance = node->Left->Height - node->Right->Height;
	}
	else if (node->Left) {
		node->Balance = node->Left->Height + 1;
	}
	else if (node->Right) {
		node->Balance = -1 * (node->Right->Height + 1);
	}
	else {
		node->Balance = 0;
	}
}