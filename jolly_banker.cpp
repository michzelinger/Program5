#include "jolly_banker.h"
#include "transaction.h"
#include "account.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <queue>
#include <math.h>

JollyBanker::JollyBanker()
{
}

JollyBanker::~JollyBanker()
{
}

bool JollyBanker::ReadTransactions()
{
    ifstream in("BankTransIn.txt");
    string ReadLine;
    if (!in)
    {
        cout << "File Cannot Be Opened!" << endl;
    }
    while (!in.eof())
    {
        getline(in, ReadLine);
        if (ReadLine.empty())
        {
            break;
        }
        istringstream ParseLine(ReadLine);
        char TransactionType;
        ParseLine >> TransactionType;
        if (TransactionType == 'O' || TransactionType == 'o')
        {
            string last_name, first_name;
            int account_ID;
            ParseLine >> last_name >> first_name >> account_ID;
            Transaction trans(TransactionType, last_name, first_name, account_ID);
            transaction_list_.push(trans);
        }
		else if (TransactionType == 'W' || TransactionType == 'w' || TransactionType == 'D' || TransactionType == 'd')
		{
			int account_ID, fund_ID, amount;
			ParseLine >> account_ID >> amount;
			fund_ID = account_ID % 10;
			account_ID = account_ID / 10;
			Transaction trans(TransactionType, account_ID, fund_ID, amount);
			transaction_list_.push(trans);
		}
		else if (TransactionType == 'T' || TransactionType == 't')
		{
			int account_ID, fund_ID, amount, transfer_account_ID, transfer_fund_ID;
			ParseLine >> account_ID >> amount >> transfer_account_ID;
			fund_ID = account_ID % 10;
			account_ID = account_ID / 10;
			transfer_fund_ID = transfer_account_ID % 10;
			transfer_account_ID = transfer_account_ID / 10;
			Transaction trans(TransactionType, account_ID, fund_ID, amount, transfer_account_ID, transfer_fund_ID);
			transaction_list_.push(trans);
		}
		else if (TransactionType == 'H' || TransactionType == 'h')
		{
			int account_ID, fund_ID;
			ParseLine >> account_ID;
			int length = 0;
			int temp = account_ID;
			do {
				++length;
				temp /= 10;
			} while (temp);
			if (length == 5)
			{
				fund_ID = account_ID % 10;
				Transaction trans(TransactionType, account_ID, fund_ID);
				transaction_list_.push(trans);
			}
			else
			{
				Transaction trans(TransactionType, account_ID);
				transaction_list_.push(trans);
			}
			
		}
		else
		{
			cout << "ERROR!" << endl;
		}
	}
	return false;
    }
void JollyBanker::ExecuteTransactions()
{
	while (!transaction_list_.empty())
	{
		Transaction trans = transaction_list_.front();

		if (trans.GetTranscationType() == 'O' || trans.GetTranscationType() == 'o')
		{
			Account* account = new Account(trans.GetFirstName(), trans.GetLastName(), trans.GetAccountID());
			account_list_.Insert(account);
		}
		else if (trans.GetTranscationType() == 'D' || trans.GetTranscationType() == 'd')
		{
			int accountNumber = trans.GetAccountID();
			int fundNumber = trans.GetFundID();
			int amountToAdd = trans.GetAmount();
			Account* account;
			if (account_list_.Retrieve(accountNumber, account))
			{
				account->AddToAcc(fundNumber, amountToAdd);
				account->RecordTransactions(trans, fundNumber);
			}

		}
		else if (trans.GetTranscationType() == 'W' || trans.GetTranscationType() == 'w')
		{
			int accountNumber = trans.GetAccountID();
			int fundNumber = trans.GetFundID();
			int amountToSubtract = trans.GetAmount();
			Account* account;
			if (account_list_.Retrieve(accountNumber, account))
			{
				//deduct funds records transactions.
				account->DeductFunds(fundNumber, amountToSubtract, trans);
			}

		}
		else if (trans.GetTranscationType() == 'T' || trans.GetTranscationType() == 't')
		{
			int accountNumber = trans.GetAccountID();
			int transferAcctNum = trans.GetTransferAccountID();
			int fundNumber = trans.GetFundID();
			int transferFundNum = trans.GetTransferFund();
			int amountToSub = trans.GetAmount();
			Account* to, * from;
			if (account_list_.Retrieve(accountNumber, to) && account_list_.Retrieve(transferAcctNum, from))
			{
				if (to->DeductFunds(fundNumber, amountToSub, trans))
				{
					from->AddToAcc(transferFundNum, amountToSub);
					from->RecordTransactions(trans, transferFundNum);
				}
				else
				{
					cerr << "ERROR: Not Enought Funds to Transer  " << amountToSub << " " << "from " << from->GetAccountID() << fundNumber << " to " << to->GetAccountID() << transferFundNum << endl;
					Transaction addToHistory('T', accountNumber, fundNumber, amountToSub, transferAcctNum, transferFundNum, "(Failed)");
					from->RecordTransactions(addToHistory, transferFundNum);
				}
			}

		}
		else if (trans.GetTranscationType() == 'H' || trans.GetTranscationType() == 'h')
		{
			if (trans.GetAccountID() >= 10000 && trans.GetAccountID() <= 99999)//5 digits = account number + fund
			{
				Account* account;
				int fundNumPrt = trans.GetAccountID() % 10;
				int acctNumSearch = trans.GetAccountID() / 10;
				if (account_list_.Retrieve(acctNumSearch, account))
				{
					account->DisplayFundHistory(fundNumPrt);
					
				}
			}
			else if (trans.GetAccountID() >= 1000 && trans.GetAccountID() <= 9999)//4 digits = account number
			{
				Account* account;
				int acctNumSearch = trans.GetAccountID();
				if (account_list_.Retrieve(acctNumSearch, account))
				{
					account->DisplayHistory();
					
				}
			}
		}
		transaction_list_.pop();
	}
}

void JollyBanker::Display()
{
	cout << endl;
	cout << "Processing Done. Final Balances" << endl;
	account_list_.Display();
}

