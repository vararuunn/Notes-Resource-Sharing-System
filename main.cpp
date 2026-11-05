
#include "User.cpp"
#include "ResourceManager.cpp"

int main() {
    cout << "====================================\n";
    cout << "  Welcome to Notes and Resource Sharing System!\n";
    cout << "====================================\n\n";

    cout << "Notes and Resource Sharing System\n";

    ResourceManager manager;
    manager.loadFromFile("resources.txt");

    int choice = -1;
    while (choice != 0) {
        cout << "\n1. Add Resource\n2. Display Resources\n3. Search Resource\n";
        cout << "4. Like Resource\n5. Subject Statistics\n6. Open PDF Resource\n0. Exit\n";
        cout << "Enter choice: ";

        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(10000, '\n');
            choice = -1;
            cout << "Please enter a number.\n";
            continue;
        }
        cin.ignore(10000, '\n');

        if (choice == 1) {
            manager.addResource();
            manager.saveToFile("resources.txt");
        } else if (choice == 2) {
            manager.displayAll();
        } else if (choice == 3) {
            manager.searchResource();
        } else if (choice == 4) {
            manager.likeResource();
            manager.saveToFile("resources.txt");
        } else if (choice == 5) {
            manager.showSubjectStatistics();
        } else if (choice == 6) {
            manager.openResourceFile();
        } else if (choice == 0) {
            manager.saveToFile("resources.txt");
            cout << "Data saved. Goodbye!\n";
        } else {
            cout << "Invalid choice.\n";
        }
    }

    return 0;
}
