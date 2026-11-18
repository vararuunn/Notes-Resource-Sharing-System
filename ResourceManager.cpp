
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <limits>
#include <cctype>
#include <cstdlib>
using namespace std;

#include "Resource.cpp"

class ResourceManager {
private:
    Resource* resources;
    int count;
    int capacity;

    void growArray() {
        capacity = capacity * 2;

        Resource* newArray = new Resource[capacity];

        for (int i = 0; i < count; i++) {
            newArray[i] = resources[i];
        }

        delete[] resources;
        resources = newArray;
    }

public:
    ResourceManager() {
        count = 0;
        capacity = 2;
        resources = new Resource[capacity];
        loadFromFile();
    }

    ~ResourceManager() {
        saveToFile();
        delete[] resources;
    }

    void addResource();
    void displayAll() const;
    void searchResource() const;
    void editResource();
    void deleteResource();
    void likeResource();
    void showSubjectStatistics() const;
    void openResourceFile();

    void filterBySubject() const;
    void filterByType() const;
    void sortByLikes() const;

    void saveToFile() const;
    void loadFromFile();

    int getCount() const {
        return count;
    }

    const Resource& getResource(int index) const {
        return resources[index];
    }
};

#include "ResourceFeatures.cpp"

void ResourceManager::addResource() {
    if (count == capacity) {
        growArray();
    }

    int id, choice;
    string title, subject, description, type, filePath;

    cout << "\nEnter Resource ID: ";
    cin >> id;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Enter Title: ";
    getline(cin, title);

    cout << "Enter Subject: ";
    getline(cin, subject);

    cout << "Enter Description: ";
    getline(cin, description);

    cout << "\n1. Complete Notes";
    cout << "\n2. Short Notes";
    cout << "\n3. Important Questions";
    cout << "\n4. Previous Year Questions";
    cout << "\n5. Revision Notes";
    cout << "\nEnter Resource Type: ";

    cin >> choice;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (choice == 1)
        type = "Complete Notes";
    else if (choice == 2)
        type = "Short Notes";
    else if (choice == 3)
        type = "Important Questions";
    else if (choice == 4)
        type = "Previous Year Questions";
    else if (choice == 5)
        type = "Revision Notes";
    else {
        cout << "Invalid choice.\n";
        return;
    }

    cout << "Enter Google Drive link or file path: ";
    getline(cin, filePath);

    resources[count] = Resource(id, title, subject, description,
                                type, filePath);

    count++;

    saveToFile();

    cout << "\nResource added successfully!\n";
}

void ResourceManager::displayAll() const {
    if (count == 0) {
        cout << "\nNo resources available.\n";
        return;
    }

    cout << "\n===== ALL RESOURCES =====\n";

    for (int i = 0; i < count; i++) {
        resources[i].display();
        cout << "--------------------\n";
    }
}

void ResourceManager::searchResource() const {
    string search;

    cout << "\nEnter title to search: ";
    getline(cin, search);

    for (int i = 0; i < (int)search.length(); i++) {
        search[i] = tolower((unsigned char)search[i]);
    }

    bool found = false;

    for (int i = 0; i < count; i++) {
        string title = resources[i].getTitle();

        for (int j = 0; j < (int)title.length(); j++) {
            title[j] = tolower((unsigned char)title[j]);
        }

        if (title.find(search) != string::npos) {
            resources[i].display();
            cout << "--------------------\n";
            found = true;
        }
    }

    if (!found) {
        cout << "\nResource not found.\n";
    }
}

void ResourceManager::editResource() {
    int id;

    cout << "\nEnter Resource ID to edit: ";
    cin >> id;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (int i = 0; i < count; i++) {
        if (resources[i].getId() == id) {
            string title, subject, description, filePath;

            cout << "Enter new Title: ";
            getline(cin, title);

            cout << "Enter new Subject: ";
            getline(cin, subject);

            cout << "Enter new Description: ";
            getline(cin, description);

            cout << "Enter new Google Drive link or file path: ";
            getline(cin, filePath);

            string type = resources[i].getType();
            int likes = resources[i].getLikes();

            resources[i] = Resource(id, title, subject,
                                    description, type,
                                    filePath, likes);

            saveToFile();

            cout << "\nResource updated successfully!\n";
            return;
        }
    }

    cout << "\nResource ID not found.\n";
}

void ResourceManager::deleteResource() {
    int id;

    cout << "\nEnter Resource ID to delete: ";
    cin >> id;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (int i = 0; i < count; i++) {
        if (resources[i].getId() == id) {
            for (int j = i; j < count - 1; j++) {
                resources[j] = resources[j + 1];
            }

            count--;
            saveToFile();

            cout << "\nResource deleted successfully!\n";
            return;
        }
    }

    cout << "\nResource ID not found.\n";
}

void ResourceManager::likeResource() {
    int id;

    cout << "\nEnter Resource ID to like: ";
    cin >> id;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (int i = 0; i < count; i++) {
        if (resources[i].getId() == id) {
            resources[i].addLike();
            saveToFile();

            cout << "\nResource liked successfully!\n";
            return;
        }
    }

    cout << "\nResource ID not found.\n";
}

void ResourceManager::showSubjectStatistics() const {
    if (count == 0) {
        cout << "\nNo resources available.\n";
        return;
    }

    cout << "\n===== SUBJECT STATISTICS =====\n";

    for (int i = 0; i < count; i++) {
        bool alreadyCounted = false;

        for (int j = 0; j < i; j++) {
            if (resources[i].getSubject() ==
                resources[j].getSubject()) {
                alreadyCounted = true;
                break;
            }
        }

        if (!alreadyCounted) {
            int total = 0;

            for (int j = 0; j < count; j++) {
                if (resources[i].getSubject() ==
                    resources[j].getSubject()) {
                    total++;
                }
            }

            cout << resources[i].getSubject()
                 << " : " << total << " resources\n";
        }
    }
}

void ResourceManager::openResourceFile() {
    int id;

    cout << "\nEnter Resource ID to open: ";
    cin >> id;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (int i = 0; i < count; i++) {
        if (resources[i].getId() == id) {
            string path = resources[i].getFilePath();

            if (path.empty()) {
                cout << "\nNo file link available.\n";
                return;
            }

            string command = "start \"\" \"" + path + "\"";
            system(command.c_str());

            cout << "\nOpening resource...\n";
            return;
        }
    }

    cout << "\nResource ID not found.\n";
}

void ResourceManager::saveToFile() const {
    ofstream file("resources.txt");

    if (!file) {
        cout << "\nUnable to save resources.\n";
        return;
    }

    file << count << "\n";

    for (int i = 0; i < count; i++) {
        file << resources[i].getId() << "\n";
        file << quoted(resources[i].getTitle()) << "\n";
        file << quoted(resources[i].getSubject()) << "\n";
        file << quoted(resources[i].getDescription()) << "\n";
        file << quoted(resources[i].getType()) << "\n";
        file << quoted(resources[i].getFilePath()) << "\n";
        file << resources[i].getLikes() << "\n";
    }

    file.close();
}

void ResourceManager::loadFromFile() {
    ifstream file("resources.txt");

    if (!file) {
        return;
    }

    int total;

    if (!(file >> total)) {
        return;
    }

    for (int i = 0; i < total; i++) {
        int id, likes;
        string title, subject, description, type, filePath;

        if (!(file >> id
                  >> quoted(title)
                  >> quoted(subject)
                  >> quoted(description)
                  >> quoted(type)
                  >> quoted(filePath)
                  >> likes)) {
            break;
        }

        if (count == capacity) {
            growArray();
        }

        resources[count] = Resource(id, title, subject,
                                    description, type,
                                    filePath, likes);

        count++;
    }

    file.close();
}
