#include "BankAccount.h"
#include <iostream>
#include <fstream>
#include <iomanip>


using namespace std;


void BankAccount::createAccount() {
    cout << "\n==== Create New Account ====\n" << endl;
    cin.ignore();
    cout << "Enter Full Name        : ";
    getline(cin, accountHolderName);
    cout << "Enter Adhaar Number    : ";
    getline(cin, adhaarNumber);
    cout << "Enter Email            : ";
    getline(cin, email);
    cout << "Enter Phone Number     : ";
    getline(cin, phoneNumber);


    int typeChoice;
    do
    {
        cout << "Choose Account Type:\n1. Savings\n2. Current\nEnter choice: ";
        cin >> typeChoice;
        cin.ignore();
        if(typeChoice == 1) {
            accountType = "Savings";
        } else if(typeChoice == 2) {
            accountType = "Current";
        } else {
            cout << "Invalid choice. Please try again." << endl;
        }
    } while (accountType != "Savings" && accountType != "Current");

    cout << "Set Account Password : ";
    getline(cin, accountPassword);


    ifstream file("data/bankcode.txt");
    if(!file.is_open()) {
        bankCode = 1001;
        ofstream initFile("data/bankcode.txt");
        initFile << bankCode;
        initFile.close();
    } else {
        file >> bankCode;
        file.close();   
    }


    ofstream out("data/bankcode.txt");
    out << bankCode + 1;
    out.close();


    accountNumber = bankName + to_string(bankCode);
    balance = 500.0;
    transactionHistory.push_back("Account created with initial balance Rs. 500.0");


    cout << "\nAccount created successfully!" << endl;
    cout << "Account Number: " << accountNumber << endl;
    cout << "Use your password to login.\n" << endl;
    saveToFile();
  
}


void BankAccount::saveToFile() {
    ofstream file("data/" + accountNumber + ".txt");
    if (file.is_open()) {
        file << accountHolderName << endl;
        file << accountNumber << endl;
        file << accountPassword << endl;
        file << adhaarNumber << endl;
        file << email << endl;
        file << phoneNumber << endl;
        file << accountType << endl;
        file << balance << endl;
        for (auto&tx : transactionHistory) {
            file << tx << endl;   
        }
        file.close();
    } else {
        cerr << "Error saving account file." << endl;
    }
    
}


bool BankAccount::loadFromFile() {
    ifstream file("data/" + accountNumber + ".txt");
    if (file.is_open()) {
        getline(file, accountHolderName);
        getline(file, accountNumber);
        getline(file, accountPassword);
        getline(file, adhaarNumber);
        getline(file, email);
        getline(file, phoneNumber);
        getline(file, accountType);
        file >> balance;
        file.ignore();
        string tx;
        while (getline(file, tx)) {
            transactionHistory.push_back(tx);
        }
        file.close();
        return true;
    } else {
        cerr << "Account file not found." << endl;
        return false;
    }

}


void BankAccount::loginAccount() {
    cin.ignore();
    cout << "\n==== Login to Account ====\n" << endl;
    string accNum, Pass;
    cout << "Enter Account Number: ";
    getline(cin, accNum);
    accountNumber = accNum;
    if (!loadFromFile()) {
        cout << "Account not found. Please create an account first." << endl;
        return;
    }

    cout << "Enter Password: ";
    getline(cin, Pass);
    if (Pass != accountPassword) {
        cerr << "Login failed. Incorrect password." << endl;
        return;
    }

    cout << "\nLogin successful!" << endl;
    mainMenu();

}

void BankAccount::mainMenu() {
    int choice;
    do {
        cout << "\n==== Welcome to " << bankName << " ====\n" << endl;
        cout << "\nLogged in as [" << accountType << " Account]" << endl;
        cout << "\n==== Account Menu ====" << endl;
        cout << "1. Deposit Money" << endl;
        cout << "2. Withdraw Money" << endl;
        cout << "3. Check Balance" << endl;
        cout << "4. Show Account Details" << endl;
        cout << "5. Show Transaction History" << endl;
        cout << "6. Calculate Monthly Interest (Savings Only)" << endl;
        cout << "7. Logout" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();
        switch(choice) {
            case 1:
                depositMoney();
                break;
            case 2:
                withdrawMoney();
                break;
            case 3:
                checkBalance();
                break;
            case 4:
                showAccountDetails();
                break;
            case 5:
                showTransactionHistory();
                break;
            case 6:
                if (accountType == "Savings") {
                    calculateInterest();
                } else {
                    cout << "Interest calculation is only available for Savings accounts." << endl;
                }
                break;
            case 7:
                saveToFile();
                cout << "Logging out..." << endl;
                return;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 7);

}


void BankAccount::depositMoney() {
    double amount;
    cout << "Enter amount to deposit: Rs. ";
    cin >> amount;
    if (amount >0) {
        balance += amount;
        transactionHistory.push_back("Deposited Rs. " + to_string(amount));
        cout << "Deposit successful! New balance: Rs. " << fixed << setprecision(2) << balance << endl;
    } else {
        cerr << "Invalid amount. Deposit failed." << endl;
    }
}


void BankAccount::withdrawMoney() {
    double amount;
    cout << "Enter amount to withdraw: Rs. ";
    cin >> amount;

    if (amount <=0) {
        cout << "Invalid amount. Withdrawal failed." << endl;
        return; 
    }

    if (accountType == "Savings" && (amount > 25000|| balance - amount < 500)) {
        cout << "Withdrawal limit exceeded or insufficient balance. Minimum balance of Rs. 500 must be maintained." << endl;
        return;
    } else if (accountType == "Current" && (balance-amount < 1000)) {
        cout << "Minimum balance of Rs. 1000 required.\n" << endl;
        return;
    }

    balance -= amount;
    transactionHistory.push_back("Withdrew Rs. " + to_string(amount));
    cout << "Withdrawal successful! New balance: Rs. " << fixed << setprecision(2) << balance << endl;

}


void BankAccount::checkBalance() {
    cout << "Current Balance: Rs. " << fixed << setprecision(2) << balance << endl;
}


void BankAccount::showAccountDetails() {
    cout << "\n==== Account Information ====\n" << endl;
    cout << "Name                : " << accountHolderName << endl;
    cout << "Account Number      : " << accountNumber << endl;
    cout << "Adhaar Number       : " << adhaarNumber << endl;
    cout << "Email               : " << email << endl;
    cout << "Phone Number        : " << phoneNumber << endl;
    cout << "Account Type        : " << accountType << endl;
    cout << "Current Balance     : Rs. " << fixed << setprecision(2) << balance << endl;

}


void BankAccount::showTransactionHistory() {
    cout << "\n==== Transaction History ====\n" << endl;
    if (transactionHistory.empty()) {
        cout << "No transactions found." << endl;
        return;
    } else  {
        for (const auto &tx : transactionHistory) {
        cout << tx << endl;
        }
    }

}


void BankAccount::calculateInterest() {
    double interestRate = 0.04; // 4% annual interest rate
    double interest = (balance * interestRate) / 12; // Monthly interest
    balance += interest;
    transactionHistory.push_back("Interest credited: Rs. " + to_string(interest));
    cout << fixed << setprecision(2);
    cout << "Monthly interest credited: Rs. " << interest << endl;
    
}