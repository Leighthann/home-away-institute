//Authors: Leigh-Ann Cross, Diamond Buchanan, Winroy Jennings
#ifndef STUDENT_H_
#define STUDENT_H_


#include "Course.h"

class Student : public User
{
private:
    static int sequence;
    int enrolmentStatus;
    int dateEnrolled;
    int semester;
    

public:
    string programmeCode;
    string courseCode;

    Student()
    {
        this->enrolmentStatus = 0;
        this->dateEnrolled = 0;
        this->fName = "";
        this->lName = "";
        this->userID = "";
        this->password = "";
        this->faculty = "";
        this->address = "";
        this->contactNumber = " ";
        this->programmeCode = "";
        this->courseCode = "";
        this->semester = 0;
    }

    Student(int enrolmentStatus, int dateEnrolled, string idNumber, string firstName, string lastName, string username, string password, string faculty, string address, int contactNumber, string programmeCode, string courseCode, int semester) // TODO Initial User here
    {
        this->enrolmentStatus = enrolmentStatus;
        this->dateEnrolled = dateEnrolled;
        this->fName = firstName;
        this->lName = lastName;
        this->userID = username;
        this->password = password;
        this->faculty = faculty;
        this->address = address;
        this->contactNumber = contactNumber;
        this->programmeCode = programmeCode;
        this->courseCode = courseCode;
        this->semester = semester;
    }

    Student(const Student &student) // TODO Initial User here
    {
        this->enrolmentStatus = student.enrolmentStatus;
        this->dateEnrolled = student.dateEnrolled;
        this->fName = student.fName;
        this->lName = student.lName;
        this->userID = student.userID;
        this->password = student.password;
        this->faculty = student.faculty;
        this->address = student.address;
        this->contactNumber = student.contactNumber;
        this->programmeCode = student.programmeCode;
        this->courseCode = student.courseCode;
        this->semester = student.semester;
    }

    string getCourseCode()
    {
        return courseCode;
    }

    void setCourseCode(string courseCode)
    {
        this->courseCode = courseCode;
    }

    int getEnrolmentStatus()
    {
        return this->enrolmentStatus;
    }

    void setEnrolmentStatus(int enrolmentStatus)
    {
        this->enrolmentStatus = enrolmentStatus;
    }

    int getDateEnrolled()
    {
        return this->dateEnrolled;
    }

    void setDateEnrolled(int dateEnrolled)
    {
        this->dateEnrolled = dateEnrolled;
    }

    string getProgrammeCode()
    {
        return this->programmeCode;
    }

    void setProgrammeCode(string programmeCode)
    {
        this->programmeCode = programmeCode;
    }

    int getSemester()
    {
        return semester;
    }

    void setSemester(int semester)
    {
        this->semester = semester;
    }

    

    void getCourseProgrammeDetails()
    {
        string line, progCode;
        size_t pos;

        string programmeCode, programmeName, award, accreditation;
      
        cout << "Enter programme code to search for courses: ";
        cin >> progCode;
        try
        {
            ifstream *readcourseFile = new ifstream("course-db.txt", ios::in);
            if (readcourseFile->fail())
            {
                throw runtime_error("In file stream could not be created ");
            }

            if (readcourseFile->is_open())
            {
                while (!readcourseFile->eof())
                {
                    getline(*readcourseFile, line); //getline from file
                    pos = line.find(progCode);
                    if (pos != string::npos)
                    {
                       
                        cout << line << '\n';
                        cout << "\nProgramme found" << endl;
                        return;
                    }
                }
            }
            readcourseFile->close();
            Student::login();

            cout << "Courses not found" << endl;
        }
        catch (runtime_error *re)
        {
            cerr << re->what();
        }
    }

    void addCourseToEnrollment()
    {
        Student student;
        string cCode, again;
        string cName;
        string cDescription;
        string cPrerequisite;
        string progCodes;
        string progCode;
        string line;
        size_t pos;
        string IdNumber, stuFile, coFile, firstName, lastName;
        int semester;
        int status = 1;

        try
        {
            ifstream *courseFile = new ifstream("course-db.txt", ios::in | ios::out);
            ofstream *tempstudentFile = new ofstream("temp-student-db.txt", ios::out | ios::app);
            if (courseFile->fail())
            {
                throw runtime_error("Files could not be opened ");
            }
            cout << "What semester is this " << endl;
            cin >> semester;
            cout << "Enter your programme code " << endl;
            cin >> progCodes;

            if (courseFile->is_open())
            {
                while (!courseFile->eof())
                {
                    getline(*courseFile, coFile);
                    pos = coFile.find(progCodes);
                    if (pos != string::npos)
                    {
                        cout << coFile << '\n';
                    }
                }
            }
            courseFile->close();

            if (tempstudentFile->fail())
            {
                throw runtime_error("File could not be opened ");
            }

            cout << "Enter your id Number " << endl;
            cin >> IdNumber;

            cout << "\nEnter Course Code: Comma-separated lists are allowed" << endl;
            cin.ignore();
            getline(cin, cCode);
            student.setSemester(semester);
            student.setUserID(IdNumber);
            student.setCourseCode(cCode);
            student.setEnrolmentStatus(status);
           

            *tempstudentFile << student.getSemester() << "\t"
                             << student.getUserID() << "\t"
                             << student.getCourseCode() << "\t"
                             << student.getEnrolmentStatus() << endl;

            tempstudentFile->close();

            system("cls");

            Student::login();
        }
        catch (runtime_error *re)
        {
            cerr << re->what();
        }
    }

    void generateProgressReport()
    {

        string tempidnum, tempsemester, tempcoursecode;
        string cCode, progCode, cPrerequisite, cDescription, cName, tempstuFile;
        int cCredits;
        float cPrice;
        string idnumber;
        size_t pos;

        try
        {
            ifstream *courseFile = new ifstream("course-db.txt", ios::in);
            ifstream *tempstudentFile = new ifstream("temp-student-db.txt", ios::in);
            if (courseFile->fail() || tempstudentFile->fail())
            {
                throw runtime_error("Files could not be accessed ");
            }

            string idnum = "";
            cout << "Enter idNumber:";
            cin >> idnum;

            *tempstudentFile >> tempsemester >> tempidnum >> tempcoursecode;

            if (idnum != tempidnum)
            {
                cout << "Re-enter idNumber:";
                cin >> idnum;
            }

            while (!tempstudentFile->eof())
            {

                getline(*tempstudentFile, tempstuFile);
                pos = tempstuFile.find(idnum);
                if (pos != string::npos)
                {
                    cout << tempstuFile << '\n';
                }
            }
        }
        catch (runtime_error *re)
        {
            cerr << re->what();
        }
    }

    void generateFeeBreakdownForSemester()
    {
        string tempidnum, tempsemester, tempcoursecode;
        size_t pos, posforSem, posforCourse;
        int total_cost = 0;
        int cPrice;

        Course cCourse;
        string cName;
        string progCode;
        int sequence;
        Student student;
        string cCode;
        string cDescription;
        int cCredits = 0;
        string cPrerequisite;
        string tempstuFile;
        string coFile;
        string semester;
        string studentCourse[5];

        try
        {
            ifstream *courseFile = new ifstream("course-db.txt", ios::in);
            ifstream *tempstudentFile = new ifstream("temp-student-db.txt", ios::in);

            if (courseFile->fail() && (tempstudentFile->fail()))
            {
                throw runtime_error("Files could not be accessed ");
            }

            string idnum = "";
            cout << "Enter idNumber:";
            cin >> idnum;

            cout << "Enter your semester: ";
            cin >> semester;

            int i = 0;

            while (!tempstudentFile->eof())
            {
                *tempstudentFile >> tempsemester >> tempidnum >> tempcoursecode;

                if (semester == tempsemester && idnum == tempidnum)
                {
                    studentCourse[i++] += tempcoursecode;
                }
            }

            if (courseFile->is_open())
            {
                while (!courseFile->eof())
                {
                    *courseFile >> progCode >> courseCode >> cName >> cDescription >> cCredits >> cPrerequisite >> cPrice;

                    if (courseCode == "?")
                    {
                        break;
                    }

                    for (int i = 0; i < studentCourse->length(); i++)
                    {

                        if (courseCode == studentCourse[i])
                        {
                            cout << progCode << "\t" << courseCode << "\t" << cName << "\t" << cDescription << "\t" << cCredits << "\t" << cPrerequisite << "\t"
                                 << "$" << cPrice << endl;

                            total_cost += cPrice * cCredits;
                        }
                    }

                    courseCode = "?";
                }

                cout << "Student Total Cost: $" << total_cost << endl;
            }
        }
        catch (runtime_error *re)
        {
            cerr << re->what();
        }
    }

    void login()
    {

        int optionSelection;
        int optionSelection2;

        cout << "Student Menu Console" << endl
             << endl;

        cout << "Select one of the following option." << endl;
        cout << "1 - Enrollement for Semester" << endl;
        cout << "2 - Generate Progress Report" << endl;
        cout << endl
             << "Selection: ";

        // Validate input type
        while (!(cin >> optionSelection))
        {
            cout << "Invalid entry, try again!" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); //holds console from reiterating: ignores new line

            cout << "Selection: ";
        }

        switch (optionSelection)
        {
        case 1:
           
            cout << "1 - Select your courses " << endl;
            cout << "2 - View Programme Details" << endl;
            cout << "3 - Generate Fee Breakdown for semester" << endl;

            cout << endl
                 << "You have Selected: ";

            while (!(cin >> optionSelection2))
            {
                cout << "Invalid entry, try again!" << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); //holds console from reiterating: ignores new line
                cout << "Selection: ";
            }

            switch (optionSelection2)
            {

            case 1:
                cout << "Select your courses: ";
                addCourseToEnrollment();

                break;
            case 2:
                cout << "View Programme Details :";
                getCourseProgrammeDetails();
                break;

            case 3:
                cout << "Generate Fee Breakdown: \n";
                generateFeeBreakdownForSemester();
                break;
            }
            break;

        case 2:

            cout << "Progress Report:\n"
                 << endl;
            generateProgressReport();
            break;
        }
    }
};

#endif /* STUDENT_H_ */
