#include"bank.h"
using namespace std;

Bank::Bank(): customers(), accounts() { }

void Bank::create_person(string name,int nr,int balance,int limit,int mode,double fee_factor){
    for(auto it{customers.begin()}; it != customers.end(); it++){
        if(it->first == name) throw runtime_error("Person vorhanden");
    }
    for(auto it{accounts.begin()}; it != accounts.end(); it++){
        if(it->first == nr) throw runtime_error("Konto vorhanden");
    }

    auto pers_ptr = make_shared<Person>(name);
    auto acc_ptr = pers_ptr->create_account(nr, balance, limit, mode, fee_factor);

    customers.insert({name, pers_ptr});
    accounts.insert({nr, acc_ptr});
}

ostream& Bank::print_customers(ostream& o) const{
    bool first{true};
    o << "[\n";
    for(auto it{customers.begin()}; it != customers.end(); it++){
        auto pers_ptr = it->second;
        if(first){
            (*pers_ptr).print(o);
            first = false;
        }
        else{
            o << "\n";
            (*pers_ptr).print(o);
        }
    }
    o << "\n]";
    return o;
}

ostream& Bank::print_accounts(ostream& o) const{
    bool first{true};
    o << "[\n";
    for(auto it{accounts.begin()}; it != accounts.end(); it++){
        auto acc_ptr = it->second;
        if(first){
            (*acc_ptr).print(o);
            first = false;
        }
        else{
            o << "\n";
            (*acc_ptr).print(o);
        }
    }
    o << "\n]";
    return o;
}

shared_ptr<Person> Bank::get_person(string n){
    auto it = customers.find(n);
    if(it == customers.end()) throw runtime_error("Bank: Person nicht vorhanden");
    return it->second;
}

shared_ptr<Account> Bank::get_account(int n){
    auto it = accounts.find(n);
    if(it == accounts.end()) throw runtime_error("Bank: Account nicht vorhanden");
    return it->second;
}

bool Bank::remove_person(string n){
    if(customers.find(n) == customers.end()) return false;

    customers.at(n).reset();
    customers.erase(n);
//suche nach zeichnungsberechtigen personen - loeschen falls keine mehr
    for(auto it{accounts.begin()}; it != accounts.end(); ){
//wieso break? evtl continue?
        if(it->second == nullptr) continue;
        auto acc_ptr{it->second};
        if(!(acc_ptr->number_of_owners())) { it = accounts.erase(it); }
        else it++;
    }
    return true;
}



bool Bank::remove_account(int n){
    if(accounts.find(n) == accounts.end()) return false;

    accounts.at(n).reset();
    accounts.erase(n);
//suche nach acc ohne pers - loeschen falls keine mehr
    for(auto it{customers.begin()}; it != customers.end(); ){
        auto pers_ptr{it->second};
        if(pers_ptr == nullptr) continue;
        if(!(pers_ptr->number_of_accounts())) { it = customers.erase(it); }
        else it++;
    }
    return true;
}
