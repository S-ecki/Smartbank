#include"person.h"
#include"account.h"
using namespace std;

template<typename T>
shared_ptr<T> check(weak_ptr<T> weak){
    if (auto check = weak.lock()) {
        return check;
    } else {
        return nullptr;
    }
}

Person::Person(string name): name(name){
    if(name.empty()) throw runtime_error("name empty");
}

shared_ptr<Account> Person::create_account(int nr, int balance, int limit, int mode, double fee_factor){
    if(mode != 0 && mode != 1 && mode != 2 && mode != 3) throw runtime_error("mode ungueltig");
    auto this_ptr{this->pers_get_shared()};

    if(mode == 0){
        auto acc_ptr{make_shared<GiroAccount>(nr, balance, limit, this_ptr, fee_factor)};
        accounts.insert({nr, acc_ptr});
        acc_ptr->add_authorized_person(this_ptr);
        return acc_ptr;
    }

    else if(mode == 1){
        auto acc_ptr{make_shared<BusinessAccount>(nr, balance, limit, this_ptr, fee_factor)};
        accounts.insert({nr, acc_ptr});
        acc_ptr->add_authorized_person(this_ptr);
        return acc_ptr;
    }

    else if(mode == 2){
        auto acc_ptr{make_shared<SGiroAccount>(nr, balance, limit, this_ptr, fee_factor)};
        accounts.insert({nr, acc_ptr});
        acc_ptr->add_authorized_person(this_ptr);
        return acc_ptr;
    }

    else if(mode == 3){
        auto acc_ptr{make_shared<SBusinessAccount>(nr, balance, limit, this_ptr, fee_factor)};
        accounts.insert({nr, acc_ptr});
        acc_ptr->add_authorized_person(this_ptr);
        return acc_ptr;
    }

    return nullptr;
}

string Person::get_name() const{
    return name;
}

size_t Person::number_of_accounts() const{
    size_t sum{0};
    for(auto it{accounts.begin()}; it != accounts.end(); it++){
        if(!(it->second.expired())) sum++;
    }
    return sum;
}

vector<int> Person::get_account_nrs() const{
    vector<int> list;
    for(auto it{accounts.begin()}; it != accounts.end(); it++){
        if(check(it->second) != nullptr) list.push_back(it->first);
    }
    return list;
}

bool Person::share_account(shared_ptr<Person> other,int nr){
    if(accounts.find(nr) == accounts.end()) return false;
    vector<int> other_nrs{other->get_account_nrs()};
    for(int elem: other_nrs){
        if(elem == nr) return false;
    }
//achtung mit [] - fuegt wert ein falls nicht vorhanden - sollte aber gehen, da schon mit find() gecheckt wurde
    auto nr_ptr = check(accounts[nr]);
    nr_ptr->add_authorized_person(other);
    other->insert_acc(nr_ptr);

    return true;   
}

ostream& Person::print(ostream& o) const{
    o << "Name: " << name << ", {";
    bool firstt{true};
    for(auto it{accounts.begin()}; it != accounts.end(); it++){
        if(firstt){
            auto acc_ptr = check(it->second);
            if(acc_ptr == nullptr) continue;
            o << "[Nr.: " << it->first << ", [";
            o << acc_ptr->get_balance() << "/" << acc_ptr->get_limit() << "], Fees: " << acc_ptr->get_fee() << ", Owners: {";
            bool first{true};
            for(string p: acc_ptr->get_authorized_persons()){
                if(first){
                    o << p;
                    first = false;
                }
                else{
                    o << ", " << p;
                }
            }
            o << "}]";
            firstt = false;
        } 
        else{
            auto acc_ptr = check(it->second);
            if(acc_ptr == nullptr) continue;
            o << ", ";
            o << "[Nr.: " << it->first << ", [";
            o << acc_ptr->get_balance() << "/" << acc_ptr->get_limit() << "], Fees: " << acc_ptr->get_fee() << ", Owners: {";
            bool first{true};
            for(string p: acc_ptr->get_authorized_persons()){
                if(first){
                    o << p;
                    first = false;
                }
                else{
                    o << ", " << p;
                }
            }
            o << "}]";
            firstt = false;
        }
    }
    o << "}";
    return o;
}

void Person::insert_acc(shared_ptr<Account> a){
    weak_ptr<Account> wp = a;
    accounts.insert({a->get_nr(), wp});
}