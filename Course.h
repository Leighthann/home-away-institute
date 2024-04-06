//Authors: Diamond Buchanan
#ifndef COURSE_H_
#define COURSE_H_

class Course
{
private:
    string courseCode;
    string name;
    string description;
    int credits;
    string prerequisite;
    float price;
    string proCode;

public:
    Course() // Default Constructor
    {
        courseCode = "";
        name = "";
        description = "";
        credits = 0;
        prerequisite = "";
        price = 0.0;
        proCode = " ";
    }

    Course(string courseCode, string name, string description, int credits, string prerequisite, float price, string proCode) // Primary Constructor
    {
        this->courseCode = courseCode;
        this->name = name;
        this->description = description;
        this->credits = credits;
        this->prerequisite = prerequisite;
        this->price = price;
        this->proCode = proCode;
    }

    Course(const Course &course) // Copy Constructor
    {
        this->courseCode = course.courseCode;
        this->name = course.name;
        this->description = course.description;
        this->credits = course.credits;
        this->prerequisite = course.prerequisite;
        this->price = course.price;
        this->proCode = course.proCode;
    }

//Mutators
    string getCourseCode()
    {

        return courseCode;
    }

    void setCourseCode(string courseCode)
    {
        this->courseCode = courseCode;
    }

    string getName()
    {
        return name;
    }

    void setName(string name)
    {
        this->name = name;
    }

    string getDescription()
    {
        return description;
    }

    void setDescription(string description)
    {
        this->description = description;
    }

    int getCredits()
    {
        return credits;
    }

    void setCredits(int credits)
    {
        this->credits = credits;
    }

    string getPrerequiste()
    {
        return prerequisite;
    }

    void setPrerequisite(string prerequisite)
    {
        this->prerequisite = prerequisite;
    }

    float getCoursePrice()
    {
        return price;
    }

    void setCoursePrice(float price)
    {
        this->price = price;
    }

    string getProCode()
    {
        return proCode;
    }

    void setProCode(string proCode)
    {
        this->proCode = proCode;
    }
};

#endif /* COURSE_H_ */
