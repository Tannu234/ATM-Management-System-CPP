#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

class Account {
public:
    string accountNumber;
    string name;
    int pin;
    double balance;

    Account(string accNo, string n, int p, double bal) {
        accountNumber = accNo;
        name = n;
        pin = p;
        balance = bal;
    }
};

vector<Account> accounts;

// Load accounts from file
void loadAccounts() {
    accounts.clear();

    ifstream file("accounts.txt");

    string accNo, name;
    int pin;
    double balance;

    while (file >> accNo >> name >> pin >> balance) {
        accounts.push_back(Account(accNo, name, pin, balance));
    }

    file.close();
}

// Save accounts to file
void saveAccounts() {
    ofstream file("accounts.txt");

    for (auto &acc : accounts) {
        file << acc.accountNumber << " "
             << acc.name << " "
             << acc.pin << " "
             << acc.balance << endl;
    }

    file.close();
}

// Create account
void createAccount() {
    string accNo, name;
    int pin;

    cout << "\n===== CREATE ACCOUNT =====\n";

    cout << "Enter Account Number: ";
    cin >> accNo;

    for (auto &acc : accounts) {
        if (acc.accountNumber == accNo) {
            cout << "Account already exists!\n";
            return;
        }
    }

    cout << "Enter Name: ";
    cin >> name;

    cout << "Create 4-digit PIN: ";
    cin >> pin;

    accounts.push_back(Account(accNo, name, pin, 0));

    saveAccounts();

    cout << "Account Created Successfully!\n";
}

// Login
int login() {
    string accNo;
    int pin;

    cout << "\n===== LOGIN =====\n";

    cout << "Account Number: ";
    cin >> accNo;

    cout << "PIN: ";
    cin >> pin;

    for (int i = 0; i < accounts.size(); i++) {
        if (accounts[i].accountNumber == accNo &&
            accounts[i].pin == pin) {

            cout << "\nWelcome "
                 << accounts[i].name
                 << "!\n";

            return i;
        }
    }

    cout << "Invalid Credentials!\n";
    return -1;
}

// ATM Menu
void atmMenu(int index) {

    int choice;

    do {
        cout << "\n===== ATM MENU =====\n";
        cout << "1. Check Balance\n";
        cout << "2. Deposit Money\n";
        cout << "3. Withdraw Money\n";
        cout << "4. Change PIN\n";
        cout << "5. Logout\n";

        cout << "\nEnter Choice: ";
        cin >> choice;

        switch (choice) {

        case 1:
            cout << "\nCurrent Balance: Rs. "
                 << accounts[index].balance
                 << endl;
            break;

        case 2: {
            double amount;

            cout << "Enter Amount: ";
            cin >> amount;

            accounts[index].balance += amount;

            saveAccounts();

            cout << "Deposit Successful!\n";
            break;
        }

        case 3: {
            double amount;

            cout << "Enter Amount: ";
            cin >> amount;

            if (amount > accounts[index].balance) {
                cout << "Insufficient Balance!\n";
            }
            else {
                accounts[index].balance -= amount;

                saveAccounts();

                cout << "Withdrawal Successful!\n";
            }
            break;
        }

        case 4: {
            int newPin;

            cout << "Enter New PIN: ";
            cin >> newPin;

            accounts[index].pin = newPin;

            saveAccounts();

            cout << "PIN Changed Successfully!\n";
            break;
        }

        case 5:
            cout << "Logged Out Successfully!\n";
            break;

        default:
            cout << "Invalid Choice!\n";
        }

    } while (choice != 5);
}

int main() {

    loadAccounts();

    int choice;

    do {

        cout << "\n===== ATM MANAGEMENT SYSTEM =====\n";
        cout << "1. Create Account\n";
        cout << "2. Login\n";
        cout << "3. Exit\n";

        cout << "\nEnter Choice: ";
        cin >> choice;

        switch (choice) {

        case 1:
            createAccount();
            break;

        case 2: {
            int userIndex = login();

            if (userIndex != -1) {
                atmMenu(userIndex);
            }
            break;
        }

        case 3:
            cout << "\nThank You!\n";
            break;

        default:
            cout << "\nInvalid Choice!\n";
        }

    } while (choice != 3);

    return 0;
}