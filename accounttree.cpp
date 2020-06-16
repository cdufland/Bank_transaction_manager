#include<cassert>
#include "accounttree.h"
#include "account.h"
using namespace std;

AccountTree::AccountTree() {
  Root = nullptr;
}


// Delete all nodes in BST
AccountTree::~AccountTree() {
  clear();
}
//Helper function for recursive insert
//@param *&Node the root of the given subtree
//@param *&Account the new account to be inserted into the tree
//return boolean Returns False if the account is already in the tree
bool AccountTree::insertHelper(Node *&STRoot, Account *&NewAcc) {
  bool IsInsert = false;
  if (NewAcc->ID == STRoot->Acc->ID) {
    cout << "ERROR: Account " << NewAcc->ID << " already exists" << endl;
    IsInsert = false;
  }
  if (NewAcc->ID > STRoot->Acc->ID) {
    if (STRoot->Right != nullptr) {
      insertHelper(STRoot->Right, NewAcc);
    } else {
      STRoot->Right = new Node(NewAcc);
      IsInsert = true;
    }
  }
  if (NewAcc->ID < STRoot->Acc->ID) {
    if (STRoot->Left != nullptr) {
      insertHelper(STRoot->Left, NewAcc);
    } else {
      STRoot->Left = new Node(NewAcc);
      IsInsert = true;
    }
  }
  return IsInsert;
}
//Helper function for recursive retrieve
//@param *&Node the root of the given subtree
//@param int the ID of the Account being retrieved
//@param *Account pointer to point to the located account
//return boolean Returns False if the account is not in the tree
bool AccountTree::retrieveHelper(Node *STRoot, const int AccountNumber,
                                 Account *&NewAcc ) const {
  if (STRoot == nullptr) {
    NewAcc = nullptr;
    return false;
  }
  if (STRoot->Acc->ID == AccountNumber) {
    NewAcc = STRoot->Acc;
    return true;
  }
  if(STRoot->Acc->ID < AccountNumber) {
      return retrieveHelper(STRoot->Right, AccountNumber, NewAcc);
    }
      return retrieveHelper(STRoot->Left, AccountNumber, NewAcc);
    }
// Insert new account
  bool AccountTree::insert(Account *NewAcc) {
    if(isEmpty()){
      Root = new Node (NewAcc);
      return true;
    }
    return insertHelper(Root, NewAcc);
    }
// Retrieve account Recursive calls retrieve helper
// returns true if successful AND *Account points to account
bool AccountTree::retrieve(const int &AccountNumber, Account *&NewAcc) const {
  if(!isEmpty()  && Root->Acc->ID == AccountNumber){
    NewAcc = Root->Acc;
    return true;
  }
    return retrieveHelper(Root, AccountNumber, NewAcc) ;

}

// Display information on all accounts
//recursive, in order traversal
void AccountTree::display(){
  Node *CurrNode = Root;
    displayHelper(CurrNode);
  }
//Helper function for recursive display
//@param *&Node the root of the given subtree
void AccountTree::displayHelper(Node *STRoot){
 if(STRoot == nullptr) {
   return;
 }
  displayHelper(STRoot->Left);
  STRoot->Acc->displayBalances();
  displayHelper(STRoot->Right);
}
// delete all information in AccountTree calls clearHelper(node)
//in order traversal
void AccountTree::clear() {
  if (Root == nullptr) {
    cout << "Tree is Empty" << endl;
    return;
  }
  clearHelper(Root->Left);
  Node *Temp = Root->Right;
  delete Root->Acc;
  delete Root;
  clearHelper(Temp);
}
//Helper function for recursive clearHelper; in order traversal
//@param *&Node the root of the given subtree
void AccountTree::clearHelper(Node *STRoot){
  if(STRoot == nullptr) {
    return;
  }
  clearHelper(STRoot->Left);
  Node *Temp = STRoot->Right;
  delete STRoot->Acc;
  delete STRoot;
  clearHelper(Temp);

}
// check if tree is empty
bool AccountTree::isEmpty() const {
  return Root == nullptr;
}


