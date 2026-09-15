NOTES AND RESOURCE SHARING SYSTEM - FINAL SIMPLE VERSION

This version is designed for a college PBL project. The code is kept simple
and uses separate .h and .cpp files so each part is easy to explain.

FEATURES
1. Study Dashboard
2. View Profile
3. Add Resource
4. Search Resources
5. View Resource
6. Like Resource
7. Exam Mode
8. Smart Resource Recommendations
9. Subject Statistics
10. Save Data
11. Logout

EXAM MODE
- Important Questions
- Previous Year Question Papers
- Revision Notes
- Short Notes

FILE UPLOAD
When adding a resource, enter the path of your own file. The program copies
the file into uploaded_notes/ and saves that path with the resource.
Example:
C:\Users\hp\Downloads\DSA_PYQ_2025.pdf

SMART RECOMMENDATIONS
The user enters a subject. The program recommends resources from that subject.
This is a simple rule-based recommendation system, so it is easy to understand.

STL MAP
The project uses map<string, int> subjectCount.
The key is the subject and the value is the number of resources in that subject.
This is used for Subject Statistics.

DSA / OOP
- Dynamic Array stores resources.
- STL map stores subject statistics.
- Classes and objects are used throughout the project.
- Encapsulation, inheritance, polymorphism and constructors are demonstrated.
- File handling is used for users, resources and uploaded files.

NOT USED
- No Binary Search Tree
- No vector
- No STL stack
- No STL queue
- No priority_queue

COMPILE IN VS CODE
g++ *.cpp -std=c++17 -o notes_system

RUN
.\notes_system.exe

DEMO LOGIN
Username: demo
Password: 1234
