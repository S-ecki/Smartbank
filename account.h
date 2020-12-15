#ifndef ACCOUNT_H
#define ACCOUNT_H
#include<map>
#include<memory>
#include<string>
#include<vector>
#include<iostream>
#include "person.h"
using namespace std;

class Person;

class Account : public enable_shared_from_this<Account>{
    int nr;
    int balance;
    int limit;
    map<string, weak_ptr<Person>> persons;
    double fee{0};
    int bonus{0};
public:
    Account(int nr,int balance,int limit,shared_ptr<Person> p);
    virtual ~Account() = default;
    int get_nr() const;
    vector<string> get_authorized_persons() const;
    size_t number_of_owners() const;
    bool add_authorized_person(shared_ptr<Person> p);
    bool transfer(shared_ptr<Account> target,int x);
    virtual double calc_fee(int) const = 0;
    virtual ostream& print(ostream& o) const;
    shared_ptr<Account> acc_get_shared() { return shared_from_this(); }
    void add_fee(int x){ fee += calc_fee(x); }
    void sub_money(int x){ balance -= x; }
    void add_money(int x){ balance += x; }
    int get_balance() { return balance; }
    int get_limit() { return limit; }
    double get_fee() { return fee; }
    int get_bonus()const { return bonus; }
    void set_bonus(int x) { bonus = x; }
    virtual bool calc_bonus() { return false; }
};


class GiroAccount: public Account{
    double fee_factor;
public:
    GiroAccount(int nr,int balance,int limit,shared_ptr<Person> p,double);
    bool add_authorized_person(shared_ptr<Person> p);
    double calc_fee(int) const;
};

class SGiroAccount: public GiroAccount{
public:
    SGiroAccount(int nr,int balance,int limit,shared_ptr<Person> p,double d): GiroAccount(nr, balance, limit, p, d) {}
    bool calc_bonus();
    ostream& print(ostream& o) const override;
};

class BusinessAccount: public Account{
    double fee_factor;
public:
    BusinessAccount(int nr,int balance,int limit,shared_ptr<Person> p,double );
    bool add_authorized_person(shared_ptr<Person> p);
    double calc_fee(int x) const;
};

class SBusinessAccount: public BusinessAccount{
public:
    SBusinessAccount(int nr,int balance,int limit,shared_ptr<Person> p,double d): BusinessAccount( nr,balance, limit, p,d ) {}
    bool calc_bonus();
    ostream& print(ostream& o) const override;
};


class AccountCollection{
    vector<weak_ptr<Account>> v;
public:
    AccountCollection(vector<weak_ptr<Account>> v): v(v) {}
    bool calc_boni();
};

#endif