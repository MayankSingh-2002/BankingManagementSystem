#ifndef BANK_ACCOUNT_H
#define BANK_ACCOUNT_H

#include <iostream>
#include <string>
#include <vector>


class BankAccount {
    private:
        std::string bankName = "MSBOI";
        int bankCode;
        std::string accountHolderName;
        std::string accountNumber;
        std::string accountPassword;
        std::string adhaarNumber;
        std::string email;
        std::string phoneNumber;
        std::string accountType;
        double balance;
        std::vector<std::string> transactionHistory;


    public:
        void createAccount();
        void loginAccount();
        void mainMenu();
        void depositMoney();
        void withdrawMoney();
        void checkBalance();
        void showAccountDetails();
        void showTransactionHistory();
        void saveToFile();
        bool loadFromFile();
        void calculateInterest();

};


#endif 