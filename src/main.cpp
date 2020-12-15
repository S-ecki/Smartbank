#include"account.h"
#include"person.h"
#include"bank.h"
#include<iostream>
using namespace std;


int main(){
cout << "Aufgabe 1:\n\n";
    Bank b{};
    b.create_person("Niklas B", 1, 0, 2000, 0, 0.05);
    b.create_person("Matteo R", 2, 100, 0, 1, 0.03);
    b.print_customers(cout);
    cout << "\n";
    b.print_accounts(cout);
    cout << "\n\n";

    (*b.get_account(1)).transfer(b.get_account(2), 500);
    b.print_customers(cout);
    cout << "\n";
    b.print_accounts(cout);
    cout << "\n\n";

    (*b.get_person("Matteo R")).share_account(b.get_person("Niklas B"), 2);
    b.print_customers(cout);
    cout << "\n";
    b.print_accounts(cout);
    cout << "\n\n";

    (*b.get_account(2)).transfer(b.get_account(1), 601);
    b.print_customers(cout);
    cout << "\n";
    b.print_accounts(cout);
    cout << "\n\n";


    b.remove_account(2);
    b.print_customers(cout);
    cout << "\n";
    b.print_accounts(cout);
    cout << "\n\n";


    b.remove_person("Niklas B");
    b.print_customers(cout);
    cout << "\n";
    b.print_accounts(cout);
    cout << "\n\n";

cout << "Aufgabe 2:\n\n";
    Bank b2{};
    b2.create_person("Niklas B", 1, 0, 2000, 3, 0.05);
    b2.create_person("temp", 2, 0, 2000, 0, 0.05);
    (*(b2.get_person("temp"))).share_account(b2.get_person("Niklas B"), 2);
    b2.remove_person("temp");
    b2.create_person("Matteo R", 3, 0, 1000, 2, 0.03);
    cout << boolalpha  << "\nBonus veraendert Nr1: " << (b2.get_account(1)->calc_bonus()) << "\nBonus veraendert Nr2: " << (b2.get_account(2)->calc_bonus()) << "\nBonus veraendert Nr3: " << (b2.get_account(3)->calc_bonus()) << endl;
    b2.print_accounts(cout);
    cout << endl;
    (*(b2.get_person("Matteo R"))).share_account(b2.get_person("Niklas B"), 3);
    cout << "\nBonus veraendert Nr1: " << (b2.get_account(1)->calc_bonus()) << "\nBonus veraendert Nr2: " << (b2.get_account(2)->calc_bonus()) << "\nBonus veraendert Nr3: " << (b2.get_account(3)->calc_bonus()) << endl;
    b2.print_accounts(cout);
    cout << endl << endl;

cout << "Aufgabe 3:\n\n";
    Bank b3{};
    b3.create_person("Niklas B", 1, 0, 2000, 1, 0.05);

    b3.create_person("temp", 2, 0, 2000, 3, 0.05);
    (*(b3.get_person("temp"))).share_account(b3.get_person("Niklas B"), 2);
    b3.remove_person("temp");

    b3.create_person("temp", 3, 0, 2000, 0, 0.05);
    (*(b3.get_person("temp"))).share_account(b3.get_person("Niklas B"), 3);
    b3.remove_person("temp");

    b3.create_person("temp", 4, 0, 2000, 2, 0.05);
    (*(b3.get_person("temp"))).share_account(b3.get_person("Niklas B"), 4);
    b3.remove_person("temp");


    vector<weak_ptr<Account>> v{b3.get_account(1),b3.get_account(2),b3.get_account(3),b3.get_account(4)};
    AccountCollection col(v);
    cout << col.calc_boni() << endl;
    b3.print_accounts(cout);



    Bank b4{};
    b4.create_person("Matteo R", 1, 0, 2000, 1, 0.05);

    b4.create_person("temp", 2, 0, 2000, 3, 0.05);
    (*(b4.get_person("temp"))).share_account(b4.get_person("Matteo R"), 2);
    b4.remove_person("temp");

    b4.create_person("temp", 3, 0, 2000, 0, 0.05);
    (*(b4.get_person("temp"))).share_account(b4.get_person("Matteo R"), 3);
    b4.remove_person("temp");

    b4.create_person("temp", 4, 0, 2000, 2, 0.05);
    (*(b4.get_person("temp"))).share_account(b4.get_person("Matteo R"), 4);
    b4.remove_person("temp");

    vector<weak_ptr<Account>> vv{b4.get_account(1),b4.get_account(2),b4.get_account(3),b4.get_account(4)};
    AccountCollection coll(vv);
    cout << coll.calc_boni() << endl;
    b4.print_accounts(cout);
    cout << endl;
}