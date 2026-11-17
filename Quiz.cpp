
#include <iostream>
#include <fstream>
#include <string>
#include <limits>
using namespace std;

class Quiz {
public:

    // Add a new question
    void addQuestion() {
        ofstream file("questions.txt", ios::app);

        string question, a, b, c, d;
        char answer;

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "\nEnter question: ";
        getline(cin, question);

        cout << "Option A: ";
        getline(cin, a);

        cout << "Option B: ";
        getline(cin, b);

        cout << "Option C: ";
        getline(cin, c);

        cout << "Option D: ";
        getline(cin, d);

        cout << "Correct answer (A/B/C/D): ";
        cin >> answer;

        answer = toupper(answer);

        if (answer < 'A' || answer > 'D') {
            cout << "Invalid answer. Question not saved.\n";
            return;
        }

        file << question << "\n";
        file << a << "\n";
        file << b << "\n";
        file << c << "\n";
        file << d << "\n";
        file << answer << "\n";

        file.close();

        cout << "\nQuestion added successfully!\n";
    }


    // Display all questions
    void displayQuestions() {
        ifstream file("questions.txt");

        string question, a, b, c, d;
        char answer;
        int count = 0;

        while (getline(file, question)) {
            if (!getline(file, a) ||
                !getline(file, b) ||
                !getline(file, c) ||
                !getline(file, d) ||
                !(file >> answer)) {
                break;
            }

            file.ignore(numeric_limits<streamsize>::max(), '\n');

            count++;

            cout << "\nQ" << count << ". " << question;
            cout << "\nA. " << a;
            cout << "\nB. " << b;
            cout << "\nC. " << c;
            cout << "\nD. " << d << "\n";
        }

        if (count == 0) {
            cout << "\nNo questions available.\n";
        }
    }


    // Start quiz
    void startQuiz() {
        ifstream file("questions.txt");

        string question, a, b, c, d;
        char correct, userAnswer;
        int score = 0, total = 0;

        while (getline(file, question)) {
            if (!getline(file, a) ||
                !getline(file, b) ||
                !getline(file, c) ||
                !getline(file, d) ||
                !(file >> correct)) {
                break;
            }

            file.ignore(numeric_limits<streamsize>::max(), '\n');

            total++;

            cout << "\nQ" << total << ". " << question;
            cout << "\nA. " << a;
            cout << "\nB. " << b;
            cout << "\nC. " << c;
            cout << "\nD. " << d;

            cout << "\nYour answer: ";
            cin >> userAnswer;

            userAnswer = toupper(userAnswer);

            if (userAnswer == correct) {
                cout << "Correct!\n";
                score++;
            } else {
                cout << "Wrong! Correct answer: " << correct << "\n";
            }
        }

        if (total == 0) {
            cout << "\nNo questions available. Add questions first.\n";
            return;
        }

        cout << "\n===== QUIZ RESULT =====\n";
        cout << "Total Questions: " << total << "\n";
        cout << "Correct Answers: " << score << "\n";
        cout << "Wrong Answers: " << total - score << "\n";
        cout << "Final Score: " << score << "/" << total << "\n";
    }
};
