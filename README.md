Notes and Resources Sharing System

About the Project

This is a C++ console-based project that puts all your study resources at a one place. Title, subject, description, type, path, and likes are all features of each resource.

This project is build gradually. In the current stage we have introduced four important modules: Resource, User and Student, Resource Manager and main().

Features Implemented So Far

- Add at least one study resource, such as a book or a website.
- Display all available resources.
- Search resources.
- Like a resource.
- View subject-wise resource statistics.
- On your local PC, open a resource file.
- Export resource information to a text file.
- Restore resource information saved in the previous session at program startup.

Project Modules

# 1. Resource Module

This class store information about a study resource. It keeps resource id, title, subject, description, type, file path and number of likes. It can shows information of the resource, return the information and increment the number of likes.

# 2. User and Student Module

The User class stores the user's name, and has a virtual displayProfile() function. The Student class is derived from User and re-implements that function to display a student-specific welcome message.

These classes show inheritance and overriding of functions. They are defined in the current code but haven't been added to the main menu.

# 3. Resource Manager Module

Resource Manager class is responsible for managing the list of resources, it is made up of methods to: add a resource; display resources; search; show subject statistics; like; open resource; save and load data.

It use an array of the dynamic type to hold all resources. And when the array is full, it enlarges itself.

# 4. Main Module

A function main() will dispay the welcome message and menu, construct the resource manager, load the saved data, get choice from the user, invoking the corresponding function, and finally saving the resource info when asked for.

Tools and Techniques Utilized

- Language: C++
- Header files: iostream, fstream, iomanip, map, string, and cstdlib
- OOP concepts: Classes and objects, encapsulation, constructors, inheritance, virtual functions, and overriding
- Concepts included in DSA: Dynamic arrays, Dynamic Memory Allocation, Linear search & Maps
- File handling: Reading and writing resources' info file: resources.txt

How to Compile and Run

Required: a C++ compiler like g++.

If the project is composed of individual source files, open a terminal at the project folder and type:

``bash

G++ main.cpp User.cpp Resource.cpp Resource Manager.cpp -std=c++17 -o notes_app.exe

`

Execute in Windows Power Shell:

`powershell

.\notes_app.exe

``

Use this: n.n.lang: Replace n.n with the actual value. If you are putting everything in a single combined.cpp file, compile the file's real filename.

Present shortcomings and future enhancements

At this point, the program records the location of a local file and tries to open that file on your demand. You are not uploading the file. You are recording the filepath.

Suggest future development such as shared PDF uploads, recently used resources, bookmarks, enhancement of file validation and a server based system for students to share resources from different computers.

Team Responsibilities

- Shorya Barthwal: Resource module
- Rishav Negi: User and Student module
- Varun Kumar: Resource Manager module
- Sarthak Silswal: Main program and menu

This is the current implementation of the README file. Other features can be added to it as the project progresses.
