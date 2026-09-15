#include "DynamicArray.h"

DynamicArray::DynamicArray() {
    count = 0;
    capacity = 10;
    notes = new Note[capacity];
}

DynamicArray::~DynamicArray() {
    delete[] notes;
}

void DynamicArray::resize() {
    capacity = capacity * 2;
    Note* newNotes = new Note[capacity];

    for (int i = 0; i < count; i++)
        newNotes[i] = notes[i];

    delete[] notes;
    notes = newNotes;
}

void DynamicArray::add(const Note& note) {
    if (count == capacity)
        resize();

    notes[count] = note;
    count++;
}

int DynamicArray::size() const {
    return count;
}

Note* DynamicArray::get(int index) {
    if (index < 0 || index >= count)
        return nullptr;
    return &notes[index];
}

const Note* DynamicArray::get(int index) const {
    if (index < 0 || index >= count)
        return nullptr;
    return &notes[index];
}
