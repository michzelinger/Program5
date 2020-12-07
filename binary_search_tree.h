#pragma once
#include "account.h"
class BinarySearchTree
{
public:
	BinarySearchTree();
	~BinarySearchTree();

	bool Insert(Account* account);
	bool Retrieve(const int& account_num, Account*& account)const;
	void Display()const;
	
	

	void Empty();
	bool IsEmpty()const;

private:
	struct Node
	{
		Account* pAcct;
		Node* right;
		Node* left;
	};
	Node* root_ = nullptr;
	bool RecInsert(Node* current, Account* key);
	void RecDisplay(Node* current) const;
	void DeleteTree(Node* node);
};

