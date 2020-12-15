#ifndef PERSON_H
#define PERSON_H
#include"account.h"
using namespace std;

class Account;

class Person : public enable_shared_from_this<Person>{
    string name;
    map<int,weak_ptr<Account>> accounts;
public:
    Person(string name);
    shared_ptr<Account> create_account(int nr, int balance, int limit, int mode, double fee_factor);
    string get_name() const;
    size_t number_of_accounts() const;
    vector<int> get_account_nrs() const;
    bool share_account(shared_ptr<Person> other,int nr);
    ostream& print(ostream& o) const;
    shared_ptr<Person> pers_get_shared() { return shared_from_this(); }
    void insert_acc(shared_ptr<Account>);
};

#endif