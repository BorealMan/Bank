#pragma once
#include <iostream>
#include <math.h>
#include <vector>
#include "bankaccount.cpp"
#include "loan.cpp"
using namespace std;

enum MANAGE_ACCOUNT
{
    Widthdraw,
    Deposit,
    CheckBalance
};

enum MANAGE_LOAN
{
    MakePayment,
    ViewLoan
};

class Bank
{

private:
    // Banking Variables
    int id;
    double cash;
    double deposits;
    double reserves;
    // Account Mangement
    vector<BankAccount *> accounts;
    int accountIdCount;
    double IRates[3] = {.001, .0025, .0035};
    // Loan Management
    vector<Loan *> loans;
    int loanIdCount;
    double reserveRatio = 10;
    double loanableReserves;
    double totalCashOnLoan;
    double totalInterestPayable;
    // Analysis
    double totalInterestPaid;
    double totalInterestCollected;
    // Real Time Values
    int numberOfAccounts;
    int numberOfLoans;

public:
    Bank(int _id, double _cash)
    {
        id = _id;
        cash = _cash;
        deposits = 0;
        calculateReserves();
        accountIdCount = 0;
        loanIdCount = 0;
        numberOfAccounts = 0;
        calculateLonableReserves();
        numberOfLoans = 0;
        totalCashOnLoan = 0;
        totalInterestPaid = 0;
        totalInterestCollected = 0;
        double totalInterestPayable = 0;
    }

    BankAccount *findAccount(int _id)
    {
        for (BankAccount *account : accounts)
        {
            if (account->getId() == _id)
            {
                return account;
            }
        }
        cout << "Unable To Find Account Id: " << _id << "\n\n";
        return NULL;
    }

    void openAccount(double _deposit)
    {
        if (_deposit >= 0)
        {
            BankAccount *newAccount = new BankAccount(accountIdCount, _deposit, IRates[0]);
            accounts.push_back(newAccount);
            accountIdCount++;
            numberOfAccounts++;
            deposits += _deposit;
            reserves = deposits + cash;
            calculateLonableReserves();
        }
        else
        {
            cout << "Cannot Open A New Account With Negative Funds\n\n";
        }
    }

    void closeAccount(int _id)
    {
        int i = 0;
        for (BankAccount *account : accounts)
        {
            if (account->getId() == _id)
            {
                deposits -= account->getBalance();
                reserves = deposits + cash;
                calculateLonableReserves();
                delete account;
                accounts.erase(accounts.begin() + i);
                numberOfAccounts -= 1;
            }
            i++;
        }
    }

    bool manageAccount(int _id, MANAGE_ACCOUNT _action, double _amount = 0)
    {

        BankAccount *account = findAccount(_id);
        if (account == NULL)
        {
            return 0;
        }
        else if (_action == Deposit)
        {
            bool proccessed = account->deposit(_amount);
            if (proccessed)
            {
                deposits += _amount;
                calculateLonableReserves();
            }
            return 1;
        }
        else if (_action == Widthdraw)
        {
            bool proccessed = account->widthdraw(_amount);
            if (proccessed)
            {
                deposits -= _amount;
                calculateLonableReserves();
            }
            return 1;
        }
        else if (_action == CheckBalance)
        {
            account->print();
            return 1;
        }
        else
        {
            cout << "An unknown error occured when managing account: " << _id << "\n\n";
            return -1;
        }
    }

    void payInterest()
    {
        int periodDivisor = 12;
        for (BankAccount *account : accounts)
        {
            double i = account->getBalance() * (account->getInterestRate() / periodDivisor);
            cash -= i;
            deposits += i;
            totalInterestPaid += i;
            account->setBalance(account->getBalance() + i);
            calculateLonableReserves();
        }
    }

    void calculateReserves()
    {
        reserves = deposits + cash;
    }

    void calculateLonableReserves()
    {
        calculateReserves();
        loanableReserves = reserves * reserveRatio;
    }

    bool transferPayment(int _bankAccount1, int _bankAccount2, double _amount)
    {

        return 0;
    }

    Loan *findLoan(int _id)
    {
        for (Loan *loan : loans)
        {
            if (loan->getId() == _id)
            {
                return loan;
            }
        }
        cout << "Unable To Find Loan Id: " << _id << "\n\n";
        return NULL;
    }

    bool canMakeLoan(double _amount)
    {
        return loanableReserves >= totalCashOnLoan + _amount && _amount >= 100;
    }

    void createLoan(int _barrower_id, double _amount, int _years, double _IR)
    {
        if (canMakeLoan(_amount))
        {
            Loan *l = new Loan(loanIdCount, _amount, id, _barrower_id, _years, _IR);
            totalCashOnLoan += _amount;
            totalInterestPayable += l->getTotalInterest();
            loanIdCount += 1;
            numberOfLoans += 1;
            loans.push_back(l);
        }
        else
        {
            cout << "Bank Cannot Meet Loan Request :: Amount Requested: $" << _amount << "\n\n";
        }
    }

    void removeLoan(int _id)
    {
        int i = 0;
        for (Loan *loan : loans)
        {
            if (loan->getId() == _id)
            {
                numberOfLoans -= 1;
                loans.erase(loans.begin() + i);
            }
            i++;
        }
    }

    void payLoan(Loan *l)
    {
        bool last = l->pay();
        cash += l->getInterestPerPayment();
        totalInterestCollected += l->getInterestPerPayment();
        totalInterestPayable -= l->getInterestPerPayment();
        totalCashOnLoan -= l->getPayment() - l->getInterestPerPayment();
        if (last)
        {
            removeLoan(l->getId());
            delete l;
        }
        calculateLonableReserves();
    }

    bool manageLoan(int _id, MANAGE_LOAN _action)
    {
        Loan *l = findLoan(_id);
        if (l == NULL)
        {
            return 0;
        }
        else if (_action == MakePayment)
        {
            payLoan(l);
        }
        else if (_action == ViewLoan)
        {
            l->print();
        }
        else
        {
            cout << "An Unknown Error Occured Managing Loan Id: " << id << "\n\n";
        }
    }

    void collectInterest()
    {
        for (Loan *loan : loans)
        {
            payLoan(loan);
        }
    }

    void runPeriod()
    {
        payInterest();
        collectInterest();
    }

    void print()
    {
        cout << "Bank Details: " << endl;
        cout << "Bank Id: " << id << endl;
        cout << "Number Of Accounts: " << numberOfAccounts << endl;
        cout << "Number Of Loans: " << numberOfLoans << endl;
        cout << "Cash: $" << cash << endl;
        cout << "Deposits: $" << deposits << endl;
        cout << "Reserves: $" << reserves << endl;
        cout << "Loanable Reserves: $" << loanableReserves << endl;
        cout << "Total Cash On Loan: $" << totalCashOnLoan << endl;
        cout << "Total Book Value Of Loans: $" << totalInterestPayable << endl;
        cout << "Total Interest Paid: $" << totalInterestPaid << endl;
        cout << "Total Interest Collected: $" << totalInterestCollected << "\n\n";
    }

    int getNumberOfLoans()
    {
        return numberOfLoans;
    }
};