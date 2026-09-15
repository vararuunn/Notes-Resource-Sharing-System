#ifndef NOTE_H
#define NOTE_H

class Note {
private:
    int id;
    int ownerId;
    char title[100];
    char subject[50];
    char description[200];
    char type[40];
    char filePath[200];
    int likes;
    int views;

public:
    Note();
    Note(int id, int ownerId, const char title[], const char subject[],
         const char description[], const char type[], const char filePath[],
         int likes = 0, int views = 0);

    int getId() const;
    int getOwnerId() const;
    const char* getTitle() const;
    const char* getSubject() const;
    const char* getDescription() const;
    const char* getType() const;
    const char* getFilePath() const;
    int getLikes() const;
    int getViews() const;

    void like();
    void addView();
    void setFilePath(const char path[]);
    void display() const;
};

#endif
