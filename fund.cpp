#include "fund.h"


Fund::Fund()
{
	balance_ = 0;
}

Fund::~Fund()
{
}

bool Fund::AddAmount(int amount_add)
{
	balance_ += amount_add;
	return true;
}

bool Fund::SubtractAmount(int amount_sub)
{
	balance_ -= amount_sub;
	return true;
}

bool Fund::BalanceCheck(int amount_sub)
{
	if (balance_ >= amount_sub)
	{
		return true;
	}
	return false;
}

bool Fund::RecordTrans(Transaction trans)
{
	history_.push_back(trans);
	return true;
}

void Fund::PrintHistory()
{
	if (history_.size() == 0)
	{
		return;
	}
	else
	{
		cout << fund_name_ << ": $" << balance_ << endl;
		for (int i = 0; i < history_.size(); i++)
		{
			cout << " " << history_[i];
		}
	}
}

void Fund::PrintHistoryOfFund()
{
	for (int i = 0; i < history_.size(); i++)
	{
		cout << " " << history_[i];
	}
}

void Fund::SetName(string fund_name)
{
	fund_name_ = fund_name;
}

string Fund::GetName() const
{
	return fund_name_;
}

int Fund::GetBalance() const
{
	return balance_;
}
