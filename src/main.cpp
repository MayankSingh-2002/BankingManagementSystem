#include "../include/BankAccount.h"
#include <iostream>

int main() {
    BankAccount account;
    int choice;

    std::cout << "==== Welcome to MSBOI Bank ====\n" << std::endl;

    do {
        std::cout << "1. Create New Account" << std::endl;
        std::cout << "2. Login to Existing Account" << std::endl;
        std::cout << "3. Exit" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        std::cin.ignore();


        switch (choice) {
            case 1:
                account.createAccount();
                break;
            case 2:
                account.loginAccount();
                break;
            case 3:
                std::cout << "Thank you for using MOSIBank. Goodbye!" << std::endl;
                break;
            default:
                std::cerr << "Invalid choice. Please try again." << std::endl;
        }
    } while (choice != 3);

    return 0;
}