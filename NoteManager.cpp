#include "NoteManager.h"
#include "FileManager.h"
#include <iostream>
#include <cstring>
#include <cctype>
#include <filesystem>
using namespace std;

static void input(char text[], int size, const char message[]) {
    cout << message;
    cin.getline(text, size);
}

static void chooseType(char type[]) {
    int choice;

    cout << "\nResource Type\n";
    cout << "1. Complete Notes\n";
    cout << "2. Short Notes\n";
    cout << "3. Important Questions\n";
    cout << "4. Previous Year Questions\n";
    cout << "5. Revision Notes\n";
    cout << "Enter choice: ";
    cin >> choice;
    cin.ignore(1000, '\n');

    if (choice == 1) strcpy(type, "Complete Notes");
    else if (choice == 2) strcpy(type, "Short Notes");
    else if (choice == 3) strcpy(type, "Important Questions");
    else if (choice == 4) strcpy(type, "Previous Year Questions");
    else if (choice == 5) strcpy(type, "Revision Notes");
    else strcpy(type, "Complete Notes");
}

NoteManager::NoteManager() {
    nextId = 1;
    FileManager::loadNotes(notes);

    for (int i = 0; i < notes.size(); i++) {
        if (notes.get(i)->getId() >= nextId)
            nextId = notes.get(i)->getId() + 1;

        subjectCount[notes.get(i)->getSubject()]++;
    }
}

DynamicArray& NoteManager::getNotes() {
    return notes;
}

int NoteManager::findNote(int id) const {
    for (int i = 0; i < notes.size(); i++) {
        if (notes.get(i)->getId() == id)
            return i;
    }
    return -1;
}

bool NoteManager::sameText(const char a[], const char b[]) const {
    int i = 0;

    while (a[i] && b[i]) {
        if (tolower(a[i]) != tolower(b[i]))
            return false;
        i++;
    }

    return a[i] == b[i];
}

bool NoteManager::contains(const char text[], const char key[]) const {
    if (key[0] == '\0')
        return true;

    for (int i = 0; text[i]; i++) {
        int j = 0;

        while (text[i + j] && key[j] &&
               tolower(text[i + j]) == tolower(key[j])) {
            j++;
        }

        if (key[j] == '\0')
            return true;
    }

    return false;
}

void NoteManager::addResource(int userId) {
    char title[100], subject[50], description[200];
    char type[40], source[300];

    cout << "\n===== ADD RESOURCE =====\n";
    input(title, 100, "Title: ");
    input(subject, 50, "Subject: ");
    input(description, 200, "Description: ");
    chooseType(type);

    cout << "Enter file path (leave empty if no file): ";
    cin.getline(source, 300);

    char savedPath[200] = "";

    if (source[0] != '\0') {
        filesystem::create_directories("uploaded_notes");

        filesystem::path filePath(source);
        string fileName = filePath.filename().string();
        string destination = "uploaded_notes/resource_" +
                             to_string(nextId) + "_" + fileName;

        if (FileManager::uploadFile(source, destination.c_str())) {
            strcpy(savedPath, destination.c_str());
            cout << "File uploaded successfully.\n";
        } else {
            cout << "File could not be uploaded. Resource will be saved without file.\n";
        }
    }

    notes.add(Note(nextId, userId, title, subject, description,
                   type, savedPath));
    subjectCount[subject]++;

    cout << "Resource added successfully. ID: " << nextId << "\n";
    nextId++;
    FileManager::saveNotes(notes);
}

void NoteManager::searchResources() const {
    char key[100];
    input(key, 100, "Search title, subject or keyword: ");

    bool found = false;

    for (int i = 0; i < notes.size(); i++) {
        const Note* n = notes.get(i);

        if (contains(n->getTitle(), key) ||
            contains(n->getSubject(), key) ||
            contains(n->getDescription(), key) ||
            contains(n->getType(), key)) {
            n->display();
            found = true;
        }
    }

    if (!found)
        cout << "No resource found.\n";
}

void NoteManager::viewResource(int id) {
    int index = findNote(id);

    if (index == -1) {
        cout << "Resource not found.\n";
        return;
    }

    notes.get(index)->addView();
    notes.get(index)->display();

    if (notes.get(index)->getFilePath()[0])
        cout << "You can open this file from the shown path.\n";

    FileManager::saveNotes(notes);
}

void NoteManager::likeResource(int id) {
    int index = findNote(id);

    if (index == -1) {
        cout << "Resource not found.\n";
        return;
    }

    notes.get(index)->like();
    cout << "Resource liked.\n";
    FileManager::saveNotes(notes);
}

void NoteManager::examMode() const {
    int choice;
    char subject[50];
    const char* wantedType;

    cout << "\n========== EXAM MODE ==========\n";
    cout << "1. Important Questions\n";
    cout << "2. Previous Year Question Papers\n";
    cout << "3. Revision Notes\n";
    cout << "4. Short Notes\n";
    cout << "5. Back\n";
    cout << "Enter choice: ";
    cin >> choice;
    cin.ignore(1000, '\n');

    if (choice == 5)
        return;

    if (choice == 1) wantedType = "Important Questions";
    else if (choice == 2) wantedType = "Previous Year Questions";
    else if (choice == 3) wantedType = "Revision Notes";
    else if (choice == 4) wantedType = "Short Notes";
    else {
        cout << "Invalid choice.\n";
        return;
    }

    input(subject, 50, "Enter subject (or ALL): ");

    bool found = false;

    for (int i = 0; i < notes.size(); i++) {
        const Note* n = notes.get(i);

        if (sameText(n->getType(), wantedType) &&
            (sameText(subject, "ALL") || sameText(n->getSubject(), subject))) {
            n->display();
            found = true;
        }
    }

    if (!found)
        cout << "No exam resource found.\n";
}

void NoteManager::dashboard(int userId) const {
    int myResources = 0;
    int myLikes = 0;
    int myViews = 0;

    for (int i = 0; i < notes.size(); i++) {
        const Note* n = notes.get(i);

        if (n->getOwnerId() == userId) {
            myResources++;
            myLikes += n->getLikes();
            myViews += n->getViews();
        }
    }

    cout << "\n========== STUDY DASHBOARD ==========\n";
    cout << "My resources : " << myResources << "\n";
    cout << "My likes     : " << myLikes << "\n";
    cout << "My views     : " << myViews << "\n";
    cout << "All resources: " << notes.size() << "\n";
    cout << "\nStudy options:\n";
    cout << "- Exam Mode\n";
    cout << "- Subject Tree\n";
    cout << "- Smart Recommendations\n";
    cout << "- Subject Statistics\n";
}

void NoteManager::recommendations() const {
    char subject[50];
    input(subject, 50, "Enter a subject you are studying: ");

    cout << "\n===== SMART RECOMMENDATIONS =====\n";
    cout << "Resources related to " << subject << ":\n";

    int shown = 0;

    for (int i = 0; i < notes.size() && shown < 5; i++) {
        const Note* n = notes.get(i);

        if (sameText(n->getSubject(), subject)) {
            cout << shown + 1 << ". " << n->getTitle()
                 << " - " << n->getType() << "\n";
            shown++;
        }
    }

    if (shown == 0)
        cout << "No matching resources found. Add more resources for this subject.\n";
    else
        cout << "These are recommended because they match your selected subject.\n";
}

void NoteManager::showSubjectStatistics() const {
    cout << "\n===== SUBJECT STATISTICS =====\n";

    if (subjectCount.empty()) {
        cout << "No resources available.\n";
        return;
    }

    std::map<std::string, int>::const_iterator it;
    for (it = subjectCount.begin(); it != subjectCount.end(); ++it)
        cout << it->first << " : " << it->second << " resources\n";
}
