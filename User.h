#ifndef USER_H
#define USER_H

class User {
private:
    int id;
    char name[50];
    char username[50];
    char password[50];

public:
    User();
    User(int id, const char name[], const char username[], const char password[]);

    int getId() const;
    const char* getName() const;
    const char* getUsername() const;
    const char* getPassword() const;

    bool checkPassword(const char password[]) const;
    virtual void displayProfile() const;
    virtual ~User() {}
};

class Student : public User {
public:
    Student();
    Student(int id, const char name[], const char username[], const char password[]);
    void displayProfile() const override;
};

#endif
