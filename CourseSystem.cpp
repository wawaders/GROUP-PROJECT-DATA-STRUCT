#include "CourseSystem.h"
#include <iostream>
#include <fstream>

using namespace std;

// Programmer: 
void CourseEnrollmentSystem::quickSort(int left, int right) {
    int i = left, j = right;
    string pivot = courses[(left + right) / 2].courseCode;

    while (i <= j) {
        while (courses[i].courseCode < pivot) i++;
        while (courses[j].courseCode > pivot) j--;
        if (i <= j) {
            swap(courses[i], courses[j]);
            i++;
            j--;
        }
    }

    if (left < j) quickSort(left, j);
    if (i < right) quickSort(i, right);
}

// Programmer: 
int CourseEnrollmentSystem::binarySearch(string code) {
    int left = 0, right = courses.size() - 1;
    while (left <= right) {
        int mid = (left + right) / 2;
        if (courses[mid].courseCode == code) return mid;
        if (courses[mid].courseCode < code) left = mid + 1;
        else right = mid - 1;
    }
    return -1;
}

// Programmer: 
int CourseEnrollmentSystem::sentinelSearch(string code) {
    int n = courses.size();
    courses.push_back(Course(code, "")); // sentinel
    int i = 0;

    while (courses[i].courseCode != code) i++;

    courses.pop_back(); // remove sentinel

    if (i < n) return i;
    else return -1;
}

// Programmer: 
void CourseEnrollmentSystem::addCourse() {
    string code, name;
    cout << "Enter course code: ";
    cin >> code;
    cin.ignore();
    cout << "Enter course name: ";
    getline(cin, name);
    courses.push_back(Course(code, name));
    cout << "Course added.\n";
}

// Programmer: 
void CourseEnrollmentSystem::displayCourses() {
    if (courses.empty()) {
        cout << "No courses to display.\n";
        return;
    }

    cout << "\nCourse List:\n";
    for (const auto& course : courses) {
        cout << course.courseCode << " - " << course.courseName << endl;
    }
}

// Programmer: 
void CourseEnrollmentSystem::sortCourses() {
    if (courses.empty()) {
        cout << "No courses to sort.\n";
        return;
    }
    quickSort(0, courses.size() - 1);
    cout << "Courses sorted by course code.\n";
}

// Programmer: 
void CourseEnrollmentSystem::searchCourse() {
    if (courses.empty()) {
        cout << "No courses to search.\n";
        return;
    }

    int choice;
    string code;
    cout << "Search using:\n1. Binary Search\n2. Sentinel Search\nEnter choice: ";
    cin >> choice;
    cout << "Enter course code to search: ";
    cin >> code;

    int index = -1;
    if (choice == 1) {
        sortCourses(); // required before binary search
        index = binarySearch(code);
    }
    else if (choice == 2) {
        index = sentinelSearch(code);
    }

    if (index != -1) {
        cout << "Course found: " << courses[index].courseCode << " - " << courses[index].courseName << endl;
    }
    else {
        cout << "Course not found.\n";
    }
}

// Programmer: 
void CourseEnrollmentSystem::countCourses() {
    cout << "Total courses enrolled: " << courses.size() << endl;
}

// Programmer: 
void CourseEnrollmentSystem::deleteCourse() {
    if (courses.empty()) {
        cout << "No courses to delete.\n";
        return;
    }

    string code;
    cout << "Enter course code to delete: ";
    cin >> code;

    bool found = false;
    for (auto it = courses.begin(); it != courses.end(); ++it) {
        if (it->courseCode == code) {
            courses.erase(it);
            cout << "Course " << code << " deleted.\n";
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "Course not found.\n";
    }
}

// File Saving
void CourseEnrollmentSystem::saveToFile() {
    ofstream outFile("courses.txt");
    if (!outFile) {
        cout << "Error saving file.\n";
        return;
    }

    for (const auto& course : courses) {
        outFile << course.courseCode << "," << course.courseName << endl;
    }

    outFile.close();
    cout << "Courses saved to courses.txt\n";
}

// File Loading
void CourseEnrollmentSystem::loadFromFile() {
    ifstream inFile("courses.txt");
    if (!inFile) {
        return;
    }

    string line;
    while (getline(inFile, line)) {
        size_t commaPos = line.find(',');
        if (commaPos != string::npos) {
            string code = line.substr(0, commaPos);
            string name = line.substr(commaPos + 1);
            courses.push_back(Course(code, name));
        }
    }

    inFile.close();
    cout << "Courses loaded from courses.txt\n";
}

// Programmer: All
void CourseEnrollmentSystem::menu() {
    loadFromFile();

    int choice;
    do {
        cout << "\n==== Course Enrollment System Menu ====\n";
        cout << "1. Add Course\n";
        cout << "2. Display Courses\n";
        cout << "3. Sort Courses (Quick Sort)\n";
        cout << "4. Search Course (Binary/Sentinel)\n";
        cout << "5. Count Total Courses\n";
        cout << "6. Exit\n";
        cout << "7. Delete Course\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1: addCourse(); break;
        case 2: displayCourses(); break;
        case 3: sortCourses(); break;
        case 4: searchCourse(); break;
        case 5: countCourses(); break;
        case 6:
            saveToFile();
            cout << "Exiting...\n";
            break;
        case 7: deleteCourse(); break;
        default:
            cout << "Invalid choice!\n";
            break;
        }
    } while (choice != 6);
}