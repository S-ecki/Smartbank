#include"account.h"
#include "person.h"
#include<stdexcept>
using namespace std;

template<typename T>
shared_ptr<T> check(weak_ptr<T> weak){
    if (auto check = weak.lock()) {
        return check;
    } else {
        return nullptr;
    }
}

Account::Account(int nr,int balance,int limit,shared_ptr<Person> p): nr(nr), balance(balance), limit(limit){
    if(nr<=0) throw runtime_error("nr ungueltig!");
    if(balance<(limit*-1)) throw runtime_error("balance ungueltig!");
    if(limit<0) throw runtime_error("limit ungueltig!");
    persons.insert(pair<string,weak_ptr<Person>> (p->get_name(), p));
}

int Account::get_nr() const{
    return nr;
}

vector<string> Account::get_authorized_persons() const{
    vector<string> list;
    for(auto it{persons.begin()}; it != persons.end(); it++){
        if(check(it->second) == nullptr) continue;
        list.push_back(it->first);
    }
    return list;
}

size_t Account::number_of_owners() const{
    size_t sum{0};
    for(auto it{persons.begin()}; it != persons.end(); it++){
        if(!(it->second.expired())) sum++;
    }
    return sum;
}

bool Account::add_authorized_person(shared_ptr<Person> p){
    auto pr = persons.insert(pair<string, weak_ptr<Person>> (p->get_name(), p));
    bool inserted{get<1>(pr)};
    return inserted;
}
bool GiroAccount::add_authorized_person(shared_ptr<Person> p){
    return Account::add_authorized_person(p);
}
bool BusinessAccount::add_authorized_person(shared_ptr<Person> p){
    return Account::add_authorized_person(p);
}

bool Account::transfer(shared_ptr<Account> target,int x){
    if((balance-x) < (-limit)) return false;

    this->sub_money(x);
    target->add_money(x);

    this->add_fee(x);
    target->add_fee(x);

    return true;
}

ostream& Account::print(ostream& o) const{
    o << "Nr.: " << nr << ", [" << balance << "/" << limit << "], Fees: " << fee << ", Owners: {";
    bool firstt{true};
    for(auto it{persons.begin()}; it != persons.end(); it++){
        if(firstt){
            auto pers_ptr = check(it->second);
            if(pers_ptr == nullptr) continue;
            o << "[Name: " << it->first << ", {";
            auto acc_nrs{pers_ptr->get_account_nrs()};
            bool first{true};
            for(auto itt{acc_nrs.begin()}; itt != acc_nrs.end(); itt++){
                if(first){
                    o << *itt;
                    first = false;
                } 
                else o << ", " << *itt;
            }
            o << "}]";
            firstt = false;
        }
        else{
            auto pers_ptr = check(it->second);
            if(pers_ptr == nullptr) continue;
            o <<", ";
            o << "[Name: " << it->first << ", {";
            auto acc_nrs{pers_ptr->get_account_nrs()};
            bool first{true};
            for(auto itt{acc_nrs.begin()}; itt != acc_nrs.end(); itt++){
                if(first){
                    o << *itt;
                    first = false;
                } 
                else o << ", " << *itt;
            }
            o << "}]";
        }
    }
    o << "}";
    return o;
}

GiroAccount::GiroAccount(int nr,int balance,int limit,shared_ptr<Person> p,double fee_factor): Account(nr, balance, limit, p), fee_factor(fee_factor){
    if(fee_factor<=0) throw runtime_error("fee factor ungueltig");
}

double GiroAccount::calc_fee(int x) const{
    return fee_factor;
}

bool SGiroAccount::calc_bonus(){
    int change{0};
    auto persons{Account::get_authorized_persons()};
    for(auto it{persons.begin()}; it != persons.end(); ++it){
        if((*it).find("la") != string::npos) change = 1;
    }
    int tmp_bonus{get_bonus()};
    set_bonus(get_bonus() + change);
    return tmp_bonus != get_bonus();
}

ostream& SGiroAccount::print(ostream& o) const{
    Account::print(o);
    o << " Bonus: " << Account::get_bonus();
    return o;
}

BusinessAccount::BusinessAccount(int nr,int balance,int limit,shared_ptr<Person> p,double fee_factor): Account(nr, balance, limit, p), fee_factor(fee_factor){
    if(fee_factor<=0) throw runtime_error("fee factor ungueltig");
}

double BusinessAccount::calc_fee(int x) const{
    return (fee_factor * x);
}

bool SBusinessAccount::calc_bonus(){
    int tmp_bonus{get_bonus()};
    set_bonus(get_bonus() + 2);
    return tmp_bonus != get_bonus();
}

ostream& SBusinessAccount::print(ostream& o) const{
    Account::print(o);
    o << " Bonus: " << Account::get_bonus();
    return o;
}

bool AccountCollection::calc_boni(){
    bool alltrue{true};
    for(auto it{v.begin()}; it != v.end(); ++it){
        auto sptr{check(*it)};
        if(!sptr) continue;
        if(!(sptr->calc_bonus())) alltrue = false;
    }
    return alltrue;
}