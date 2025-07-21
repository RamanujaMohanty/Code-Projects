#include <iostream>
using namespace std;
class Student
{
public:
    Student() {}
    explicit Student(char favMuni) : favMuni(favMuni) {};
    Student(string name, char favMuni, string favColor = "Purple")
            : name(name), favMuni(favMuni), favColor(favColor) {}
    static string getSchoolName()
    {
        return Student::schoolName;
    }
    string getName() const
    {
        return (*this).name;
    }
    char getFavMuni() const
    {
        return this->favMuni;
    }
}
