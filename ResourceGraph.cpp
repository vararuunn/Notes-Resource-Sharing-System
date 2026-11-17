
#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <string>
#include <algorithm>
#include <cctype>

using namespace std;

class ResourceGraph {
private:
    vector<vector<int>> adj;

    string toLower(string str) {
        transform(str.begin(), str.end(), str.begin(),
                  [](unsigned char c) {
                      return tolower(c);
                  });
        return str;
    }

    void createGraph(const ResourceManager& manager) {
        int n = manager.getCount();

        adj.clear();
        adj.resize(n);

        vector<vector<int>> groups;

        // Group resources by subject
        for (int i = 0; i < n; i++) {
            string subject = toLower(
                manager.getResource(i).getSubject()
            );

            bool found = false;

            for (int j = 0; j < groups.size(); j++) {
                string firstSubject = toLower(
                    manager.getResource(groups[j][0]).getSubject()
                );

                if (subject == firstSubject) {
                    groups[j].push_back(i);
                    found = true;
                    break;
                }
            }

            if (!found) {
                groups.push_back({i});
            }
        }

        // Create a binary-tree-like graph
        for (int i = 0; i < groups.size(); i++) {
            for (int j = 1; j < groups[i].size(); j++) {
                int parent = groups[i][(j - 1) / 2];
                int child = groups[i][j];

                adj[parent].push_back(child);
                adj[child].push_back(parent);
            }
        }
    }

    void displayResources(const ResourceManager& manager) {
    cout << "\n===== AVAILABLE RESOURCES =====\n";

    for (int i = 0; i < manager.getCount(); i++) {

        string subject = manager.getResource(i).getSubject();

        // Remove spaces from the beginning
        size_t start = subject.find_first_not_of(" \t");

        if (start == string::npos) {
            subject = "";
        } else {
            subject = subject.substr(start);
        }

        cout << i << ". "
             << manager.getResource(i).getTitle()
             << " (" << subject << ")" << endl;
    }
}

public:
    void BFS(const ResourceManager& manager) {
        int n = manager.getCount();

        if (n == 0) {
            cout << "\nNo resources available!\n";
            return;
        }

        createGraph(manager);
        displayResources(manager);

        int start;
        cout << "\nEnter starting resource number: ";
        cin >> start;

        if (start < 0 || start >= n) {
            cout << "Invalid resource number!\n";
            return;
        }

        vector<bool> visited(n, false);
        queue<int> q;

        visited[start] = true;
        q.push(start);

        cout << "\nBFS Traversal: ";

        while (!q.empty()) {
            int current = q.front();
            q.pop();

            cout << manager.getResource(current).getTitle() << " -> ";

            for (int neighbour : adj[current]) {
                if (!visited[neighbour]) {
                    visited[neighbour] = true;
                    q.push(neighbour);
                }
            }
        }

        cout << "NULL\n";
    }

    void DFS(const ResourceManager& manager) {
        int n = manager.getCount();

        if (n == 0) {
            cout << "\nNo resources available!\n";
            return;
        }

        createGraph(manager);
        displayResources(manager);

        int start;
        cout << "\nEnter starting resource number: ";
        cin >> start;

        if (start < 0 || start >= n) {
            cout << "Invalid resource number!\n";
            return;
        }

        vector<bool> visited(n, false);
        stack<int> st;

        st.push(start);

        cout << "\nDFS Traversal: ";

        while (!st.empty()) {
            int current = st.top();
            st.pop();

            if (!visited[current]) {
                visited[current] = true;

                cout << manager.getResource(current).getTitle()
                     << " -> ";

                for (int i = adj[current].size() - 1; i >= 0; i--) {
                    int neighbour = adj[current][i];

                    if (!visited[neighbour]) {
                        st.push(neighbour);
                    }
                }
            }
        }

        cout << "NULL\n";
    }
};
