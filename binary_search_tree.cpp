#include "binary_search_tree.h"
#include <queue>

BinarySearchTree::BinarySearchTree()
{
	root_ = nullptr;
}

BinarySearchTree::~BinarySearchTree()
{
	Empty();
}

bool BinarySearchTree::Insert(Account* account)
{
	if (account->GetAccountID() < 1000 || account->GetAccountID() > 9999)
	{
		return false;
	}

	if (root_ == nullptr)
	{
		root_ = new Node;
		root_->pAcct = account;
		root_->left = nullptr;
		root_->right = nullptr;
		return true;
	}
	else
	{
		Node* current = root_;
		RecInsert(current, account);
	}
	return false;
}

bool BinarySearchTree::RecInsert(Node* current, Account* key)
{
	if (key->GetAccountID() < current->pAcct->GetAccountID())
	{
		if (current->left == nullptr)
		{
			Node* InsNode = new Node;
			InsNode->pAcct = key;
			InsNode->left = nullptr;
			InsNode->right = nullptr;
			current->left = InsNode;
			return true;
		}
		else
		{
			return RecInsert(current->left, key);
		}
	}
	else if (key->GetAccountID() > current->pAcct->GetAccountID())
	{
		if (current->right == nullptr)
		{
			Node* InsNode = new Node;
			InsNode->pAcct = key;
			InsNode->left = nullptr;
			InsNode->right = nullptr;
			current->right = InsNode;
			return true;
		}
		else
		{
			return RecInsert(current->right, key);
		}
	}
	else
	{
		cerr << "ERROR: Account " << key->GetAccountID() << " is already open. Transaction refused." << endl;
		return false;
	}
}



bool BinarySearchTree::Retrieve(const int& account_num, Account*& account) const
{
	Node* current = root_;
	bool flag = false;

	while (!flag)
	{
		if (current != nullptr && account_num == current->pAcct->GetAccountID())
		{
			account = current->pAcct;
			flag = true;
			return flag;
		}
		else if (current!=nullptr && account_num > current->pAcct->GetAccountID())
		{
			current = current->right;
		}
		else if (current!= nullptr && account_num < current->pAcct->GetAccountID())
		{
			current = current->left;
		}
		else
		{
			flag = true;
		}
	}
	cerr << "ERROR: Account " << account_num << " not found. Transferal refused." << endl;
	return false;
}

void BinarySearchTree::Empty()
{
	DeleteTree(root_);
}

void BinarySearchTree::Display() const
{
	if (root_ == nullptr)
	{
		return;
	}
	RecDisplay(root_);
}

void BinarySearchTree::RecDisplay(Node* current) const
{
	if (current->right != nullptr && current->left != nullptr)
	{
		RecDisplay(current->right);
		cout << *current->pAcct << endl;
		RecDisplay(current->left);
	}
	else if (current->right != nullptr)
	{
		cout << *current->pAcct << endl;
		RecDisplay(current->right);
	}
	else if (current->left != nullptr)
	{
		cout << *current->pAcct << endl;
		RecDisplay(current->left);
	}
	else
	{
		cout << *current->pAcct << endl;
	}
}

void BinarySearchTree::DeleteTree(Node* node)
{
	if (node == nullptr)
	{
		return;
	}
	DeleteTree(node->left);
	DeleteTree(node->right);
	delete node;
}

bool BinarySearchTree::IsEmpty() const
{
	if (root_ == nullptr)
	{
		return true;
	}
	return false;
}