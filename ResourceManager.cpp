#include <iostream>
#include <fstream>
#include <iomanip>
#include <map>
#include <string>
#include <cstdlib>
using namespace std;

// No .h files are used. Include Resource.cpp to make Resource available here.
#include "Resource.cpp"

class ResourceManager {
private:
    Resource* resources;
    int count;
    int capacity;
    int nextId;

    void growArray();

public:
    ResourceManager();
    ~ResourceManager();

    ResourceManager(const ResourceManager&) = delete;
    ResourceManager& operator=(const ResourceManager&) = delete;

    void addResource();
    void displayAll() const;
    void searchResource() const;
    void likeResource();
    void showSubjectStatistics() const;
    void openResourceFile();

    void saveToFile(const string& filename) const;
    void loadFromFile(const string& filename);
};

ResourceManager::ResourceManager() {
    capacity = 2;
    count = 0;
    nextId = 1;
    resources = new Resource[capacity];
}

ResourceManager::~ResourceManager() {
    delete[] resources;
}

void ResourceManager::growArray() {
    capacity = capacity * 2;
    Resource* newArray = new Resource[capacity];

    for (int i = 0; i < count; i++) {
        newArray[i] = resources[i];
    }

    delete[] resources;
    resources = newArray;
}

void ResourceManager::addResource() {
    string title, subject, description, type, path;
    int choice;

    cout << "Enter title: ";
    getline(cin, title);
    cout << "Enter subject: ";
    getline(cin, subject);
    cout << "Enter description: ";
    getline(cin, description);

    cout << "\n1. Complete Notes\n2. Short Notes\n3. Important Questions\n";
    cout << "4. Previous Year Questions\n5. Revision Notes\n";
    cout << "Choose type: ";

    if (!(cin >> choice)) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Invalid choice.\n";
        return;
    }
    cin.ignore(10000, '\n');

    if (choice == 1) type = "Complete Notes";
    else if (choice == 2) type = "Short Notes";
    else if (choice == 3) type = "Important Questions";
    else if (choice == 4) type = "Previous Year Questions";
    else if (choice == 5) type = "Revision Notes";
    else {
        cout << "Invalid type. Resource not added.\n";
        return;
    }

    cout << "Enter file path (or press Enter to skip): ";
    getline(cin, path);

    if (count == capacity) {
        growArray();
    }

    resources[count] = Resource(nextId, title, subject, description, type, path);
    count++;
    nextId++;
    cout << "Resource added successfully!\n";
}

void ResourceManager::displayAll() const {
    if (count == 0) {
        cout << "No resources found.\n";
        return;
    }

    for (int i = 0; i < count; i++) {
        resources[i].display();
        cout << "--------------------\n";
    }
}

void ResourceManager::searchResource() const {
    string keyword;
    cout << "Enter title or subject: ";
    getline(cin, keyword);

    bool found = false;
    for (int i = 0; i < count; i++) {

        if (resources[i].getTitle().find(keyword) != string::npos ||
            resources[i].getSubject().find(keyword) != string::npos) {
            resources[i].display();
            found = true;
        }
    }

    if (!found) {
        cout << "No matching resource found.\n";
    }
}

void ResourceManager::likeResource() {
    int id;
    cout << "Enter resource ID to like: ";

    if (!(cin >> id)) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Invalid ID.\n";
        return;
    }
    cin.ignore(10000, '\n');

    for (int i = 0; i < count; i++) {
        if (resources[i].getId() == id) {
            resources[i].addLike();
            cout << "Resource liked!\n";
            return;
        }
    }
    cout << "Resource ID not found.\n";
}

void ResourceManager::showSubjectStatistics() const {
    map<string, int> subjectCount;

    for (int i = 0; i < count; i++) {

        subjectCount[resources[i].getSubject()]++;
    }

    if (subjectCount.empty()) {
        cout << "No statistics available.\n";
        return;
    }

    for (const auto& item : subjectCount) {
        cout << item.first << ": " << item.second << " resource(s)\n";
    }
}

void ResourceManager::openResourceFile() {
    int id;
    cout << "Enter resource ID to open: ";

    if (!(cin >> id)) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Invalid ID.\n";
        return;
    }
    cin.ignore(10000, '\n');

    for (int i = 0; i < count; i++) {
        if (resources[i].getId() == id) {
            string path = resources[i].getFilePath();
            if (path.size() >= 2 && path.front() == '\"' && path.back() == '\"') {
                path = path.substr(1, path.size() - 2);
            }
            if (path.empty()) {
                cout << "No file path saved for this resource.\n";
                return;
            }

            string command = "start \"\" \"" + path + "\"";
            int result = system(command.c_str());
            if (result != 0) {
                cout << "Could not open the file. Check the saved path.\n";
            }
            return;
        }
    }
    cout << "Resource ID not found.\n";
}

void ResourceManager::saveToFile(const string& filename) const {
    ofstream file(filename);
    if (!file) {
        cout << "Could not save data.\n";
        return;
    }

    file << count << '\n';
    for (int i = 0; i < count; i++) {
        file << resources[i].getId() << '\n';
        file << quoted(resources[i].getTitle()) << '\n';
        file << quoted(resources[i].getSubject()) << '\n';
        file << quoted(resources[i].getDescription()) << '\n';
        file << quoted(resources[i].getType()) << '\n';
        file << quoted(resources[i].getFilePath()) << '\n';
        file << resources[i].getLikes() << '\n';
    }
}

void ResourceManager::loadFromFile(const string& filename) {
    ifstream file(filename);
    if (!file) {
        return;
    }

    int savedCount;
    if (!(file >> savedCount)) {
        return;
    }

    for (int i = 0; i < savedCount; i++) {
        int id, likes;
        string title, subject, description, type, path;

        if (!(file >> id >> quoted(title) >> quoted(subject)
                  >> quoted(description) >> quoted(type)
                  >> quoted(path) >> likes)) {
            cout << "Could not read saved resources.\n";
            return;
        }

        if (count == capacity) {
            growArray();
        }

        resources[count] = Resource(id, title, subject, description, type, path, likes);
        count++;

        if (id >= nextId) {
            nextId = id + 1;
        }
    }
}

