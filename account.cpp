#include "account.h"
Account::Account()
{
	account_ID_ = 0;
	fund_ID_ = 0;
}

Account::Account(string first_name, string last_name, int account_ID)
{
	first_name_ = first_name;
	last_name_ = last_name;
	account_ID_ = account_ID;
	string fund_names[] = { "Money Market", "Prime Money Market","Long-Term Bond", "Short-Term Bond","500 Index Fund", "Capital Value Fund","Growth Equity Fund", "Growth Index Fund","Value Fund", "Value Stock Index" };
	for (int i = 0; i < 10; i++)
	{
		array_fund_[i].SetName(fund_names[i]);
	}
}

Account::~Account()
{
}

void Account::AddToAcc(int fund_num, int amount)
{
	array_fund_[fund_num].AddAmount(amount);
}

bool Account::DeductFunds(int fund_num, int amount, Transaction trans)
{
	if (fund_num == MONEY_MARKET || fund_num == PRIME_MONEY_MARKET || fund_num == LONG_TERM_BOND || fund_num == SHORT_TERM_BOND)
	{
		if (fund_num == MONEY_MARKET || fund_num == PRIME_MONEY_MARKET)
		{
			if (array_fund_[fund_num].BalanceCheck(amount))
			{
				array_fund_[fund_num].SubtractAmount(amount);
				array_fund_[fund_num].RecordTrans(trans);
				return true;
			}
			else if (((array_fund_[MONEY_MARKET].GetBalance() + array_fund_[PRIME_MONEY_MARKET].GetBalance()) >= amount))
			{
				if (fund_num == MONEY_MARKET)
				{
					WidthFromSimilarAcct(MONEY_MARKET, PRIME_MONEY_MARKET, amount);
				}
				else
				{
					WidthFromSimilarAcct(PRIME_MONEY_MARKET, MONEY_MARKET, amount);
				}
			}
			else
			{
				DisplayError(amount, GetFirstName(), GetLastName(), fund_num);
				if (fund_num == MONEY_MARKET)
				{
					WidthFromSimilarAcct(MONEY_MARKET, PRIME_MONEY_MARKET, amount);
				}
				else
				{
					WidthFromSimilarAcct(PRIME_MONEY_MARKET, MONEY_MARKET, amount);
				}
				return false;
			}
		
		}
		else if (fund_num == LONG_TERM_BOND || fund_num == SHORT_TERM_BOND)
		{
			if (array_fund_[fund_num].BalanceCheck(amount))
			{
				array_fund_[fund_num].SubtractAmount(amount);
				array_fund_[fund_num].RecordTrans(trans);
				return true;
			}
			else if (((array_fund_[LONG_TERM_BOND].GetBalance() + array_fund_[SHORT_TERM_BOND].GetBalance()) >= amount))
			{
				if (fund_num == LONG_TERM_BOND)
				{
					WidthFromSimilarAcct(LONG_TERM_BOND, SHORT_TERM_BOND, amount);
				}
				else
				{
					WidthFromSimilarAcct(SHORT_TERM_BOND, LONG_TERM_BOND, amount);
				}
			}
			else
			{
				DisplayError(amount, GetFirstName(), GetLastName(), fund_num);
				if (fund_num == LONG_TERM_BOND)
				{
					WidthFromSimilarAcct(LONG_TERM_BOND, SHORT_TERM_BOND, amount);
				}
				else
				{
					WidthFromSimilarAcct(SHORT_TERM_BOND, LONG_TERM_BOND, amount);
				}
				return false;
			}
		}
	}
	else
	{
		if (array_fund_[fund_num].BalanceCheck(amount))
		{
			array_fund_[fund_num].SubtractAmount(amount);
			array_fund_[fund_num].RecordTrans(trans);
			return true;
		}
		else
		{
			DisplayError(amount, GetFirstName(), GetLastName(), fund_num);
			return false;
		}
	}
	return true;
}

void Account::RecordTransactions(Transaction trans, int fund_num)
{
	array_fund_[fund_num].RecordTrans(trans);
}

void Account::WidthFromSimilarAcct(int primary_fund, int secondary_fund, int amount)
{
	if (((array_fund_[primary_fund].GetBalance() + array_fund_[secondary_fund].GetBalance()) >= amount))
	{
		int available_balance = array_fund_[primary_fund].GetBalance();
		array_fund_[primary_fund].SubtractAmount(available_balance);
		Transaction trans('W', GetAccountID(), primary_fund, available_balance);
		array_fund_[primary_fund].RecordTrans(trans);
		amount -= available_balance;
		array_fund_[secondary_fund].SubtractAmount(amount);
		Transaction trans2('W', GetAccountID(), secondary_fund, amount);
		array_fund_[secondary_fund].RecordTrans(trans2);
	}
	else
	{
		int available_balance = array_fund_[primary_fund].GetBalance();
		if (available_balance > amount)
		{
			array_fund_[primary_fund].SubtractAmount(available_balance);
			Transaction trans('W', GetAccountID(), primary_fund, available_balance);
			array_fund_[primary_fund].RecordTrans(trans);
			amount -= available_balance;
		}
		if (array_fund_[secondary_fund].BalanceCheck(amount))
		{
			array_fund_[secondary_fund].SubtractAmount(amount);
			Transaction trans('W', GetAccountID(), secondary_fund, amount);
			array_fund_[secondary_fund].RecordTrans(trans);
		}
		else
		{
			cout << "ERROR: Not Enough Funds To Withdraw " << amount << " from " << GetFirstName() << " " << GetLastName() << " " << GetFundName(secondary_fund) << endl;
			Transaction trans('W', GetAccountID(), secondary_fund, amount, "Failed");
			array_fund_[secondary_fund].RecordTrans(trans);
		}
	}
}

void Account::DisplayHistory()
{
	cout << "Transaction History For: " << first_name_ << " " << last_name_ << " " << "By Fund." << endl;
	for (int i = 0; i < 10; i++)
	{
		array_fund_[i].PrintHistory();
	}
}

void Account::DisplayFundHistory(int fund_number)
{
	cout << "Transaction History For: " << first_name_ << " " << last_name_ << " " << GetFundName(fund_number) << " $" << GetBalance(fund_number) << endl;
	array_fund_[fund_number].PrintHistoryOfFund();
}

void Account::DisplayError(int amount, string first_name, string last_name, int fund_num)
{
	cout << "ERROR: Not Enough Funds To Withdraw " << amount << " from " << first_name << " " << last_name << " " << GetFundName(fund_num) << endl;
	Transaction ErrorTrans('W', GetAccountID(), fund_num, amount, "Failed");
	array_fund_[fund_num].RecordTrans(ErrorTrans);
}

int Account::GetAccountID() const
{
	return account_ID_;
}

int Account::GetBalance(int fund_num) const
{
	return array_fund_[fund_num].GetBalance();
}

string Account::GetFundName(int fund_num)
{
	return array_fund_[fund_num].GetName();
}

string Account::GetFirstName() const
{
	return first_name_;
}

string Account::GetLastName() const
{
	return last_name_;
}

void Account::SetFundID(int fund_num)
{
	fund_ID_ = fund_num;
}

ostream& operator<<(ostream& out_stream, Account& rhs)
{
	out_stream << rhs.GetFirstName() << " " << rhs.GetLastName() << " ID: " << rhs.GetAccountID() << endl;
	for (int i = 0; i < 10; i++)
	{
		out_stream << " " << rhs.GetFundName(i) << " :$" << rhs.GetBalance(i);
		out_stream << endl;
	}
	return out_stream;
}
