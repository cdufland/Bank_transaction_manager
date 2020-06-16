
#ifndef ASS5_BANK_H
#define ASS5_BANK_H

#include <fstream>
#include <queue>
#include <string>
#include "accounttree.h"
#include "account.h"

using namespace std;

class Bank {
public:
  Bank();
  ~Bank();
  void processTransactions(const string &FileName);
  void displayAllBankBalances();
  struct Transaction{
    char Type;
    int ClientID;
    int Fund = -1;
    string FirstName;
    string LastName;
    int RecipientID;
    int RecipientFund;
    int Amount;
  };
  using Transaction = struct Transaction;
private:
  //Data Fields for Bank
  AccountTree AccTree;
  queue<Transaction> TQueue;
  const int MinIdLength = 1000;
  const int MaxIdLength = 99999;

  void parseTransactions(const string &FileName);
  void handleTransaction(Transaction& CurrTrans);
  bool openAccount(Transaction& CurrTrans);
  bool deposit(Transaction& CurrTrans);
  bool withdraw(Transaction& CurrTrans);
  bool transfer(Transaction& CurrTrans);
  void displayHistory(Transaction& CurrTrans);
  bool checkID(int IDNumber);
};
#endif // ASS5_BANK_H
