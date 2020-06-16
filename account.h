
#ifndef ASS5_ACCOUNT_H
#define ASS5_ACCOUNT_H
#include<iostream>
#include<vector>
#include <string>
#include<sstream>


using namespace std;

class Account {
public:

  Account(int ClientID, string FName, string LName);


  //friend ostream &operator<<(ostream &Out, Account &Acc);

  ~Account();

  bool withdrawal(int Fund, int Amount);
  bool deposit(int Fund, int Amount);
  void displayBalances();
  void displayH(int Fund);
  void displayAllH();
  bool transfer(int Fund, int Amount, Account *&Acc, int RFund);
  int ID;
  string FirstName;
  string LastName;
private:

  static const int MAX_ACCOUNTS = 10;
  int Funds[MAX_ACCOUNTS];
  vector<string> *THistory[MAX_ACCOUNTS];

};
#endif // ASS5_ACCOUNT_H
