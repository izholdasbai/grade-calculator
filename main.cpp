// Grade Calculator: average score and grade for each student
#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

const int SCORE_COUNT = 5;   // every student has exactly 5 scores
const int MIN_SCORE = 0;
const int MAX_SCORE = 100;

// Return the grade letter for an average score
char getGrade(double average) {
    if (average >= 90) {
        return 'A';
    } else if (average >= 75) {
        return 'B';
    } else if (average >= 60) {
        return 'C';
    }
    return 'F';
}

// Ask for one score until the user enters a whole number from 0 to 100
// Returns false only if the input stream is closed (end of input)
bool readScore(int scoreNumber, int &score) {
    while (true) {
        cout << "Score " << scoreNumber << ": ";
        cin >> score;

        if (cin.fail()) {
            // Letters or symbols were typed: clear the error and skip the line
            if (cin.eof()) {
                return false;
            }
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid score. Enter a value from 0 to 100." << endl;
        } else if (score < MIN_SCORE || score > MAX_SCORE) {
            cin.ignore(1000, '\n');
            cout << "Invalid score. Enter a value from 0 to 100." << endl;
        } else {
            cin.ignore(1000, '\n');
            return true;
        }
    }
}

int main() {
    string name;
    int studentCount = 0;
    double averageSum = 0.0;

    // Main loop: one pass per student, stops when the teacher types "end"
    while (true) {
        cout << "Student name (or end to finish): ";
        getline(cin, name);

        if (!cin || name == "end") {
            break;
        }
        if (name.empty()) {
            continue;
        }

        // Read and add up the 5 scores
        int total = 0;
        bool inputOk = true;
        for (int i = 1; i <= SCORE_COUNT; i++) {
            int score;
            if (!readScore(i, score)) {
                inputOk = false;
                break;
            }
            total += score;
        }
        if (!inputOk) {
            break;
        }

        // Average and grade
        double average = (double)total / SCORE_COUNT;
        cout << name << ": average " << fixed << setprecision(1) << average
             << ", grade " << getGrade(average) << endl;
        cout << endl;

        studentCount++;
        averageSum += average;
    }

    // Final summary
    if (studentCount == 0) {
        cout << "No students entered" << endl;
    } else {
        cout << "Students entered: " << studentCount << endl;
        cout << "Class average: " << fixed << setprecision(1)
             << averageSum / studentCount << endl;
    }
    return 0;
}
