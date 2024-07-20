#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

class Customer {
public:
    int id;
    std::string name;
    std::string address;

    Customer(int id, std::string name, std::string address)
        : id(id), name(name), address(address) {}
};

class Account {
public:
    int accountNumber;
    int customerId;
    double balance;

    Account(int accountNumber, int customerId, double initialBalance)
        : accountNumber(accountNumber), customerId(customerId), balance(initialBalance) {}

    void deposit(double amount) {
        balance += amount;
    }

    bool withdraw(double amount) {
        if (amount <= balance) {
            balance -= amount;
            return true;
        }
        return false;
    }

    double checkBalance() const {
        return balance;
    }
};

class Bank {
private:
    std::vector<Customer> customers;
    std::vector<Account> accounts;

public:
    void addCustomer(int id, std::string name, std::string address) {
        customers.push_back(Customer(id, name, address));
        std::cout << "Customer added successfully.\n";
    }

    void createAccount(int accountNumber, int customerId, double initialBalance) {
        accounts.push_back(Account(accountNumber, customerId, initialBalance));
        std::cout << "Account created successfully.\n";
    }

    void deposit(int accountNumber, double amount) {
        for (auto& account : accounts) {
            if (account.accountNumber == accountNumber) {
                account.deposit(amount);
                std::cout << "Deposit successful. New balance: " << account.checkBalance() << "\n";
                return;
            }
        }
        std::cout << "Account not found.\n";
    }

    void withdraw(int accountNumber, double amount) {
        for (auto& account : accounts) {
            if (account.accountNumber == accountNumber) {
                if (account.withdraw(amount)) {
                    std::cout << "Withdrawal successful. New balance: " << account.checkBalance() << "\n";
                } else {
                    std::cout << "Insufficient funds.\n";
                }
                return;
            }
        }
        std::cout << "Account not found.\n";
    }

    void checkBalance(int accountNumber) {
        for (const auto& account : accounts) {
            if (account.accountNumber == accountNumber) {
                std::cout << "Current balance: " << account.checkBalance() << "\n";
                return;
            }
        }
        std::cout << "Account not found.\n";
    }
};

int main() {
    Bank bank;
    int choice, id, accountNumber;
    std::string name, address;
    double amount, initialBalance;

    while (true) {
        std::cout << "\n1. Add Customer\n2. Create Account\n3. Deposit\n4. Withdraw\n5. Check Balance\n6. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                std::cout << "Enter Customer ID: ";
                std::cin >> id;
                std::cout << "Enter Name: ";
                std::cin.ignore();
                std::getline(std::cin, name);
                std::cout << "Enter Address: ";
                std::getline(std::cin, address);
                bank.addCustomer(id, name, address);
                break;

            case 2:
                std::cout << "Enter Account Number: ";
                std::cin >> accountNumber;
                std::cout << "Enter Customer ID: ";
                std::cin >> id;
                std::cout << "Enter Initial Balance: ";
                std::cin >> initialBalance;
                bank.createAccount(accountNumber, id, initialBalance);
                break;

            case 3:
                std::cout << "Enter Account Number: ";
                std::cin >> accountNumber;
                std::cout << "Enter Amount to Deposit: ";
                std::cin >> amount;
                bank.deposit(accountNumber, amount);
                break;

            case 4:
                std::cout << "Enter Account Number: ";
                std::cin >> accountNumber;
                std::cout << "Enter Amount to Withdraw: ";
                std::cin >> amount;
                bank.withdraw(accountNumber, amount);
                break;

            case 5:
                std::cout << "Enter Account Number: ";
                std::cin >> accountNumber;
                bank.checkBalance(accountNumber);
                break;

            case 6:
                std::cout << "Exiting...\n";
                return 0;

            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}
