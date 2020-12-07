#pragma once
#include "transaction.h"
#include "fund.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;
const int MONEY_MARKET = 0;
const int PRIME_MONEY_MARKET = 1;
const int LONG_TERM_BOND = 2;
const int SHORT_TERM_BOND = 3;

class Account
{
	friend ostream& operator<<(ostream& out_stream, Account& rhs);

public:
	Account();
	Account(string first_name, string last_name, int account_ID);
	~Account();

	void AddToAcc(int fund_num, int amount);
	bool DeductFunds(int fund_num, int amount, Transaction trans);
	void RecordTransactions(Transaction trans, int fund_num);
	void WidthFromSimilarAcct(int primary_fund, int secondary_fund, int amount);
	void DisplayHistory();
	void DisplayFundHistory(int fund_number);
	void DisplayError(int amount, string first_name, string last_name, int fund_num);
	
	//getters-setters
	int GetAccountID() const;
	int GetBalance(int fund_num)const;
	string GetFundName(int fund_num);
	string GetFirstName()const;
	string GetLastName()const;

	void SetFundID(int fund_num);

private:
	string first_name_, last_name_;
	int account_ID_;
	int fund_ID_;
	Fund array_fund_[10];
};

