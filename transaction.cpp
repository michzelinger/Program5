
#include "transaction.h"

Transaction::Transaction()
{
	type_ = (char)0;
	account_number_ = 0;
	fund_number_ = 0;
	transfer_account_number_ = 0;
	transfer_fund_ = 0;
	amount_ = 0;
}
Transaction::Transaction(char type, string last_name, string first_name, int account_number)
{
	type_ = type;
	first_name_ = first_name;
	last_name_ = last_name;
	account_number_ = account_number;
}
Transaction::Transaction(char type, int account_number, int fund_number, int amount)
{
	type_ = type;
	account_number_ = account_number;
	fund_number_ = fund_number;
	amount_ = amount;
	transfer_account_number_ = 0;
	transfer_fund_ = 0;
}
Transaction::Transaction(char type, int account_number, int fund_number, int amount, int transfer_account_number, int transfer_fund)
{
	type_ =type;
	account_number_ = account_number;
	fund_number_ = fund_number;
	amount_ = amount;
	transfer_account_number_ = transfer_account_number;
	transfer_fund_ = transfer_fund;
}
Transaction::Transaction(char type, int account_number)
{
	type_ = type;
	account_number_ = account_number;
	fund_number_ = 0;
	transfer_account_number_ = 0;
	transfer_fund_ = 0;
	amount_ = 0;
}
Transaction::Transaction(char type, int account_number, int fund_number)
{
	type_ = type;
	account_number_ = account_number;
	fund_number_ = fund_number;
	transfer_account_number_ = 0;
	transfer_fund_ = 0;
	amount_ = 0;
}
Transaction::Transaction(char type, int account_number, int fund_number, int amount, int transfer_account_number, int transfer_fund, string trans_fail)
{
	type_ = type;
	account_number_ = account_number;
	fund_number_ = fund_number;
	amount_ = amount;
	transfer_account_number_ = transfer_account_number;
	transfer_fund_ = transfer_fund;
	trans_fail_ = trans_fail;
}
Transaction::Transaction(char type, int account_number, int fund_number, int amount, string trans_fail)
{
	type_ = type;
	account_number_ = account_number;
	fund_number_ = fund_number;
	amount_ = amount;
	trans_fail_ = trans_fail;
}
Transaction::~Transaction()
{
}

bool Transaction::IsFailed()
{
	return (trans_fail_.empty());
}
char Transaction::GetTranscationType() const
{
	return type_;
}

string Transaction::GetFirstName() const
{
	return first_name_;
}

string Transaction::GetLastName() const
{
	return last_name_;
}

int Transaction::GetAccountID() const
{
	return account_number_;
}

int Transaction::GetFundID() const
{
	return fund_number_;
}

int Transaction::GetTransferAccountID() const
{
	return transfer_account_number_;
}

int Transaction::GetTransferFund() const
{
	return transfer_fund_;
}

int Transaction::GetAmount() const
{
	return amount_;
}

ostream& operator<<(ostream& out_stream, const Transaction& trans)
{
	if (trans.trans_fail_.empty()== true)
	{
		if (trans.GetTranscationType() == 'D' || trans.GetTranscationType() == 'd' || trans.GetTranscationType() == 'W' || trans.GetTranscationType() == 'w')
		{
			out_stream << " " << trans.GetTranscationType() << " " << trans.GetAccountID() << trans.GetFundID() << " "  << trans.GetAmount();
		}
		else if (trans.GetTranscationType() == 'T' || trans.GetTranscationType() == 't')
		{
			out_stream << " " << trans.GetTranscationType() << " " << trans.GetAccountID() << trans.GetFundID() << " " << trans.GetAmount() << " " << trans.GetTransferAccountID() << trans.GetTransferFund();
		}
	}
	else
	{
		if (trans.GetTranscationType() == 'D' || trans.GetTranscationType() == 'd' || trans.GetTranscationType() == 'W' || trans.GetTranscationType() == 'w')
		{
			out_stream << " " << trans.GetTranscationType() << " " << trans.GetAccountID() << trans.GetFundID() << " " << trans.GetAmount() << " (FAILED)";
		}
		else if (trans.GetTranscationType() == 'T' || trans.GetTranscationType() == 't')
		{
			out_stream << " " << trans.GetTranscationType() << " " << trans.GetAccountID() << trans.GetFundID() << " " << trans.GetAmount() << " " << trans.GetTransferAccountID() << trans.GetTransferFund() << "(FAILED)";
		}
	}
	return out_stream << endl;
}
