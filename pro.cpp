#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// ---------- STRUCT ----------
struct profile {
    string name, job, password;
    long long age, atm, m_level, e_level, m_cbt, e_cbt, salary, No;
    float bank_bal;
};

// ---------- FUNCTION DECLARATIONS ----------
void cbt(profile &user);
bool login(profile &user);
void learningZone(profile &user);
void careerPayroll(profile &user);
void bankSystem(profile &user);
void atmSystem(profile &user);
void viewProfile(const profile &user);
void saveProfile(const profile &user);

// ---------- MAIN ----------
int main() {
    profile user;
    char firstChoice;
    int attempts = 0;
    bool loggedIn = false;

    cout << "Welcome to the Program\n";

    // ---------- CREATE / LOGIN ----------
    while (attempts < 5) {
        cout << "Create or Login (c/l): ";
        cin >> firstChoice;

        // CREATE
        if (firstChoice == 'c' || firstChoice == 'C') {
            cin.ignore();

            cout << "Enter Name: ";
            getline(cin, user.name);

            cout << "Enter Age: ";
            cin >> user.age;

            cout << "Create Password: ";
            cin >> user.password;

            cout << "Enter Personal No: ";
            cin >> user.No;

            cout << "Set ATM Pin: ";
            cin >> user.atm;

            // Initialize defaults
            user.m_level = 0;
            user.e_level = 0;
            user.m_cbt = 0;
            user.e_cbt = 0;
            user.salary = 0;
            user.bank_bal = 0;
            user.job = "Unemployed";

            saveProfile(user);

            cout << "\nProfile created successfully!\n";
            loggedIn = true;
            break;
        }

        // LOGIN
        else if (firstChoice == 'l' || firstChoice == 'L') {
            if (login(user)) {
                loggedIn = true;
                break;
            } else {
                attempts++;
            }
        }

        else {
            cout << "Invalid option!\n";
            attempts++;
        }
    }

    if (!loggedIn) {
        cout << "Too many attempts. Program exiting.\n";
        return 0;
    }

    // ---------- MAIN HUB ----------
    int choice;
    do {
        cout << "\n========== MAIN HUB ==========\n";
        cout << "1. Learning Zone\n";
        cout << "2. CBT Test\n";
        cout << "3. Career & Payroll\n";
        cout << "4. Bank\n";
        cout << "5. ATM\n";
        cout << "6. View Profile\n";
        cout << "7. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: learningZone(user); break;
            case 2: cbt(user); break;
            case 3: careerPayroll(user); break;
            case 4: bankSystem(user); break;
            case 5: atmSystem(user); break;
            case 6: viewProfile(user); break;
            case 7:
                saveProfile(user);
                cout << "Progress saved. Goodbye!\n";
                break;
            default:
                cout << "Invalid choice!\n";
        }

    } while (choice != 7);

    return 0;
}

// ---------- LOGIN ----------
bool login(profile &user) {
    ifstream file("profile.txt");
    if (!file) {
        cout << "No account found!\n";
        return false;
    }

    getline(file, user.name);
    file >> user.age;
    file >> user.atm;
    file >> user.m_level;
    file >> user.e_level;
    file >> user.m_cbt;
    file >> user.e_cbt;
    file.ignore();
    getline(file, user.job);
    file >> user.salary;
    file >> user.bank_bal;
    file >> user.No;
    file >> user.password;
    file.close();

    string pass;
    for (int i = 0; i < 5; i++) {
        cout << "Enter Password: ";
        cin >> pass;

        if (pass == user.password) {
            cout << "Login successful!\n";
            return true;
        }

        cout << "Wrong password! Attempts left: " << 4 - i << endl;
    }

    return false;
}

// ---------- SAVE PROFILE ----------
void saveProfile(const profile &user) {
    ofstream file("profile.txt");

    file << user.name << '\n'
         << user.age << '\n'
         << user.atm << '\n'
         << user.m_level << '\n'
         << user.e_level << '\n'
         << user.m_cbt << '\n'
         << user.e_cbt << '\n'
         << user.job << '\n'
         << user.salary << '\n'
         << user.bank_bal << '\n'
         << user.No << '\n'
         << user.password << '\n';

    file.close();
}

// ---------- LEARNING ZONE ----------
void learningZone(profile &user) {
    int choice, ans;

    cout << "\n[Learning Zone]\n1. Maths\n2. English\n3. Back\n";
    cin >> choice;

    if (choice == 1) {
        cout << "6 + 12 = ";
        cin >> ans;
        if (ans == 18) user.m_level++;
    }
    else if (choice == 2) {
        cout << "She __ a good player (1.is 2.was): ";
        cin >> ans;
        if (ans == 1) user.e_level++;
    }
}

// ---------- CBT ----------
void cbt(profile &user) {
    if (user.m_level < 1 || user.e_level < 1) {
        cout << "CBT locked. Practice more.\n";
        return;
    }

    int score = 0, ans;

    cout << "10 / 2 = ? (1.3 2.5 3.8): ";
    cin >> ans;
    if (ans == 2) score += 50;

    cout << "She __ a good girl (1.is 2.bad): ";
    cin >> ans;
    if (ans == 1) score += 50;

    user.m_cbt = score;
    user.e_cbt = score;

    cout << "Your score: " << score << "%\n";
}

// ---------- CAREER ----------
void careerPayroll(profile &user) {
    float avg = (user.m_cbt + user.e_cbt) / 2.0f;

    if (avg < 50) {
        user.job = "Unemployed";
        user.salary = 0;
    }
    else if (avg <= 70) {
        user.job = "Clerk";
        user.salary = 50000;
    }
    else if (avg <= 85) {
        user.job = "Officer";
        user.salary = 70000;
    }
    else {
        user.job = "Manager";
        user.salary = 100000;
    }

    user.bank_bal += user.salary;

    cout << "Job: " << user.job << "\nSalary credited: " << user.salary << endl;
}

// ---------- BANK ----------
void bankSystem(profile &user) {
    int choice, amount;

    cout << "\n1.Check Balance\n2.Deposit\n3.Withdraw\n4.Back\n";
    cin >> choice;

    if (choice == 1) {
        cout << "Balance: " << user.bank_bal << endl;
    }
    else if (choice == 2) {
        cout << "Enter amount: ";
        cin >> amount;
        user.bank_bal += amount;
        cout << "Deposited successfully.\n";
    }
    else if (choice == 3) {
        cout << "Enter amount: ";
        cin >> amount;

        if (amount <= user.bank_bal) {
            user.bank_bal -= amount;
            cout << "Withdrawn successfully.\n";
        }
        else {
            cout << "Insufficient balance!\n";
        }
    }
}

// ---------- ATM ----------
void atmSystem(profile &user) {
    int pin;

    for (int i = 0; i < 3; i++) {
        cout << "Enter ATM PIN: ";
        cin >> pin;

        if (pin == user.atm) {
            cout << "Access granted.\n";
            break;
        }

        if (i == 2) {
            cout << "Card blocked!\n";
            return;
        }

        cout << "Wrong PIN.\n";
    }

    int choice, amount;

    cout << "1.Balance\n2.Withdraw\n3.Back\n";
    cin >> choice;

    if (choice == 1) {
        cout << "Balance: " << user.bank_bal << endl;
    }
    else if (choice == 2) {
        cout << "Enter amount: ";
        cin >> amount;

        if (amount <= user.bank_bal) {
            user.bank_bal -= amount;
            cout << "Withdrawal successful.\n";
        }
        else {
            cout << "Insufficient balance!\n";
        }
    }
}

// ---------- VIEW PROFILE ----------
void viewProfile(const profile &user) {
    cout << "\nName: " << user.name
         << "\nAge: " << user.age
         << "\nMath Level: " << user.m_level
         << "\nEnglish Level: " << user.e_level
         << "\nJob: " << user.job
         << "\nSalary: " << user.salary
         << "\nBalance: " << user.bank_bal << endl;
}
