#include "User.h"
#include <iostream>
#include <cstring>
using namespace std;

void copyText(char destination[], const char source[], int size) {
    strncpy(destination, source, size - 1);
    destination[size - 1] = '\0';
}

User::User() : id(0) {
    name[0] = username[0] = password[0] = '\0';
}

User::User(int i, const char n[], const char u[], const char p[]) : id(i) {
    copyText(name, n, 50);
    copyText(username, u, 50);
    copyText(password, p, 50);
}

int User::getId() const { return id; }
const char* User::getName() const { return name; }
const char* User::getUsername() const { return username; }
const char* User::getPassword() const { return password; }

bool User::checkPassword(const char p[]) const {
    return strcmp(password, p) == 0;
}

void User::displayProfile() const {
    cout << "Name: " << name << "\n";
    cout << "Username: " << username << "\n";
    cout << "User ID: " << id << "\n";
}

Student::Student() : User() {}

Student::Student(int i, const char n[], const char u[], const char p[])
    : User(i, n, u, p) {}

void Student::displayProfile() const {
    cout << "\n===== STUDENT PROFILE =====\n";
    User::displayProfile();
    cout << "Role: Student\n";
}
