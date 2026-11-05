#include <iostream>
#include <string>
using namespace std;

class User {
protected:

    string name;

public:
    User(string userName);

    virtual void displayProfile();

    virtual ~User() {}
};

class Student : public User {
public:
    Student(string studentName);

    void displayProfile() override;
};

User::User(string userName) {
    name = userName;
}

void User::displayProfile() {
    cout << "User: " << name << "\n";
}

Student::Student(string studentName) : User(studentName) {
}

void Student::displayProfile() {
    cout << "\nWelcome, " << name << "!\n";
    cout << "Role: Student\n";
}
