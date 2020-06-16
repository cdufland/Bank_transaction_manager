#include <iostream>
#include <string>
#include<cassert>
#include "bank.h"
#include "account.h"
#include "accounttree.h"



using namespace std;
void treeTest(){
  AccountTree tree;
  Account *myAcc = new Account(1234,  "Cameron",  "Ufland");
  myAcc->deposit(5, 1000);
  assert(!myAcc->withdrawal(5,2000));
  myAcc->displayH(5);
  assert(tree.insert(myAcc));
  myAcc = nullptr;
  myAcc = new Account(2222, "Angela", "Caperro");
  assert(tree.insert(myAcc));
  myAcc = nullptr;
  assert(tree.retrieve(2222, myAcc));
  assert(myAcc->ID == 2222);
  assert(!tree.insert(myAcc));
  assert(tree.retrieve(1234, myAcc));
  assert(myAcc->ID == 1234);
  tree.display();
}
int main(int Argc, char *Argv[]) {
  Bank Bank;
  //Note that tests were done in BankTransIn.txt
  for(int I = 1; I < Argc; ++I) {
    cout << "The command line argument(s) was " << Argv[I] << std::endl;
    string FileName = Argv[I];
    cout << FileName;
    Bank.processTransactions(FileName);
  }
  Bank.processTransactions("BankTransin.txt");
  cout << "Done" << endl;

  treeTest();

  return 0;

}