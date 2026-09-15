#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include "User.h"
#include "DynamicArray.h"

class FileManager {
public:
    static void saveUsers(User users[], int count);
    static int loadUsers(User users[], int maxUsers);

    static void saveNotes(const DynamicArray& notes);
    static void loadNotes(DynamicArray& notes);

    static bool uploadFile(const char source[], const char destination[]);
};

#endif
