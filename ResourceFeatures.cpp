
void ResourceManager::filterBySubject() const {
    string subject;

    cout << "\nEnter subject to filter: ";
    getline(cin, subject);

    for (int i = 0; i < subject.length(); i++) {
        subject[i] = tolower((unsigned char)subject[i]);
    }

    bool found = false;

    for (int i = 0; i < count; i++) {
        string savedSubject = resources[i].getSubject();

        for (int j = 0; j < savedSubject.length(); j++) {
            savedSubject[j] = tolower((unsigned char)savedSubject[j]);
        }

        if (savedSubject == subject) {
            resources[i].display();
            cout << "--------------------\n";
            found = true;
        }
    }

    if (!found) {
        cout << "No resources found for this subject.\n";
    }
}

void ResourceManager::filterByType() const {
    int choice;
    string type;

    cout << "\n1. Complete Notes";
    cout << "\n2. Short Notes";
    cout << "\n3. Important Questions";
    cout << "\n4. Previous Year Questions";
    cout << "\n5. Revision Notes";
    cout << "\nChoose resource type: ";

    if (!(cin >> choice)) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Invalid choice.\n";
        return;
    }

    cin.ignore(10000, '\n');

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
        cout << "Invalid type.\n";
        return;
    }

    bool found = false;

    for (int i = 0; i < count; i++) {
        if (resources[i].getType() == type) {
            resources[i].display();
            cout << "--------------------\n";
            found = true;
        }
    }

    if (!found) {
        cout << "No resources found for this type.\n";
    }
}

void ResourceManager::sortByLikes() const {
    if (count == 0) {
        cout << "\nNo resources found.\n";
        return;
    }

    Resource* temp = new Resource[count];

    for (int i = 0; i < count; i++) {
        temp[i] = resources[i];
    }

    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (temp[j].getLikes() < temp[j + 1].getLikes()) {
                Resource t = temp[j];
                temp[j] = temp[j + 1];
                temp[j + 1] = t;
            }
        }
    }

    cout << "\nResources sorted by likes:\n";

    for (int i = 0; i < count; i++) {
        temp[i].display();
        cout << "--------------------\n";
    }

    delete[] temp;
}
