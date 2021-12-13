#include <iostream>
#include "bank.cpp"
using namespace std;

void funcationalityTest(Bank *b)
{
    b->print();
    b->openAccount(5000);
    b->openAccount(35);
    b->print();
    b->manageAccount(0, Widthdraw, 200);
    b->manageAccount(1, Deposit, 1000);
    b->payInterest();
    b->print();
    b->manageAccount(0, CheckBalance);
    b->manageAccount(1, CheckBalance);
    b->closeAccount(0);
    b->print();
    b->openAccount(50000);
    b->manageAccount(2, Deposit, 100000);
    b->payInterest();
    b->print();
    b->manageAccount(0, CheckBalance);
    b->manageAccount(1, CheckBalance);
    b->manageAccount(2, CheckBalance);
    b->print();
    b->openAccount(100000);
    b->payInterest();
    b->print();
    b->manageAccount(1, Widthdraw, 100000);
    b->createLoan(1, 10000, 3, .049);
    b->createLoan(2, 30000, 6, .059);
    b->createLoan(5, 1000000, 4, .03);
    b->collectInterest();
    b->print();
    b->createLoan(6, 2000000, 9, .0625);
    b->runPeriod();
    b->print();
    b->runPeriod();
    while (b->getNumberOfLoans() != 0)
    {
        b->runPeriod();
        // b->print();
    }
    b->print();
}

int main()
{
    Bank *b = new Bank(1, 50000);

    funcationalityTest(b);

    return 0;
}