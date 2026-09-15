#include "Note.h"
#include <iostream>
#include <cstring>
using namespace std;

static void copyText(char destination[], const char source[], int size) {
    strncpy(destination, source, size - 1);
    destination[size - 1] = '\0';
}

Note::Note() : id(0), ownerId(0), likes(0), views(0) {
    title[0] = subject[0] = description[0] = type[0] = filePath[0] = '\0';
}

Note::Note(int i, int o, const char t[], const char s[], const char d[],
           const char ty[], const char f[], int l, int v)
    : id(i), ownerId(o), likes(l), views(v) {
    copyText(title, t, 100);
    copyText(subject, s, 50);
    copyText(description, d, 200);
    copyText(type, ty, 40);
    copyText(filePath, f, 200);
}

int Note::getId() const { return id; }
int Note::getOwnerId() const { return ownerId; }
const char* Note::getTitle() const { return title; }
const char* Note::getSubject() const { return subject; }
const char* Note::getDescription() const { return description; }
const char* Note::getType() const { return type; }
const char* Note::getFilePath() const { return filePath; }
int Note::getLikes() const { return likes; }
int Note::getViews() const { return views; }

void Note::like() { likes++; }
void Note::addView() { views++; }
void Note::setFilePath(const char path[]) { copyText(filePath, path, 200); }

void Note::display() const {
    cout << "\n-----------------------------\n";
    cout << "Resource ID : " << id << "\n";
    cout << "Title       : " << title << "\n";
    cout << "Subject     : " << subject << "\n";
    cout << "Type        : " << type << "\n";
    cout << "Description : " << description << "\n";
    cout << "Likes       : " << likes << "\n";
    cout << "Views       : " << views << "\n";
    cout << "File        : " << (filePath[0] ? filePath : "No file attached") << "\n";
    cout << "-----------------------------\n";
}
