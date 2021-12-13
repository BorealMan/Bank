#pragma once
#include <iostream>
using namespace std;

class BankAccount
{
private:
    int id;
    double balance;
    double interestRate;

public:
    BankAccount(int _id, double _deposit, double _IR)
    {
        id = _id;
        interestRate = _IR;
        deposit(_deposit);
    }

    int getId()
    {
        return id;
    }

    double getBalance()
    {
        return balance;
    }

    double getInterestRate()
    {
        return interestRate;
    }

    void setBalance(double d)
    {
        if (d >= 0)
        {
            balance = d;
        }
    }

    void setInterestRate(double ir)
    {
        if (ir > 0)
        {
            interestRate = ir;
        }
    }

    bool deposit(double d)
    {
        if (d > 0)
        {
            balance += d;
            cout << "Depositing: $" << d << endl;
            print();
            return true;
        }
        else
        {
            cout << "Deposit Must Be Greater Than Zero\n\n";
            return false;
        }
    }

    bool widthdraw(double d)
    {
        if (d > 0 && balance >= d)
        {
            cout << "Widthdrawing: $" << d << endl;
            balance -= d;
            print();
            return true;
        }
        else
        {
            cout << "Insufficient Funds\n\n";
            return false;
        }
    }

    void print()
    {
        cout << "Account Details: \n"
             << "Account Id: " << id << "\nBalance: $" << balance << "\n\n";
    }
};