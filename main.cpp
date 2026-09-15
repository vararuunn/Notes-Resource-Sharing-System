#include <iostream>
#include <cstring>
#include "User.h"
#include "NoteManager.h"
#include "FileManager.h"
using namespace std;

const int MAX_USERS = 100;
User users[MAX_USERS];
int userCount = 0;

int findUser(const char username[]) {
    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].getUsername(), username) == 0)
            return i;
    }
    return -1;
}

void registerUser() {
    if (userCount >= MAX_USERS) {
        cout << "User limit reached.\n";
        return;
    }

    char name[50], username[50], password[50];

    cout << "\n===== REGISTER =====\n";
    cout << "Name: ";
    cin.getline(name, 50);
    cout << "Username: ";
    cin.getline(username, 50);

    if (findUser(username) != -1) {
        cout << "Username already exists.\n";
        return;
    }

    cout << "Password: ";
    cin.getline(password, 50);

    int id = userCount + 1;
    users[userCount] = User(id, name, username, password);
    userCount++;
    FileManager::saveUsers(users, userCount);

    cout << "Registration successful. Your ID is " << id << "\n";
}

int login() {
    char username[50], password[50];

    cout << "\n===== LOGIN =====\n";
    cout << "Username: ";
    cin.getline(username, 50);
    cout << "Password: ";
    cin.getline(password, 50);

    int index = findUser(username);

    if (index != -1 && users[index].checkPassword(password)) {
        cout << "Login successful.\n";
        return index;
    }

    cout << "Invalid username or password.\n";
    return -1;
}

void userMenu(int userIndex, NoteManager& manager) {
    int choice;

    while (true) {
        cout << "\n======================================\n";
        cout << "       NOTES RESOURCE SYSTEM\n";
        cout << "======================================\n";
        cout << "1. Study Dashboard\n";
        cout << "2. View Profile\n";
        cout << "3. Add Resource\n";
        cout << "4. Search Resources\n";
        cout << "5. View Resource\n";
        cout << "6. Like Resource\n";
        cout << "7. Exam Mode\n";
        cout << "8. Smart Recommendations\n";
        cout << "9. Subject Statistics\n";
        cout << "10. Save Data\n";
        cout << "11. Logout\n";
        cout << "Enter choice: ";
        cin >> choice;
        cin.ignore(1000, '\n');

        if (choice == 1)
            manager.dashboard(users[userIndex].getId());
        else if (choice == 2)
            users[userIndex].displayProfile();
        else if (choice == 3)
            manager.addResource(users[userIndex].getId());
        else if (choice == 4)
            manager.searchResources();
        else if (choice == 5) {
            int id;
            cout << "Resource ID: ";
            cin >> id;
            cin.ignore(1000, '\n');
            manager.viewResource(id);
        }
        else if (choice == 6) {
            int id;
            cout << "Resource ID: ";
            cin >> id;
            cin.ignore(1000, '\n');
            manager.likeResource(id);
        }
        else if (choice == 7)
            manager.examMode();
        else if (choice == 8)
            manager.recommendations();
        else if (choice == 9)
            manager.showSubjectStatistics();
        else if (choice == 10) {
            FileManager::saveUsers(users, userCount);
            FileManager::saveNotes(manager.getNotes());
            cout << "Data saved.\n";
        }
        else if (choice == 11)
            return;
        else
            cout << "Invalid choice.\n";
    }
}

int main() {
    userCount = FileManager::loadUsers(users, MAX_USERS);

    if (userCount == 0) {
        users[0] = User(1, "Demo Student", "demo", "1234");
        userCount = 1;
        FileManager::saveUsers(users, userCount);
    }

    NoteManager manager;
    int choice;

    while (true) {
        cout << "\n========== WELCOME ==========\n";
        cout << "1. Login\n";
        cout << "2. Register\n";
        cout << "3. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;
        cin.ignore(1000, '\n');

        if (choice == 1) {
            int userIndex = login();
            if (userIndex != -1)
                userMenu(userIndex, manager);
        }
        else if (choice == 2)
            registerUser();
        else if (choice == 3) {
            FileManager::saveUsers(users, userCount);
            FileManager::saveNotes(manager.getNotes());
            cout << "Goodbye!\n";
            break;
        }
        else
            cout << "Invalid choice.\n";
    }

    return 0;
}
