#include "FileManager.h"
#include <fstream>
#include <filesystem>
using namespace std;

void FileManager::saveUsers(User users[], int count) {
    ofstream file("users.txt");

    for (int i = 0; i < count; i++) {
        file << users[i].getId() << '|'
             << users[i].getName() << '|'
             << users[i].getUsername() << '|'
             << users[i].getPassword() << '\n';
    }
}

int FileManager::loadUsers(User users[], int maxUsers) {
    ifstream file("users.txt");
    if (!file)
        return 0;

    int count = 0;
    int id;
    char name[50], username[50], password[50];

    while (count < maxUsers && file >> id) {
        file.ignore(1);
        file.getline(name, 50, '|');
        file.getline(username, 50, '|');
        file.getline(password, 50);

        users[count] = User(id, name, username, password);
        count++;
    }

    return count;
}

void FileManager::saveNotes(const DynamicArray& notes) {
    ofstream file("notes.txt");

    for (int i = 0; i < notes.size(); i++) {
        const Note* n = notes.get(i);

        file << n->getId() << '|'
             << n->getOwnerId() << '|'
             << n->getTitle() << '|'
             << n->getSubject() << '|'
             << n->getDescription() << '|'
             << n->getType() << '|'
             << n->getFilePath() << '|'
             << n->getLikes() << '|'
             << n->getViews() << '\n';
    }
}

void FileManager::loadNotes(DynamicArray& notes) {
    ifstream file("notes.txt");
    if (!file)
        return;

    int id, owner, likes, views;
    char title[100], subject[50], description[200];
    char type[40], path[200];

    while (file >> id) {
        file.ignore(1);
        file >> owner;
        file.ignore(1);
        file.getline(title, 100, '|');
        file.getline(subject, 50, '|');
        file.getline(description, 200, '|');
        file.getline(type, 40, '|');
        file.getline(path, 200, '|');
        file >> likes;
        file.ignore(1);
        file >> views;
        file.ignore(1000, '\n');

        notes.add(Note(id, owner, title, subject, description,
                       type, path, likes, views));
    }
}

bool FileManager::uploadFile(const char source[], const char destination[]) {
    ifstream input(source, ios::binary);
    ofstream output(destination, ios::binary);

    if (!input || !output)
        return false;

    output << input.rdbuf();
    return true;
}
