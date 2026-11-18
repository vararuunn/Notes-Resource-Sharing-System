#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <limits>
#include <cctype>
#include <cstdlib>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>

using namespace std;

// ==========================================
// 1. User Profile Class
// ==========================================
class User {
protected:
    string name;

public:
    User(string userName) : name(userName) {}
    virtual void displayProfile() {
        cout << "User: " << name << "\n";
    }
    virtual ~User() {}
};

class Student : public User {
public:
    Student(string studentName) : User(studentName) {}
    void displayProfile() override {
        cout << "\nWelcome, " << name << "!\n"
             << "Role: Student\n";
    }
};

// ==========================================
// 2. Resource Class
// ==========================================
class Resource {
private:
    int id;
    string title;
    string subject;
    string description;
    string type;
    string filePath;
    int likes;

public:
    Resource() : id(0), likes(0) {}

    Resource(int resourceId, string resourceTitle, string resourceSubject,
             string resourceDescription, string resourceType,
             string resourceFilePath, int likeCount = 0)
        : id(resourceId), title(resourceTitle), subject(resourceSubject),
          description(resourceDescription), type(resourceType),
          filePath(resourceFilePath), likes(likeCount) {}

    int getId() const { return id; }
    string getTitle() const { return title; }
    string getSubject() const { return subject; }
    string getDescription() const { return description; }
    string getType() const { return type; }
    string getFilePath() const { return filePath; }
    int getLikes() const { return likes; }

    void addLike() { likes++; }

    void display() const {
        cout << "\nID: " << id
             << "\nTitle: " << title
             << "\nSubject: " << subject
             << "\nType: " << type
             << "\nDescription: " << description
             << "\nFile path: " << (filePath.empty() ? "Not provided" : filePath)
             << "\nLikes: " << likes << "\n";
    }
};

// ==========================================
// 3. Quiz System Class
// ==========================================
class Quiz {
public:
    void addQuestion() {
        ofstream file("questions.txt", ios::app);
        if (!file) {
            cout << "Error opening file to save question.\n";
            return;
        }

        string question, a, b, c, d;
        char answer;

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "\nEnter question: ";
        getline(cin, question);
        cout << "Option A: "; getline(cin, a);
        cout << "Option B: "; getline(cin, b);
        cout << "Option C: "; getline(cin, c);
        cout << "Option D: "; getline(cin, d);
        cout << "Correct answer (A/B/C/D): ";
        cin >> answer;

        answer = toupper(answer);
        if (answer < 'A' || answer > 'D') {
            cout << "Invalid answer choice. Question discarded.\n";
            return;
        }

        file << question << "\n" << a << "\n" << b << "\n" << c << "\n" << d << "\n" << answer << "\n";
        file.close();
        cout << "\nQuestion added successfully!\n";
    }

    void displayQuestions() {
        ifstream file("questions.txt");
        if (!file) {
            cout << "\nNo questions available yet.\n";
            return;
        }

        string question, a, b, c, d;
        char answer;
        int count = 0;

        while (getline(file, question)) {
            if (!getline(file, a) || !getline(file, b) || !getline(file, c) || !getline(file, d) || !(file >> answer))
                break;

            file.ignore(numeric_limits<streamsize>::max(), '\n');
            count++;

            cout << "\nQ" << count << ". " << question
                 << "\nA. " << a << "\nB. " << b << "\nC. " << c << "\nD. " << d << "\n";
        }

        if (count == 0) cout << "\nNo questions found.\n";
    }

    void startQuiz() {
        ifstream file("questions.txt");
        if (!file) {
            cout << "\nNo quiz questions available. Please add some first.\n";
            return;
        }

        string question, a, b, c, d;
        char correct, userAnswer;
        int score = 0, total = 0;

        while (getline(file, question)) {
            if (!getline(file, a) || !getline(file, b) || !getline(file, c) || !getline(file, d) || !(file >> correct))
                break;

            file.ignore(numeric_limits<streamsize>::max(), '\n');
            total++;

            cout << "\nQ" << total << ". " << question
                 << "\nA. " << a << "\nB. " << b << "\nC. " << c << "\nD. " << d
                 << "\nYour answer: ";
            cin >> userAnswer;

            if (toupper(userAnswer) == correct) {
                cout << "Correct!\n";
                score++;
            } else {
                cout << "Wrong! Correct answer was: " << correct << "\n";
            }
        }

        if (total == 0) {
            cout << "\nQuiz is empty.\n";
            return;
        }

        cout << "\n===== QUIZ RESULTS =====\n"
             << "Total Questions: " << total << "\n"
             << "Correct: " << score << "\n"
             << "Score: " << score << "/" << total << "\n";
    }
};

// ==========================================
// 4. Resource Review & Rating Class
// ==========================================
class ResourceReview {
public:
    void addReview() {
        int id, rating;
        string comment;

        cout << "\nEnter Resource ID to review: ";
        if (!(cin >> id)) {
            cin.clear(); cin.ignore(10000, '\n');
            cout << "Invalid input.\n";
            return;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "Enter rating (1 to 5 stars): ";
        if (!(cin >> rating) || rating < 1 || rating > 5) {
            cin.clear(); cin.ignore(10000, '\n');
            cout << "Invalid rating. Must be between 1 and 5.\n";
            return;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "Enter your review comment: ";
        getline(cin, comment);

        ofstream file("reviews.txt", ios::app);
        if (!file) {
            cout << "Unable to save review.\n";
            return;
        }

        file << id << "\n" << rating << "\n" << quoted(comment) << "\n";
        file.close();
        cout << "\nReview added successfully!\n";
    }

    void displayReviews() {
        int targetId;
        cout << "\nEnter Resource ID to view reviews: ";
        if (!(cin >> targetId)) {
            cin.clear(); cin.ignore(10000, '\n');
            cout << "Invalid input.\n";
            return;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        ifstream file("reviews.txt");
        if (!file) {
            cout << "\nNo reviews found.\n";
            return;
        }

        int id, rating, count = 0;
        string comment;
        double totalRating = 0;

        cout << "\n===== REVIEWS FOR RESOURCE #" << targetId << " =====\n";
        while (file >> id >> rating >> quoted(comment)) {
            if (id == targetId) {
                count++;
                totalRating += rating;
                cout << "\nRating: " << rating << "/5 stars\n"
                     << "Comment: " << comment << "\n--------------------\n";
            }
        }
        file.close();

        if (count == 0) {
            cout << "No reviews for this resource yet.\n";
        } else {
            cout << "\nAverage Rating: " << fixed << setprecision(1) 
                 << (totalRating / count) << "/5.0 (" << count << " reviews)\n";
        }
    }
};

// ==========================================
// 5. Resource Manager Class
// ==========================================
class ResourceManager {
private:
    Resource* resources;
    int count;
    int capacity;

    void growArray() {
        capacity *= 2;
        Resource* newArray = new Resource[capacity];
        for (int i = 0; i < count; i++) newArray[i] = resources[i];
        delete[] resources;
        resources = newArray;
    }

public:
    ResourceManager() : count(0), capacity(2) {
        resources = new Resource[capacity];
        loadFromFile();
    }

    ~ResourceManager() {
        saveToFile();
        delete[] resources;
    }

    void addResource() {
        if (count == capacity) growArray();

        int id, choice;
        string title, subject, description, type, filePath;

        cout << "\nEnter Resource ID: ";
        cin >> id;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "Enter Title: "; getline(cin, title);
        cout << "Enter Subject: "; getline(cin, subject);
        cout << "Enter Description: "; getline(cin, description);

        cout << "\n1. Complete Notes\n2. Short Notes\n3. Important Questions\n4. Previous Year Questions\n5. Revision Notes\nChoose Type: ";
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        string types[] = {"", "Complete Notes", "Short Notes", "Important Questions", "Previous Year Questions", "Revision Notes"};
        if (choice >= 1 && choice <= 5) {
            type = types[choice];
        } else {
            cout << "Invalid resource type choice.\n";
            return;
        }

        cout << "Enter Google Drive link or file path: ";
        getline(cin, filePath);

        resources[count++] = Resource(id, title, subject, description, type, filePath);
        saveToFile();
        cout << "\nResource added successfully!\n";
    }

    void displayAll() const {
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

    void searchResource() const {
        string search;
        cout << "\nEnter title to search: ";
        getline(cin, search);
        transform(search.begin(), search.end(), search.begin(), ::tolower);

        bool found = false;
        for (int i = 0; i < count; i++) {
            string title = resources[i].getTitle();
            transform(title.begin(), title.end(), title.begin(), ::tolower);

            if (title.find(search) != string::npos) {
                resources[i].display();
                cout << "--------------------\n";
                found = true;
            }
        }
        if (!found) cout << "\nNo matching resources found.\n";
    }

    void editResource() {
        int id;
        cout << "\nEnter Resource ID to edit: ";
        cin >> id;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        for (int i = 0; i < count; i++) {
            if (resources[i].getId() == id) {
                string title, subject, description, filePath;
                cout << "Enter new Title: "; getline(cin, title);
                cout << "Enter new Subject: "; getline(cin, subject);
                cout << "Enter new Description: "; getline(cin, description);
                cout << "Enter new File path/Link: "; getline(cin, filePath);

                resources[i] = Resource(id, title, subject, description, resources[i].getType(), filePath, resources[i].getLikes());
                saveToFile();
                cout << "\nResource updated successfully!\n";
                return;
            }
        }
        cout << "\nResource ID not found.\n";
    }

    void deleteResource() {
        int id;
        cout << "\nEnter Resource ID to delete: ";
        cin >> id;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        for (int i = 0; i < count; i++) {
            if (resources[i].getId() == id) {
                for (int j = i; j < count - 1; j++) resources[j] = resources[j + 1];
                count--;
                saveToFile();
                cout << "\nResource deleted successfully!\n";
                return;
            }
        }
        cout << "\nResource ID not found.\n";
    }

    void likeResource() {
        int id;
        cout << "\nEnter Resource ID to like: ";
        cin >> id;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        for (int i = 0; i < count; i++) {
            if (resources[i].getId() == id) {
                resources[i].addLike();
                saveToFile();
                cout << "\nLiked successfully! Total likes: " << resources[i].getLikes() << "\n";
                return;
            }
        }
        cout << "\nResource ID not found.\n";
    }

    void showSubjectStatistics() const {
        if (count == 0) {
            cout << "\nNo resources available.\n";
            return;
        }
        cout << "\n===== SUBJECT STATISTICS =====\n";
        for (int i = 0; i < count; i++) {
            bool counted = false;
            for (int j = 0; j < i; j++) {
                if (resources[i].getSubject() == resources[j].getSubject()) {
                    counted = true;
                    break;
                }
            }
            if (!counted) {
                int total = 0;
                for (int j = 0; j < count; j++) {
                    if (resources[i].getSubject() == resources[j].getSubject()) total++;
                }
                cout << resources[i].getSubject() << " : " << total << " resources\n";
            }
        }
    }

    void openResourceFile() {
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

    void filterBySubject() const {
        string subject;
        cout << "\nEnter subject to filter: ";
        getline(cin, subject);
        transform(subject.begin(), subject.end(), subject.begin(), ::tolower);

        bool found = false;
        for (int i = 0; i < count; i++) {
            string s = resources[i].getSubject();
            transform(s.begin(), s.end(), s.begin(), ::tolower);
            if (s == subject) {
                resources[i].display();
                cout << "--------------------\n";
                found = true;
            }
        }
        if (!found) cout << "No resources found for this subject.\n";
    }

    void filterByType() const {
        int choice;
        cout << "\n1. Complete Notes\n2. Short Notes\n3. Important Questions\n4. Previous Year Questions\n5. Revision Notes\nChoose type: ";
        if (!(cin >> choice)) {
            cin.clear(); cin.ignore(10000, '\n');
            cout << "Invalid choice.\n";
            return;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        string types[] = {"", "Complete Notes", "Short Notes", "Important Questions", "Previous Year Questions", "Revision Notes"};
        if (choice < 1 || choice > 5) {
            cout << "Invalid type choice.\n";
            return;
        }

        bool found = false;
        for (int i = 0; i < count; i++) {
            if (resources[i].getType() == types[choice]) {
                resources[i].display();
                cout << "--------------------\n";
                found = true;
            }
        }
        if (!found) cout << "No resources found of this type.\n";
    }

    void sortByLikes() const {
        if (count == 0) {
            cout << "\nNo resources found.\n";
            return;
        }
        vector<Resource> temp(resources, resources + count);
        sort(temp.begin(), temp.end(), [](const Resource& a, const Resource& b) {
            return a.getLikes() > b.getLikes();
        });

        cout << "\nResources Sorted by Likes (Highest First):\n";
        for (const auto& res : temp) {
            res.display();
            cout << "--------------------\n";
        }
    }

    void saveToFile() const {
        ofstream file("resources.txt");
        if (!file) return;

        file << count << "\n";
        for (int i = 0; i < count; i++) {
            file << resources[i].getId() << "\n"
                 << quoted(resources[i].getTitle()) << "\n"
                 << quoted(resources[i].getSubject()) << "\n"
                 << quoted(resources[i].getDescription()) << "\n"
                 << quoted(resources[i].getType()) << "\n"
                 << quoted(resources[i].getFilePath()) << "\n"
                 << resources[i].getLikes() << "\n";
        }
        file.close();
    }

    void loadFromFile() {
        ifstream file("resources.txt");
        if (!file) return;

        int total;
        if (!(file >> total)) return;

        for (int i = 0; i < total; i++) {
            int id, likes;
            string title, subject, description, type, filePath;

            if (!(file >> id >> quoted(title) >> quoted(subject) >> quoted(description) >> quoted(type) >> quoted(filePath) >> likes))
                break;

            if (count == capacity) growArray();
            resources[count++] = Resource(id, title, subject, description, type, filePath, likes);
        }
        file.close();
    }

    int getCount() const { return count; }
    const Resource& getResource(int index) const { return resources[index]; }
};

// ==========================================
// 6. Resource Graph Class (BFS / DFS Traversal)
// ==========================================
class ResourceGraph {
private:
    vector<vector<int>> adj;

    void createGraph(const ResourceManager& manager) {
        int n = manager.getCount();
        adj.assign(n, vector<int>());
        vector<vector<int>> groups;

        for (int i = 0; i < n; i++) {
            string subj = manager.getResource(i).getSubject();
            transform(subj.begin(), subj.end(), subj.begin(), ::tolower);

            bool found = false;
            for (auto& group : groups) {
                string firstSubj = manager.getResource(group[0]).getSubject();
                transform(firstSubj.begin(), firstSubj.end(), firstSubj.begin(), ::tolower);
                if (subj == firstSubj) {
                    group.push_back(i);
                    found = true;
                    break;
                }
            }
            if (!found) groups.push_back({i});
        }

        // Build binary tree connections within each subject group
        for (const auto& group : groups) {
            for (size_t j = 1; j < group.size(); j++) {
                int parent = group[(j - 1) / 2];
                int child = group[j];
                adj[parent].push_back(child);
                adj[child].push_back(parent);
            }
        }
    }

    void displayAvailableList(const ResourceManager& manager) {
        cout << "\n===== AVAILABLE RESOURCES =====\n";
        for (int i = 0; i < manager.getCount(); i++) {
            cout << i << ". " << manager.getResource(i).getTitle() 
                 << " (" << manager.getResource(i).getSubject() << ")\n";
        }
    }

public:
    void BFS(const ResourceManager& manager) {
        int n = manager.getCount();
        if (n == 0) { cout << "\nNo resources available!\n"; return; }

        createGraph(manager);
        displayAvailableList(manager);

        int start;
        cout << "\nEnter starting resource number: ";
        cin >> start;

        if (start < 0 || start >= n) { cout << "Invalid number!\n"; return; }

        vector<bool> visited(n, false);
        queue<int> q;

        visited[start] = true;
        q.push(start);

        cout << "\nBFS Traversal: ";
        while (!q.empty()) {
            int curr = q.front(); q.pop();
            cout << manager.getResource(curr).getTitle() << " -> ";

            for (int neighbor : adj[curr]) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    q.push(neighbor);
                }
            }
        }
        cout << "NULL\n";
    }

    void DFS(const ResourceManager& manager) {
        int n = manager.getCount();
        if (n == 0) { cout << "\nNo resources available!\n"; return; }

        createGraph(manager);
        displayAvailableList(manager);

        int start;
        cout << "\nEnter starting resource number: ";
        cin >> start;

        if (start < 0 || start >= n) { cout << "Invalid number!\n"; return; }

        vector<bool> visited(n, false);
        stack<int> st;
        st.push(start);

        cout << "\nDFS Traversal: ";
        while (!st.empty()) {
            int curr = st.top(); st.pop();

            if (!visited[curr]) {
                visited[curr] = true;
                cout << manager.getResource(curr).getTitle() << " -> ";

                for (int i = (int)adj[curr].size() - 1; i >= 0; i--) {
                    int neighbor = adj[curr][i];
                    if (!visited[neighbor]) st.push(neighbor);
                }
            }
        }
        cout << "NULL\n";
    }
};

// ==========================================
// 7. Main Application Loop
// ==========================================
int main() {
    cout << "====================================\n"
         << " Welcome to Notes & Resource Sharing System\n"
         << "====================================\n";

    ResourceManager manager;
    Quiz quiz;
    ResourceGraph graph;
    ResourceReview reviewSystem;

    int choice = -1;

    while (choice != 0) {
        cout << "\n========== MAIN MENU ==========\n"
             << "1. Add Resource\n"
             << "2. Display All Resources\n"
             << "3. Search Resource\n"
             << "4. Edit Resource\n"
             << "5. Delete Resource\n"
             << "6. Like Resource\n"
             << "7. Subject Statistics\n"
             << "8. Open Resource File/Link\n"
             << "9. Filter by Subject\n"
             << "10. Filter by Resource Type\n"
             << "11. Sort Resources by Likes\n"
             << "12. Quiz System Menu\n"
             << "13. Graph BFS Traversal\n"
             << "14. Graph DFS Traversal\n"
             << "15. Add Resource Review\n"
             << "16. View Resource Reviews\n"
             << "0. Exit\n"
             << "\nEnter your choice: ";

        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "\nInvalid input. Please enter a number.\n";
            continue;
        }

        cin.ignore(10000, '\n');

        switch (choice) {
            case 1: manager.addResource(); break;
            case 2: manager.displayAll(); break;
            case 3: manager.searchResource(); break;
            case 4: manager.editResource(); break;
            case 5: manager.deleteResource(); break;
            case 6: manager.likeResource(); break;
            case 7: manager.showSubjectStatistics(); break;
            case 8: manager.openResourceFile(); break;
            case 9: manager.filterBySubject(); break;
            case 10: manager.filterByType(); break;
            case 11: manager.sortByLikes(); break;
            case 12: {
                int quizChoice;
                cout << "\n======= QUIZ SYSTEM =======\n"
                     << "1. Add Question\n"
                     << "2. Display Questions\n"
                     << "3. Start Quiz\n"
                     << "0. Back to Main Menu\n"
                     << "Enter choice: ";
                if (!(cin >> quizChoice)) {
                    cin.clear(); cin.ignore(10000, '\n');
                    break;
                }
                cin.ignore(10000, '\n');
                if (quizChoice == 1) quiz.addQuestion();
                else if (quizChoice == 2) quiz.displayQuestions();
                else if (quizChoice == 3) quiz.startQuiz();
                break;
            }
            case 13: graph.BFS(manager); break;
            case 14: graph.DFS(manager); break;
            case 15: reviewSystem.addReview(); break;
            case 16: reviewSystem.displayReviews(); break;
            case 0: cout << "\nThank you for using the system. Goodbye!\n"; break;
            default: cout << "\nInvalid choice. Please try again.\n";
        }
    }

    return 0;
}
