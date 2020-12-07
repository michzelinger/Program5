#pragma once
#include "transaction.h"
#include <string>
#include <vector>
#include <iostream>

class Fund
{
public:
	Fund();
	~Fund();

	bool AddAmount(int amount_add);
	bool SubtractAmount(int amount_sub);
	bool BalanceCheck(int amount_sub); // checks if balance is >= to the amount to be subtracted.
	bool RecordTrans(Transaction trans);
	void PrintHistory();
	void PrintHistoryOfFund();

	void SetName(string fund_name);
	
	string GetName() const;
	int GetBalance() const;

private:
	string fund_name_;
	int balance_;
	vector<Transaction> history_;

};

