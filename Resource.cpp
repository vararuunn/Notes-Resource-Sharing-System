#include <iostream>
#include <string>
using namespace std;

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

    Resource();

    Resource(int resourceId, string resourceTitle, string resourceSubject,
             string resourceDescription, string resourceType,
             string resourceFilePath, int likeCount = 0);

    int getId() const;
    string getTitle() const;
    string getSubject() const;
    string getDescription() const;
    string getType() const;
    string getFilePath() const;
    int getLikes() const;

    void addLike();

    void display() const;
};

Resource::Resource() {
    id = 0;
    likes = 0;
}

Resource::Resource(int resourceId, string resourceTitle, string resourceSubject,
                   string resourceDescription, string resourceType,
                   string resourceFilePath, int likeCount) {
    id = resourceId;
    title = resourceTitle;
    subject = resourceSubject;
    description = resourceDescription;
    type = resourceType;
    filePath = resourceFilePath;
    likes = likeCount;
}

int Resource::getId() const {
    return id;
}

string Resource::getTitle() const {
    return title;
}

string Resource::getSubject() const {
    return subject;
}

string Resource::getDescription() const {
    return description;
}

string Resource::getType() const {
    return type;
}

string Resource::getFilePath() const {
    return filePath;
}

int Resource::getLikes() const {
    return likes;
}

void Resource::addLike() {
    likes++;
}

void Resource::display() const {
    cout << "\nID: " << id;
    cout << "\nTitle: " << title;
    cout << "\nSubject: " << subject;
    cout << "\nType: " << type;
    cout << "\nDescription: " << description;
    cout << "\nFile path: ";

    if (filePath == "") {
        cout << "Not provided";
    } else {
        cout << filePath;
    }

    cout << "\nLikes: " << likes << "\n";
}
