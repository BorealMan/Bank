#pragma once
#include <iostream>
#include <math.h>
using namespace std;

class Loan
{
private:
    int id;
    // Amount Details
    double loanAmount;
    double totalAmount;
    double remainingAmount;
    double totalInterest;
    // Other Details
    int lender_id;
    int barrower_id;
    double IR;
    int years;
    int totalPayments;
    int paymentsLeft;
    // Calculated Values
    double payment;
    double interestPerPayment;

public:
    Loan(int _id, double _loanAmount, int _lender_id, int _barrower_id, int _years, double _IR)
    {
        id = _id;
        loanAmount = _loanAmount;
        lender_id = _lender_id;
        barrower_id = _barrower_id;
        years = _years;
        IR = _IR;
        calculateTotalPayments();
        calculateTotalAmount();
        calculatePayment();
        calculateTotalInterest();
        calculateInterestPerPayment();
        paymentsLeft = totalPayments;
        remainingAmount = totalAmount;
    }

    int getId()
    {
        return id;
    }

    double getLoanAmount()
    {
        return loanAmount;
    }

    double getTotalAmount()
    {
        return totalAmount;
    }

    double getRemainingAmount()
    {
        return remainingAmount;
    }

    int getLenderId()
    {
        return lender_id;
    }

    int getBarrowerId()
    {
        return barrower_id;
    }

    int getYears()
    {
        return years;
    }

    double getIR()
    {
        return IR;
    }

    int getTotalPayments()
    {
        return totalPayments;
    }

    int getPaymentsLeft()
    {
        return paymentsLeft;
    }

    double getPayment()
    {
        return payment;
    }

    double getTotalInterest()
    {
        return totalInterest;
    }

    double getInterestPerPayment()
    {
        return interestPerPayment;
    }

    void calculateTotalPayments()
    {
        totalPayments = years * 12;
    }

    void calculateTotalAmount()
    {
        double e = 2.7182818;
        totalAmount = loanAmount * pow(e, IR * years);
    }

    void calculatePayment()
    {
        payment = totalAmount / totalPayments;
    }

    void calculateTotalInterest()
    {
        totalInterest = totalAmount - loanAmount;
    }

    void calculateInterestPerPayment()
    {
        interestPerPayment = totalInterest / totalPayments;
    }

    void print()
    {
        cout << "Loan Details:" << endl;
        cout << "Loan Id: " << id << endl;
        cout << "Lender Id: " << lender_id << endl;
        cout << "Barrower Id: " << barrower_id << endl;
        cout << "Loan Amount: $" << loanAmount << endl;
        cout << "Interest Rate: " << IR << "%" << endl;
        cout << "Total Repayment: $" << totalAmount << endl;
        cout << "Total Payments: " << totalPayments << endl;
        cout << "Amount Remaining: $" << remainingAmount << endl;
        cout << "Payments Left: " << paymentsLeft << endl;
        cout << "Total Interest: $" << totalInterest << endl;
        cout << "Interest Per Payment $" << interestPerPayment << endl;
        cout << "Monthly Payment: $" << payment << "\n\n";
    }

    bool isLastPayment()
    {
        return paymentsLeft <= 0;
    }

    bool pay()
    {
        if (!isLastPayment())
        {
            remainingAmount -= payment;
            paymentsLeft -= 1;
            if (isLastPayment())
            {
                remainingAmount = 0;
            }
            // print();
        }
        return isLastPayment();
    }

    void simulateLife()
    {
        print();
        while (!isLastPayment())
        {
            pay();
        }
    }
};

// Tests?

void printBond()
{
    Loan *l = new Loan(1, 250000, 1, 1, 15, .0285);
    l->print();
    delete l;
}

void simulatePaymentCycle()
{
    Loan *l = new Loan(1, 250000, 1, 1, 15, .0285);
    l->simulateLife();
    delete l;
}

// int main()
// {
//     // printBond();
//     simulatePaymentCycle();
//     return 1;
// }