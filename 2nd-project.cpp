#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Student {
private:
    string name;
    int rollNo;
    bool isPresent;

public:
    Student() {
        name = "";
        rollNo = 0;
        isPresent = true;
    }

    void setDetails(string n, int r) {
        name = n;
        rollNo = r;
    }

    string getName() { return name; }
    int getRollNo() { return rollNo; } 
    bool getAttendance() { return isPresent; }
    void setAttendance(bool status) { isPresent = status; }
};

class Batch {
private:
    string batchId;
    Student students[100];  // Array to store maximum 100 students
    int studentCount;

public:
    Batch() {
        batchId = "";
        studentCount = 0;
    }

    void createBatch(string id) {
        batchId = id;
    }

    string getBatchId() { return batchId; }

    bool addStudent(string name, int rollNo) {
        if (studentCount < 100) {
            students[studentCount].setDetails(name, rollNo);
            studentCount++;
            return true;
        }
        return false;
    }

    void displayStudents() {
        cout << "\nStudents in Batch " << batchId << ":\n";
        for (int i = 0; i < studentCount; i++) {
            cout << "Roll No: " << students[i].getRollNo() 
                 << ", Name: " << students[i].getName() << endl;
        }
    }

    void markAttendance(int absentRollNos[], int absentCount) {
        // First mark all as present
        for (int i = 0; i < studentCount; i++) {
            students[i].setAttendance(true);
        }

        // Mark absent students
        for (int i = 0; i < absentCount; i++) {
            for (int j = 0; j < studentCount; j++) {
                if (students[j].getRollNo() == absentRollNos[i]) {
                    students[j].setAttendance(false);
                    break;
                }
            }
        }
    }

    void saveAttendance(string date) {
        string filename = batchId + "_" + date + ".txt";
        ofstream file(filename);

        if (file.is_open()) {
            file << "Attendance for Batch: " << batchId << endl;
            file << "Date: " << date << endl;
            file << "\nRoll No\tName\tStatus\n";

            for (int i = 0; i < studentCount; i++) {
                file << students[i].getRollNo() << "\t"
                     << students[i].getName() << "\t"
                     << (students[i].getAttendance() ? "Present" : "Absent") << endl;
            }
            file.close();
            cout << "Attendance saved to " << filename << endl;
        }
    }

    int getStudentCount() { return studentCount; }
};

class AttendanceSystem {
private:
    Batch batches[10];  // Maximum 10 batches
    int batchCount;

public:
    AttendanceSystem() {
        batchCount = 0;
    }

    void addBatch(string batchId) {
        if (batchCount < 10) {
            batches[batchCount].createBatch(batchId);
            batchCount++;
            cout << "Batch created successfully!\n";
        } else {
            cout << "Maximum batch limit reached!\n";
        }
    }

    void displayBatches() {
        cout << "\nAll Batches:\n";
        for (int i = 0; i < batchCount; i++) {
            cout << batches[i].getBatchId() << endl;
        }
    }

    Batch* getBatch(string batchId) {
        for (int i = 0; i < batchCount; i++) {
            if (batches[i].getBatchId() == batchId) {
                return &batches[i];
            }
        }
        return nullptr;
    }
};

int main() {
    AttendanceSystem system;
    int choice;

    do {
        cout << "\n=== Attendance Management System ===\n";
        cout << "1. Create New Batch\n";
        cout << "2. Display All Batches\n";
        cout << "3. Add Student to Batch\n";
        cout << "4. Display Students in Batch\n";
        cout << "5. Mark Attendance\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                string batchId;
                cout << "Enter Batch ID: ";
                cin >> batchId;
                system.addBatch(batchId);
                break;
            }
            case 2: {
                system.displayBatches();
                break;
            }
            case 3: {
                string batchId, name;
                int rollNo;
                cout << "Enter Batch ID: ";
                cin >> batchId;
                Batch* batch = system.getBatch(batchId);
                if (batch) {
                    cout << "Enter Student Name: ";
                    cin >> name;
                    cout << "Enter Roll Number: ";
                    cin >> rollNo;
                    batch->addStudent(name, rollNo);
                    cout << "Student added successfully!\n";
                } else {
                    cout << "Batch not found!\n";
                }
                break;
            }
            case 4: {
                string batchId;
                cout << "Enter Batch ID: ";
                cin >> batchId;
                Batch* batch = system.getBatch(batchId);
                if (batch) {
                    batch->displayStudents();
                } else {
                    cout << "Batch not found!\n";
                }
                break;
            }
            case 5: {
                string batchId, date;
                cout << "Enter Batch ID: ";
                cin >> batchId;
                Batch* batch = system.getBatch(batchId);
                if (batch) {
                    cout << "Enter Date (DD-MM-YYYY): ";
                    cin >> date;
                    
                    int absentCount;
                    cout << "Enter number of absent students: ";
                    cin >> absentCount;
                    
                    int absentRollNos[100];
                    cout << "Enter roll numbers of absent students:\n";
                    for (int i = 0; i < absentCount; i++) {
                        cin >> absentRollNos[i];
                    }
                    
                    batch->markAttendance(absentRollNos, absentCount);
                    batch->saveAttendance(date);
                } else {
                    cout << "Batch not found!\n";
                }
                break;
            }
            case 6:
                cout << "Thank you for using the system!\n";
                break;
            default:
                cout << "Invalid choice!\n";
        }
    } while (choice != 6);

return 0;
}