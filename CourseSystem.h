#ifndef COURSESYSTEM_H
#define COURSESYSTEM_H

#include <vector>
#include <string>
#include "Course.h"

class CourseEnrollmentSystem {
private:
    std::vector<Course> courses;
    void quickSort(int left, int right);     // Programmer
    int binarySearch(std::string code);      // Programmer
    int sentinelSearch(std::string code);    // Programmer

public:
    void addCourse();        // Programmer
    void displayCourses();   // Programmer
    void sortCourses();      // Programmer
    void searchCourse();     // Programmer
    void countCourses();     // Programmer
    void deleteCourse();     // Programmer
    void saveToFile();       // File saving
    void loadFromFile();     // File loading
    void menu();             // Programmer: All
};

#endif