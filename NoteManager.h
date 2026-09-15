#ifndef NOTE_MANAGER_H
#define NOTE_MANAGER_H

#include "DynamicArray.h"
#include <map>
#include <string>

class NoteManager {
private:
    DynamicArray notes;
    int nextId;
    std::map<std::string, int> subjectCount;

    int findNote(int id) const;
    bool contains(const char text[], const char key[]) const;
    bool sameText(const char a[], const char b[]) const;

public:
    NoteManager();
    DynamicArray& getNotes();

    void addResource(int userId);
    void searchResources() const;
    void viewResource(int id);
    void likeResource(int id);
    void examMode() const;
    void dashboard(int userId) const;
    void recommendations() const;
    void showSubjectStatistics() const;
};

#endif
