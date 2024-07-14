#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

class Account {
protected:
    string accountNumber;
    string accountHolderName;
    double balance;

public:
    Account(string accNumber, string accHolderName, double bal)
        : accountNumber(accNumber), accountHolderName(accHolderName), balance(bal) {}

    virtual void deposit(double amount) {
        balance += amount;
        cout << "Deposited: $" << amount << " | New Balance: $" << balance << endl;
    }

    virtual void withdraw(double amount) {
        if (balance >= amount) {
            balance -= amount;
            cout << "Withdrew: $" << amount << " | New Balance: $" << balance << endl;
        } else {
            cout << "Insufficient funds!" << endl;
        }
    }

    void checkBalance() {
        cout << "Account Balance: $" << balance << endl;
    }

    string getAccountNumber() {
        return accountNumber;
    }
};

class IndividualAccount : public Account {
public:
    IndividualAccount(string accNumber, string accHolderName, double bal)
        : Account(accNumber, accHolderName, bal) {}
};

class JointAccount : public Account {
private:
    vector<string> nominees;

public:
    JointAccount(string accNumber, string accHolderName, double bal)
        : Account(accNumber, accHolderName, bal) {}

    void addNominee(string nominee) {
        if (nominees.size() < 3) {
            nominees.push_back(nominee);
            cout << "Added Nominee: " << nominee << endl;
        } else {
            cout << "Nominee limit reached!" << endl;
        }
    }

    void listNominees() {
        cout << "Nominees: ";
        for (const string& nominee : nominees) {
            cout << nominee << " ";
        }
        cout << endl;
    }
};

class BankingSystem {
private:
    map<string, Account*> accounts;
    int individualAccountCount = 0;
    int jointAccountCount = 0;

public:
    void createIndividualAccount(string accNumber, string accHolderName) {
        if (accounts.find(accNumber) != accounts.end()) {
            cout << "Account number already exists!" << endl;
            return;
        }

        if (individualAccountCount < 3) {
            accounts[accNumber] = new IndividualAccount(accNumber, accHolderName, 0.0);
            individualAccountCount++;
            cout << "Individual account created successfully!" << endl;
        } else {
            cout << "Maximum individual account limit reached!" << endl;
        }
    }

    void createJointAccount(string accNumber, string accHolderName) {
        if (accounts.find(accNumber) != accounts.end()) {
            cout << "Account number already exists!" << endl;
            return;
        }

        if (jointAccountCount < 3) {
            accounts[accNumber] = new JointAccount(accNumber, accHolderName, 0.0);
            jointAccountCount++;
            cout << "Joint account created successfully!" << endl;
        } else {
            cout << "Maximum joint account limit reached!" << endl;
        }
    }

    void deposit(string accNumber, double amount) {
        if (accounts.find(accNumber) != accounts.end()) {
            accounts[accNumber]->deposit(amount);
        } else {
            cout << "Account not found!" << endl;
        }
    }

    void withdraw(string accNumber, double amount) {
        if (accounts.find(accNumber) != accounts.end()) {
            accounts[accNumber]->withdraw(amount);
        } else {
            cout << "Account not found!" << endl;
        }
    }

    void checkBalance(string accNumber) {
        if (accounts.find(accNumber) != accounts.end()) {
            accounts[accNumber]->checkBalance();
        } else {
            cout << "Account not found!" << endl;
        }
    }

    void addNominee(string accNumber, string nominee) {
        if (accounts.find(accNumber) != accounts.end()) {
            JointAccount* jointAccount = dynamic_cast<JointAccount*>(accounts[accNumber]);
            if (jointAccount) {
                jointAccount->addNominee(nominee);
            } else {
                cout << "Not a joint account!" << endl;
            }
        } else {
            cout << "Account not found!" << endl;
        }
    }

    void listNominees(string accNumber) {
        if (accounts.find(accNumber) != accounts.end()) {
            JointAccount* jointAccount = dynamic_cast<JointAccount*>(accounts[accNumber]);
            if (jointAccount) {
                jointAccount->listNominees();
            } else {
                cout << "Not a joint account!" << endl;
            }
        } else {
            cout << "Account not found!" << endl;
        }
    }
};

int main() {
    BankingSystem bank;
    int choice;
    string accNumber, accHolderName, nominee;
    double amount;

    do {
        cout << "\n--- Banking System ---" << endl;
        cout << "1. Create Individual Account" << endl;
        cout << "2. Create Joint Account" << endl;
        cout << "3. Deposit Money" << endl;
        cout << "4. Withdraw Money" << endl;
        cout << "5. Check Balance" << endl;
        cout << "6. Add Nominee to Joint Account" << endl;
        cout << "7. List Nominees in Joint Account" << endl;
        cout << "8. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter account number: ";
            cin >> accNumber;
            cout << "Enter account holder name: ";
            cin.ignore();
            getline(cin, accHolderName);
            bank.createIndividualAccount(accNumber, accHolderName);
            break;
        case 2:
            cout << "Enter account number: ";
            cin >> accNumber;
            cout << "Enter account holder name: ";
            cin.ignore();
            getline(cin, accHolderName);
            bank.createJointAccount(accNumber, accHolderName);
            break;
        case 3:
            cout << "Enter account number: ";
            cin >> accNumber;
            cout << "Enter amount to deposit: ";
            cin >> amount;
            bank.deposit(accNumber, amount);
            break;
        case 4:
            cout << "Enter account number: ";
            cin >> accNumber;
            cout << "Enter amount to withdraw: ";
            cin >> amount;
            bank.withdraw(accNumber, amount);
            break;
        case 5:
            cout << "Enter account number: ";
            cin >> accNumber;
            bank.checkBalance(accNumber);
            break;
        case 6:
            cout << "Enter account number: ";
            cin >> accNumber;
            cout << "Enter nominee name: ";
            cin.ignore();
            getline(cin, nominee);
            bank.addNominee(accNumber, nominee);
            break;
        case 7:
            cout << "Enter account number: ";
            cin >> accNumber;
            bank.listNominees(accNumber);
            break;
        case 8:
            cout << "Exiting..." << endl;
            break;
        default:
            cout << "Invalid choice!" << endl;
        }
    } while (choice);

    return 0;
}