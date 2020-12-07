#pragma once
#include <string>
#include <iostream>
using namespace std;

class Transaction
{
	friend ostream& operator<<(ostream& out_stream, const Transaction& trans);

public:
	Transaction();
	Transaction(char type, string last_name, string first_name, int account_number);
	Transaction(char type, int account_number, int fund_number, int amount);
	Transaction(char type, int account_number, int fund_number, int amount, int transfer_account_number, int transfer_fund);
	Transaction(char type, int account_number);
	Transaction(char type, int account_number, int fund_number);

	Transaction(char type, int account_number, int fund_number, int amount, int transfer_account_number, int transfer_fund, string trans_fail);
	Transaction(char type, int account_number, int fund_number, int amount, string trans_fail);
	~Transaction();

	bool IsFailed();
	char GetTranscationType() const;
	string GetFirstName() const;
	string GetLastName() const;
	int GetAccountID()const;
	int GetFundID() const;
	int GetTransferAccountID() const;
	int GetTransferFund() const;
	int GetAmount() const;

private:
	char type_;
	string first_name_;
	string last_name_;
	string trans_fail_;
	int account_number_, fund_number_, transfer_account_number_, transfer_fund_, amount_;

};

