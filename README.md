# Smartbank
 A bank Application written in C++ using Smart Pointers, which was created for my class [Programmierung 2](https://ufind.univie.ac.at/de/course.html?lv=051020&semester=2020S) at the University of Vienna.

## Structure
`Account` is a pure virtual class, `(S)BusinessAccount` and `(S)GiroAccount` inherit its fields and methods.
Accounts have autorised persons (weak_ptr), can transfer money (which leads to fees) and use lots of other functionality.

`Person` has a name and one or more accounts (weak_ptr), which the class administers.

`Bank` oversees all of the action. It holds shared_ptr to all accounts and persons and is used to create/delete them.

## What I´ve learned
* Working with Smart Pointers
* Inheritance in C++
* Comment your code!
