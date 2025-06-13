#include<iostream>
#include<string>
#include<cctype>
#include<limits>  // For numeric_limits
using namespace std;

class Student {
private:
    string name;
    int age;
    string gender;
    int roll_no;
    int semester;
    int totalquestion;
    int correctans;

public:
    // Constructor to initialize the student data
    Student() {
        name = "";
        age = 0;
        gender = "";
        roll_no = 0;
        semester = 0;
        totalquestion = 10;
        correctans = 0;
    }

    // Method to validate the student's name (ensure no special characters or numbers)
    bool isValidName(const string& name) {
        for (char ch : name) {
            if (!isalpha(ch) && ch != ' ') {  // Allow only letters and spaces
                return false;
            }
        }
        return true;
    }

    // Method to input student information
    void inputStudentInfo() {
        bool validName = false;
        while (!validName) {
            cout << "Enter student name: ";
            cin >> name;

            // Validate the name
            if (isValidName(name)) {
                validName = true;
            } else {
                cout << "Invalid name! Please enter a valid name (letters and spaces only).\n";
            }
        }

        // Input the age carefully if it is invalid then try again.
        do {
            cout << "Enter age: ";
            cin >> age;
            if (age > 0 && age < 100) {
                break;
            } else {
                cout << "Invalid input! Please enter an age between 1 and 99.\n";
            }
        } while (age <= 0 || age >= 100);

        // Input gender
        do {
            cout << "Enter gender (male/female): ";
            cin >> gender;
            if (gender == "male" || gender == "female") {
                break;
            } else {
                cout << "Invalid input! Please enter 'male' or 'female'.\n";
            }
        } while (gender != "male" && gender != "female");

        // Input roll number
        do {
            cout << "Enter roll number: ";
            cin >> roll_no;
            if (roll_no > 0 && roll_no <= 9999) {
                break;
            } else {
                cout << "Invalid input! Please enter a positive roll number (1-9999).\n";
            }
        } while (roll_no <= 0 || roll_no > 9999);
        
        // Input semester
        do {
            cout << "Enter semester (1-8): ";
            cin >> semester;

            // Check if the input is an integer and in the correct range
            if (cin.fail()) {
                cin.clear();  // Clear the fail state
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore invalid input
                cout << "Invalid input! Please enter a number between 1 and 8.\n";
            } else if (semester >= 1 && semester <= 8) {
                break;
            } else {
                cout << "Invalid input! Please enter a semester between 1 and 8.\n";
            }
        } while (semester < 1 || semester > 8);
    }

    // Method to take the test
    void takeTest() {
        char answer;

        string questions[10] = {
            "1. ( 2x-10 ) find value of x?\n a) 4 \n b) 5 \n c) 6 \n d) 0",
            "2. What is the unit of force?\n a) meter\n b) Newton\n c) length\n d) not",
            "3. What is the atomic number of Carbon?\n a) 4\n b) 1\n c) 12\n d) 6",
            "4. Which of the following languages is understandable for computers?\n a) high-level language\n b) low-level language\n c) moderate-level language\n d) all of those",
            "5. Where is Burj Khalifa located?\n a) Paris\n b) America\n c) Dubai\n d) Pakistan",
            "6. What is the unit of heat ?\n a) Calorie \n b) Joule \n c) kelvin \n d) both a and b",
            "7. Symbol of gold is\n a) pb \n b) Au \n c) o \n d) N",
            "8. Formula of Water is\n a) CH4 \n b) N2O \n c) H2O \n d) not",
            "9. SI unit of time is\n a) meter \n b) second \n c) newton \n d) all of those",
            "10. He ____ to university daily\n a) went \n b) going \n c) goes \n d) not"
        };

        char correctAnswers[10] = {'a', 'b', 'd', 'b', 'c', 'd', 'b', 'c', 'b', 'c'};

        // Loop through each question
        for (int i = 0; i < totalquestion; ++i) {
            cout << questions[i] << endl;
            cout << "Choose (a/b/c/d): ";
            cin >> answer;
            if (tolower(answer) == tolower(correctAnswers[i])) {  // Case-insensitive comparison
                correctans++;
            }
        }
    }

    // Method to display the result and student information
    void displayResult() const {
        float percentage = (float(correctans) / totalquestion) * 100;

        cout << "\nTest completed!" << endl;
        cout << "Student Name: " << name << endl;
        cout << "Age: " << age << endl;
        cout << "Gender: " << gender << endl;
        cout << "Roll Number: " << roll_no << endl;
        cout << "Semester: " << semester << endl;
        cout << "Correct Answers: " << correctans << "/" << totalquestion << endl;
        cout << "Percentage: " << percentage << "%" << endl;
    }
};

int main() {
    Student student;
    char continuetest = 'y';

    while (continuetest == 'y' || continuetest == 'Y') {
        student.inputStudentInfo();  // Input student information
        student.takeTest();          // Take the test
        student.displayResult();     // Display results

        cout << "Do you want to continue? [y/n]: ";
        cin >> continuetest;
    }

    cout << "\nThanks for contributing!" << endl;

    return 0;
}
