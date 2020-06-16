
#ifndef ASS5_ACCOUNTTREE_H
#define ASS5_ACCOUNTTREE_H

#include <iostream>
#include "account.h"
using namespace std;

class AccountTree {
public:
  // Create BST
  AccountTree();

  // Delete all nodes in BST
  ~AccountTree();

  // Insert new account
  bool insert(Account *NewAcc);

  // Retrieve account
  // returns true if successful AND *Account points to account
  bool retrieve(const int &AccountNumber, Account *&NewAcc) const;

  // Display information on all accounts
  void display();

  // delete all information in AccountTree
  void clear();

  // check if tree is empty
  bool isEmpty() const;
  class Node {
  public:
    explicit Node(Account *Acc): Acc{Acc}, Right{nullptr}, Left{nullptr}{};
    Account *Acc;
    Node *Right;
    Node *Left;
  };
private:

  Node *Root;
  static bool insertHelper(Node *&STRoot, Account *&NewAcc);
  bool retrieveHelper(Node *STRoot, const int AccountNumber, Account *&NewAcc)const;
  void displayHelper(Node *STRoot);
  void clearHelper(Node *STRoot);
};
#endif // ASS5_ACCOUNTTREE_H
