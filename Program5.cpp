
#include <iostream>
#include "account.h"
#include "binary_search_tree.h"
#include "jolly_banker.h"
#include "fund.h"
#include "transaction.h"

using namespace std;

int main()
{
    JollyBanker bank;
    bank.ReadTransactions();
    bank.ExecuteTransactions();
    bank.Display();

    system("pause");
    return 0;
}
