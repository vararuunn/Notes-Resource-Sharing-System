#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

#include "Note.h"

class DynamicArray {
private:
    Note* notes;
    int count;
    int capacity;
    void resize();

public:
    DynamicArray();
    ~DynamicArray();

    void add(const Note& note);
    int size() const;
    Note* get(int index);
    const Note* get(int index) const;
};

#endif
