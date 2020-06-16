#include <string>
#include<iostream>
#include<vector>
#include "account.h"

using namespace std;
//constructor
Account::Account(int ClientID, string FName, string LName) {
  ID = ClientID;
  FirstName = FName;
  LastName = LName;
  for (int I = 0; I < MAX_ACCOUNTS; I++) {
    THistory[I] = new vector<string>();
    Funds[I] = 0;
  }
}
//destructor
Account::~Account() {
  for (auto &I : THistory) {
    for (unsigned int J = 0; J < I->size(); J++) {
      I->clear();
    }
    delete I;
  }
}
//withdraws funds from a specified account
//@param int Fund - the specific fund to wothdraw funds from
//@param int Amount - the sum to be withdrawn
//return boolean whether the transaction was a success
bool Account::withdrawal(int Fund, int Amount) {
  bool Output = false;
  stringstream ClntMsg;
  switch (Fund) {
  case 0:
    if (Amount > Funds[0]) {
      if ((Amount - Funds[Fund]) > Funds[1]) {
        Output = false;
      } else {
        Funds[1] -= (Amount - Funds[Fund]);
        Funds[Fund] = 0;
        ClntMsg << "Withdrew $" << Amount;
        Output = true;
      }
    } else {
      Funds[0] -= Amount;
      ClntMsg << "Withdrew $" << Amount;
      Output = true;
    }
    break;
    //Accounts 0-3 can share funds
  case 1:
    if (Amount > Funds[1]) {
      if ((Amount - Funds[Fund]) > Funds[0]) {
        Output = false;
      } else {
        Funds[0] -= (Amount - Funds[1]);
        Funds[1] = 0;
        ClntMsg << "Withdrew $" << Amount;
        Output = true;
      }
    } else {
      Funds[1] -= Amount;
      ClntMsg << "Withdrew $" << Amount;
      Output = true;
    }
    break;

  case 2:
    if (Amount > Funds[2]) {
      if ((Amount - Funds[Fund]) > Funds[3]) {
        Output = false;
      } else {
        Funds[3] -= (Amount - Funds[2]);
        Funds[2] = 0;
        ClntMsg << "Withdrew $" << Amount;
        Output = true;
      }
    } else {
      Funds[2] -= Amount;
      ClntMsg << "Withdrew $" << Amount;
      Output = true;
    }
    break;

  case 3:
    if (Amount > Funds[3]) {
      if ((Amount - Funds[Fund]) > Funds[2]) {
        Output = false;
      } else {
        Funds[2] -= (Amount - Funds[3]);
        Funds[3] = 0;
        ClntMsg << "Withdrew $" << Amount;
        Output = true;
      }
    } else {
      Funds[3] -= Amount;
      ClntMsg << "Withdrew $" << Amount;
      Output = true;
    }
    break;
  default:
    if (Funds[Fund] < Amount) {
      Output = false;
    } else {
      Funds[Fund] -= Amount;
      ClntMsg << "Withdrew $" << Amount;
    }
    break;
  }
  THistory[Fund]->push_back(ClntMsg.str());
  return Output;
}
//deposits funds to a specified account
//@param int Fund - the specific fund to deposit funds
//@param int Amount - the sum to be deposited
//return boolean whether the transaction was a success
bool Account::deposit(int Fund, int Amount) {
  stringstream ClntMsg;
  if (Fund < 10 && Amount > -1) {
    Funds[Fund] += Amount;
    ClntMsg << "Deposited $" << Amount;
    THistory[Fund]->push_back(ClntMsg.str());
    return true;
  }
  return false;
}
//Transfers money from account, and transfers to provided account
//@param int - the specific fund to withdraw funds from/
//@param int - the sum to be transferred
//@param *Account  The recipient account
//@param int - the fund to move funds into
//return boolean whether the transaction was a success
bool Account::transfer(int Fund, int Amount, Account *&Acc, int RFund) {
  bool Output = false;
  stringstream ClntMsg(""), RcpntMsg("");

  switch (Fund) {
  case 0:
    if (Amount > Funds[Fund]) {
      if ((Amount - Funds[Fund]) > Funds[Fund + 1]) {
        cout<< "**************************************************************";
        cout << "ERROR: There are not enough funds for Transfer from account "
             << (ID * 10 + Fund) << endl;
        cout<< "**************************************************************";
        Output = false;
      } else {
        Funds[Fund + 1] -= (Amount - Funds[0]);
        Funds[Fund] = 0;
        Acc->Funds[RFund] += Amount;
        ClntMsg << "Transfer of $" << Amount << " to "
                << (Acc->ID * 10 + RFund);
        RcpntMsg << "Transfer of $" << Amount << " from " << (ID * 10 + Fund);
        THistory[0]->push_back(ClntMsg.str());
        Output = true;
      }
    } else {
      Funds[0] -= Amount;
      Acc->Funds[RFund] += Amount;
      ClntMsg << "Transfer of $" << Amount << " to " << (Acc->ID * 10 + RFund);
      RcpntMsg << "Transfer of $" << Amount << " from " << (ID * 10 + Fund);
      Output = true;
    }
    break;

  case 1:
    if (Amount > Funds[Fund]) {
      if ((Amount - Funds[Fund]) > Funds[Fund - 1]) {
        cout<< "**************************************************************";
        cout << "ERROR: There are not enough funds for Transfer from account "
             << (ID * 10 + Fund) << endl;
        cout<< "**************************************************************";
        Output = false;
      } else {
        Funds[Fund - 1] -= (Amount - Funds[Fund]);
        Funds[Fund] = 0;
        Acc->Funds[RFund] += Amount;
        ClntMsg << "Transfer of $" << Amount << " to "
                << (Acc->ID * 10 + RFund);
        RcpntMsg << "Transfer of $" << Amount << " from " << (ID * 10 + Fund);
        Output = true;
      }
    } else {
      Funds[Fund] -= Amount;
      Acc->Funds[RFund] += Amount;
      ClntMsg << "Transfer of $" << Amount << " to " << (Acc->ID * 10 + RFund);
      RcpntMsg << "Transfer of $" << Amount << " from " << (ID * 10 + Fund);
      Output = true;
    }
    break;

  case 2:
    if (Amount > Funds[Fund]) {
      if ((Amount - Funds[Fund]) > Funds[Fund + 1]) {
        cout<< "**************************************************************";
        cout << "ERROR: There are not enough funds for Transfer from account "
             << (ID * 10 + Fund) << endl;
        cout<< "**************************************************************";
        Output = false;
      } else {
        Funds[Fund + 1] -= (Amount - Funds[Fund]);
        Funds[Fund] = 0;
        Acc->Funds[RFund] += Amount;
        ClntMsg << "Transfer of $" << Amount << " to "
                << (Acc->ID * 10 + RFund);
        RcpntMsg << "Transfer of $" << Amount << " from " << (ID * 10 + Fund);
        Output = true;
      }
    } else {
      Funds[Fund] -= Amount;
      Acc->Funds[RFund] += Amount;
      ClntMsg << "Transfer of $" << Amount << " to " << (Acc->ID * 10 + RFund);
      RcpntMsg << "Transfer of $" << Amount << " from " << (ID * 10 + Fund);
      Output = true;
    }
    break;

  case 3:
    if (Amount > Funds[Fund]) {
      if ((Amount - Funds[Fund]) > Funds[Fund - 1]) {
        cout<< "**************************************************************";
        cout << "ERROR: There are not enough funds for transfer from account "
             << (ID * 10 + Fund) << endl;
        cout<< "**************************************************************";
        Output = false;
      } else {
        Funds[Fund - 1] -= (Amount - Funds[Fund]);
        Funds[Fund] = 0;
        Acc->Funds[RFund] += Amount;
        ClntMsg << "Transfer of $" << Amount << " to "
                << (Acc->ID * 10 + RFund);
        RcpntMsg << "Transfer of $" << Amount << " from " << (ID * 10 + Fund);
        Output = true;
      }
    } else {
      Funds[Fund] -= Amount;
      Acc->Funds[RFund] += Amount;
      ClntMsg << "Transfer of $" << Amount << " to " << (Acc->ID * 10 + RFund);
      RcpntMsg << "Transfer of $" << Amount << " from " << (ID * 10 + Fund);
      Output = true;
    }
    break;

  default:
    if (Funds[Fund] < Amount) {
      cout<< "**************************************************************";
      cout << "ERROR: There are not enough funds for Transfer from account "
           << (ID * 10 + Fund) << endl;
      cout<< "**************************************************************";
      Output = false;
    } else {
      Funds[Fund] -= Amount;
      Acc->Funds[RFund] += Amount;

      ClntMsg << "Transfer of $" << Amount << " to " << (Acc->ID * 10 + RFund);
      RcpntMsg << "Transfer of $" << Amount << " from " << (ID * 10 + Fund);
    }
  }
  THistory[Fund]->push_back(ClntMsg.str());
  Acc->THistory[RFund]->push_back(RcpntMsg.str());
  return Output;
}
//displays all the current balances in the account
void Account::displayBalances() {
  cout << FirstName << " " << LastName << ". ID: " << ID << endl;
  for (int I = 0; I < 10; I++) {
    cout << "\t";
    switch (I) {
    case 0:cout << "Money Market Fund: $";
      break;
    case 1:cout << "Prime Money Market Fund: $";
      break;
    case 2:cout << "Long-Term Bond Fund: $";
      break;
    case 3:cout << "Short-Term Bond Fund: $";
      break;
    case 4:cout << "500 Index Fund: $";
      break;
    case 5:cout << "Capital Value Fund: $";
      break;
    case 6:cout << "Growth Equity Fund: $";
      break;
    case 7:cout << "Growth Index Fund: $";
      break;
    case 8:cout << "Value Fund: $";
      break;
    case 9:cout << "Value Stock Index: $";
      break;
    default:break;
    }
    cout << Funds[I] << endl;
  }
}
//Displays a specific funds history and balance
//@param int Fund - the specific fund to show
void Account::displayH(int Fund) {
  switch (Fund) {
  case 0:cout << "Money Market Fund: $";
    break;
  case 1:cout << "Prime Money Market Fund: $";
    break;
  case 2:cout << "Long-Term Bond Fund for: ";
    break;
  case 3:cout << "Short-Term Bond Fund: $";
    break;
  case 4:cout << "500 Index Fund: $";
    break;
  case 5:cout << "Capital Value Fund: $";
    break;
  case 6:cout << "Growth Equity Fund: $";
    break;
  case 7:cout << "Growth Index Fund: $";
    break;
  case 8:cout << "Value Fund: $";
    break;
  case 9:cout << "Value Stock Index: $";
    break;
  default:break;
  }
  cout << Funds[Fund] << endl;
  for (const auto & I : *THistory[Fund]) {
    cout << "\t" << I << endl;
  }
}
//Displays the History of every fund in the account
void Account::displayAllH() {
  cout << "Displaying Transaction History for " << FirstName << " " << LastName
       << "by fund" << endl;
  for (int I = 0; I < MAX_ACCOUNTS; I++) {
    displayH(I);
  }
}
