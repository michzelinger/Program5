#pragma once
#include <queue>
#include "binary_search_tree.h"
#include "transaction.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

class JollyBanker
{
public:
	JollyBanker();
	~JollyBanker();

	bool ReadTransactions();
	void ExecuteTransactions();
	void Display();

private:
	queue<Transaction> transaction_list_;
	BinarySearchTree account_list_;
};

