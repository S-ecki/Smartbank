#ifndef BANK_H
#define BANK_H
#include"person.h"
#include"account.h"
using namespace std;

class Bank{
    map<string,shared_ptr<Person>> customers;
    map<int,shared_ptr<Account>> accounts;
public:
    Bank();
    void create_person(string name,int nr,int balance,int limit,int mode,double fee_factor);
    ostream& print_customers(ostream& o) const;
    ostream& print_accounts(ostream& o) const;
    shared_ptr<Person> get_person(string n);
    shared_ptr<Account> get_account(int n);
    bool remove_person(string n);
    bool remove_account(int n);
};

#endif