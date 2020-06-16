#include <cassert>
#include "bank.h"


//constructor
Bank::Bank() = default;

//destructor
Bank::~Bank() = default;
//Reads in a file to open, parses it into a transaction, loads into queue, pops them off and processes all transactions
//@param &FileName the name of a file to open
void Bank::processTransactions(const string &FileName) {
  parseTransactions(FileName);
  assert(!TQueue.empty());
  while(!TQueue.empty()){
    handleTransaction(TQueue.front());
    TQueue.pop();
  }
  displayAllBankBalances();
}
//Reads file into specific variables to be loaded into queue
//@param &FileName the name of a file to be opened
void Bank::parseTransactions(const string &FileName) {
  ifstream MyFile;
  MyFile.open(FileName);
  if(!MyFile){
    cout << "Error: Could not read file" << endl;
    return;
  }
  while (!MyFile.eof()) {
    Transaction CurrTran;
    MyFile >> CurrTran.Type;
    int IDAccount;
    switch (CurrTran.Type) {
      case 'O':
        MyFile >> CurrTran.LastName;
        MyFile >> CurrTran.FirstName;
        MyFile >> IDAccount;
        if(IDAccount < MinIdLength || IDAccount > MaxIdLength/10){
          cout << "ERROR: Account Number invalid" << endl;
        }
        CurrTran.ClientID = IDAccount;
        break;

      case 'D':
        MyFile >> IDAccount;
        CurrTran.ClientID = IDAccount / 10;
        CurrTran.Fund = IDAccount % 10;
        MyFile >> CurrTran.Amount;
        break;

      case 'H':
        MyFile >> IDAccount;
        if(IDAccount>999 && IDAccount < 10000) {
          CurrTran.ClientID = IDAccount;
        }else if(IDAccount > 9999 && IDAccount < 100000){
          CurrTran.ClientID = IDAccount/10;
          CurrTran.Fund = IDAccount%10;
        }else{
          cout<< "Cant process transaction" << endl;
          continue;
        }
        break;

      case 'W':
        MyFile >> IDAccount;
        CurrTran.ClientID = IDAccount / 10;
        CurrTran.Fund = IDAccount % 10;
        MyFile >> CurrTran.Amount;
        break;

      case 'T':
        MyFile >> IDAccount;
        CurrTran.ClientID = IDAccount / 10;
        CurrTran.Fund = IDAccount % 10;
        MyFile >> CurrTran.Amount;
        MyFile >> IDAccount;
        CurrTran.RecipientID = IDAccount / 10;
        CurrTran.RecipientFund = IDAccount %10;
        break;
    default:
      cout<< "ERROR could not process transaction";
    }
    TQueue.push(CurrTran);
  }
MyFile.close();
}
//after transactions are popped off queue, they are processed into specific banking functions
//@param &CurrTrans the current transaction being processed
void Bank::handleTransaction(Bank::Transaction &CurrTrans) {
  switch(CurrTrans.Type){
    case 'O':
      openAccount(CurrTrans);
      break;
    case 'D':
      deposit(CurrTrans);
      break;
    case 'H':
      displayHistory(CurrTrans);
      break;
    case 'W':
      withdraw(CurrTrans);
      break;
    case 'T':
      transfer(CurrTrans);
      break;

  }
}
//opens an account with the information in the provided transaction
//@param &CurrTrans The transaction with all information to open an account
//return bool true if opened account
bool Bank::openAccount(Bank::Transaction &CurrTrans) {
  Account *myAcc = nullptr;
  if(AccTree.retrieve(CurrTrans.ClientID, myAcc)){
    cout << "Error: ACCOUNT " <<  CurrTrans.ClientID << " ALREADY EXISTS" << endl; ;
    return false;
  }
  assert(myAcc == nullptr);
  myAcc = new Account(CurrTrans.ClientID, CurrTrans.FirstName, CurrTrans.LastName);
  if(AccTree.insert(myAcc)){
    return true;
  }
  myAcc = nullptr;
  return false;
}

bool Bank::deposit(Bank::Transaction &CurrTrans) {
  Account *MyAcc;
  checkID(CurrTrans.ClientID);
  if(!AccTree.retrieve(CurrTrans.ClientID, MyAcc)){
    cout << "ERROR: Could not find account";
  }
  if(MyAcc->deposit(CurrTrans.Fund, CurrTrans.Amount)){
    return true;
  }
  cout<<"ERROR: Could not process deposit";
  return false;
}

//withdraws funds based on the transaction provided
//@param CurrTrans transaction with all withdrawal information
//returns bool true if withdrawal was successful
bool Bank::withdraw(Bank::Transaction &CurrTrans) {
  Account *MyAcc;
  if(AccTree.retrieve(CurrTrans.ClientID, MyAcc)){
    MyAcc->withdrawal(CurrTrans.Fund, CurrTrans.Amount);
    return true;
  }
  return false;
}
//transfers funds based on the transaction provided
//@param CurrTrans transaction with all transfer information
//returns bool true if transfer was successful
bool Bank::transfer(Bank::Transaction &CurrTrans) {
  Account *MyAcc, *RecipientAcc;
  bool Output = false;
  if(AccTree.retrieve(CurrTrans.ClientID, MyAcc) &&
     AccTree.retrieve(CurrTrans.RecipientID, RecipientAcc)) {
      assert(MyAcc != nullptr);
      MyAcc->transfer(CurrTrans.Fund, CurrTrans.Amount, RecipientAcc,
                      CurrTrans.RecipientFund);
    Output= true;
  }
  return Output;
}
//displays funds history based on the transaction provided
//can print one specific fund or all funds history
//@param CurrTrans transaction with all History information
void Bank::displayHistory(Bank::Transaction &CurrTrans) {
  Account *MyAcc;
  if (AccTree.retrieve(CurrTrans.ClientID, MyAcc)) {
    if (CurrTrans.Fund > -1) {
      cout << "Displaying History for " << MyAcc->FirstName << " " << MyAcc->LastName << "'s ";
      MyAcc->displayH(CurrTrans.Fund);
    } else {
      MyAcc->displayAllH();
    }
  }
  //cout << "ERROR: Could not display account";
}
//prints out all balances of every open account
void Bank::displayAllBankBalances() {
  cout<< "Processing Done. Final Balances." << endl;
  AccTree.display();
  cout << "Good Night" << endl;
}
//helper method checks the ID to make sure its the proper length
//used only after ID has been parsed into transaction
//returns bool true if the number is valid
bool Bank::checkID(int IDNumber){
  if(IDNumber < MinIdLength || IDNumber> MaxIdLength/10){
    cout << "Invalid Id Number";
    return false;
  }
  return true;
}