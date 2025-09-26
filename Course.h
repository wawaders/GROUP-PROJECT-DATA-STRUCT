#ifndef COURSE_H
#define COURSE_H

#include <string>
using namespace std;

class Course {
public:
    string courseCode;
    string courseName;

    Course();
    Course(string code, string name);
};

#endif


