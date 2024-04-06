// Authors: Leigh-Ann Cross, Diamond Buchanan, Winroy Jennings
#include <string.h>

#ifndef STAFF_H_
#define STAFF_H_

#include "Student.h"
#include "Programme.h"
#include "Course.h"

class Staff : public User
{
protected:
    string department;
    Date dateEmployed;
    string contactNumber;

public:
    static int sequence;

    // Destructor
    ~Staff()
    {
    }

    // Default Conctructor-
    Staff()
    {
        this->contactNumber = "";
        this->faculty = "";
        this->department = "";
        this->dateEmployed = Date();
    }

    // Primary constructor
    Staff(string userID, string fName, string lName, string password, string position, string faculty, string address, string contactNumber, string department, int day, int month, int year)
    {
        this->userID = userID;
        this->fName = fName;
        this->lName = lName;
        this->password = password;
        this->position = position;
        this->faculty = faculty;
        this->address = address;
        this->department = department;
        this->contactNumber = contactNumber;
        this->dateEmployed = Date(day, month, year);
    }

    // Copy constructor
    Staff(const Staff &staff)
    {
        this->userID = staff.userID;
        this->fName = staff.fName;
        this->lName = staff.lName;
        this->password = staff.password;
        this->position = staff.position;
        this->faculty = staff.faculty;
        this->address = staff.address;
        this->department = staff.department;
        this->contactNumber = staff.contactNumber;
        this->dateEmployed = staff.dateEmployed;
    }

    // Accessor Methods
    string getContactNumber()
    {
        return contactNumber;
    }

    string getDepartment()
    {
        return department;
    }

    Date getDateEmployed()
    {
        return dateEmployed;
    }

    // Mutator Methods
    void setContactNumber(string contactNumber)
    {
        this->contactNumber = contactNumber;
    }

    void setDepartment(string department)
    {
        this->department = department;
    }

    void setDateEmployed(Date dateEmployed)
    {
        this->dateEmployed = dateEmployed;
    }

    // Saves All Programs Entered to the file
    void saveProgram(Programme program)
    {
        try // this entire block of code is executed provided that no error is detected
        {
            ofstream *writeprogrammeFile = new ofstream("programme-db.txt", ios::out | ios::app); // opens the file in writing mode
            if (writeprogrammeFile->fail())                                                       // if the program file is open.......
            {
                throw runtime_error("Program file could not be created "); // error message if the file fails to open
            }
            // If the program file open , save each record to the file
            *writeprogrammeFile
                << program.getProgrammeCode() << "\t" // '\t' endures that each record is saved with horizontally space in your output
                << program.getProgrammeName() << "\t"
                << program.getMaxNumOfCourses() << "\t"
                << program.getAward() << "\t"
                << program.getAccreditation() << endl;

            writeprogrammeFile->close();                                  // Closes the program file
            cout << "The Programme has succesfully been logged " << endl; // output message
            cout << "Press enter to return to login " << endl;
            getch();
            Staff::login(); //
        }
        catch (runtime_error *re) // catches all exception of type runtime
        {
            cerr << re->what(); //
        }
    }

    // Generates student lists based on the programme code
    void generateStudentListForProgramme()
    {
        string proCode = " ";
        string file; // temporary buffer for the studentFile stream
        size_t pos;

        try // this entire block of code is executed provided that no exception is detected
        {
            ifstream *readstudentFile = new ifstream("student-db.txt", ios::in); // opens the file in reading mode
            if (readstudentFile->fail())                                         // if the student file is open.......
            {
                throw runtime_error("Student file could not be accessed "); // error message if the file fails to open
            }
            cout << "Enter the programme code to see the students who are enrolled: "; // asks the user to enter the desired programme code
            cin >> proCode;

            if (readstudentFile->is_open()) // if the sudentFile is open
            {
                while (readstudentFile->good()) // if the readStudentFile stream has not raised any errors
                {
                    getline(*readstudentFile, file); // reads the entire file stream into the string file

                    pos = file.find(proCode); // finds the proCode entered and returns 0

                    if (pos != string::npos) // string::npos default value is -1. If find returns 0 then
                    {
                        cout << file << '\n'; // the content of the file is printed
                    }
                }

                cout << "Press enter to continue to system login " << endl;
                getch(); // waits for character input from the user to proceed with the program
            }

            cout << "There are no students currently enrolled in this programme " << endl;

            readstudentFile->close(); // Closes the student file
            Staff::login();
        }
        catch (runtime_error *re) // catches all exception of type runtime
        {
            cerr << re->what();
        }
    }

    // Saves the students entered to the file
    void saveStudent(Student student)
    {
        try
        {
            ofstream *writestudentFile = new ofstream("student-db.txt", ios::out | ios::app); // opens the file in writing mode
            if (writestudentFile->fail())                                                     // if the student file is open.......
            {
                throw runtime_error("Student file could not be created "); // error message if the file fails to open
            }
            // If the student file open , save each record to the file
            *writestudentFile
                << student.getFName() << "\t"
                << student.getLName() << "\t"
                << student.getPassword() << "\t"
                << student.getUserID() << "\t"
                << student.getAddress() << "\t"
                << student.getProgrammeCode() << "\t"
                << student.getContactNumber() << "\t"
                << student.getFaculty() << "\t"
                << student.getDateEnrolled() << "\t"
                << student.getEnrolmentStatus() << endl;

            writestudentFile->close(); // Closes the program file
            cout << "\n Student has been successfully created\n"
                 << endl;
            cout << "Press enter to return to login " << endl;
            getch();
            Staff::login();
        }
        catch (runtime_error *re) // catches all exception of type runtime
        {
            cerr << re->what();
        }
    }

    void removeCourse(string poCode, string coCode) // removing Course
    {
        string pcode;
        string cCode;
        string cName;
        string cDescription;
        int cCredits;
        string cPrerequisite;
        float cPrice;
        try
        {

            ifstream *courseFile = new ifstream("course-db.txt", ios::in);
            ofstream *tempcourseFile = new ofstream("temp-course-db.txt", ios::out | ios::app); // For adding records

            if (courseFile->fail() && tempcourseFile->fail())
            {
                throw runtime_error("Error accessing database!");
            }

            while (!courseFile->eof())
            {
                *courseFile >> pcode >> cCode >> cName >> cDescription >> cCredits >> cPrerequisite >> cPrice;

                if (pcode == "?" || cCode == "?")
                {
                    break;
                }

                if ((poCode == pcode && coCode != cCode) || (poCode != pcode))
                {
                    *tempcourseFile << pcode << "\t"
                                    << cCode << "\t"
                                    << cName << "\t"
                                    << cDescription << "\t"
                                    << cCredits << "\t"
                                    << cPrerequisite << "\t"
                                    << cPrice << "\t" << endl;
                }

                cCode = "?";
                pcode = "?";
            }

            courseFile->close();
            tempcourseFile->close();

            // Remove file
            if (remove("course-db.txt") != 0)
                cerr << "Error removing file" << endl;
            if (rename("temp-course-db.txt", "course-db.txt") != 0)
                cerr << "Error renaming file" << endl;

            cout << endl
                 << "The file has now been updated" << endl;

            system("cls");

            Staff::login();
        }
        catch (runtime_error *re)
        {
            cerr << re->what();
        }
    }

    void displayCourse() // Displaying Course details
    {
        string pcode;
        string cCode;
        string cName;
        string cDescription;
        int cCredits;
        string cPrerequisite;
        float cPrice;

        string cId;

        cout << "Enter course ID: ";
        cin >> cId;

        try
        {
            ifstream *courseFile = new ifstream("course-db.txt", ios::in);

            if (courseFile->fail())
            {
                throw runtime_error("Error accessing database!");
            }

            while (!courseFile->eof())
            {
                *courseFile >> pcode >> cCode >> cName >> cDescription >> cCredits >> cPrerequisite >> cPrice;

                if (cId == cCode)
                {
                    cout << pcode << "\t"
                         << cCode << "\t"
                         << cName << "\t"
                         << cDescription << "\t"
                         << cCredits << "\t"
                         << cPrerequisite << "\t"
                         << cPrice << "\t" << endl;

                    break;
                }
            }

            courseFile->close();
            cout << "Press enter to continue...";
            getch();
            Staff::login();
        }
        catch (runtime_error *re)
        {
            cerr << re->what();
        }
    }

    void getProgrammeDetails() // display programme details
    {
        string line, proCode;
        size_t pos;

        string programmeCode, programmeName, award, accreditation, maxNumOfCourses;

        cout << "Enter programme code to search: ";
        cin >> proCode;

        try
        {
            ifstream *readprogrammeFile = new ifstream("programme-db.txt", ios::in);
            if (readprogrammeFile->fail())
            {
                throw runtime_error("In file stream could not be created ");
            }

            while (!readprogrammeFile->eof())
            {
                *readprogrammeFile >> programmeCode >> programmeName >> maxNumOfCourses >> award >> accreditation;

                if (proCode == programmeCode)
                {

                    cout << "Programmecode: "
                         << "\t" << programmeCode << "ProgrammeName: "
                         << "\t" << programmeName << "MaxNumOfCourses: "
                         << "\t" << maxNumOfCourses << "Award: "
                         << "\t" << award << " Accreditation: "
                         << "\t" << accreditation;
                }
            }

            readprogrammeFile->close();
            cout << "Press enter to continue...";
            getch();
            Staff::login();
        }
        catch (runtime_error *re)
        {
            cerr << re->what();
        }
        Staff::login();
    }

    string Extract() // Extract first three chars from programme code
    {
        string pcode;

        cout << "Enter the students programme code" << endl;
        cin >> pcode; // @suppress("Invalid arguments")
        string partialString = "";

        for (int i = 0; i < 3; i++)
        {
            partialString += pcode[i];
        }

        return partialString;
    }

    string getEnrollmentYear() // Displays Enrollment year of student
    {
        time_t t = time(NULL);
        tm *tPtr = localtime(&t);

        int dates;

        dates = tPtr->tm_year + 1900;
        return to_string(dates);
    }

    int getDateEnrolled()
    {
        time_t t = time(NULL);
        tm *tPtr = localtime(&t);

        int dates;

        int day;
        int month;
        int year;

        day = (tPtr->tm_mday);
        month = ((tPtr->tm_mon) + 1);
        year = ((tPtr->tm_year) + 1900);
        return day, month, year;
    }

    void registerStudent() // register student
    {
        char again = 'N';
        Student student;

        string date;
        string extract;
        string idNumber;
        string firstName;
        string lastName;
        string password;
        int enrolldate;
        string address;
        string programmeCode;
        string contactNumber;
        string faculty;
        int enrollmentStatus = 0;

        cout << "Enter student first name: ";
        cin >> firstName;

        cout << "Enter student last name: ";
        cin >> lastName;

        cout << "Enter student password: ";
        cin >> password;

        enrolldate = getDateEnrolled();

        cout << "Enroll date : " << enrolldate << endl;
        cin.ignore();

        cout << "Enter the students address: ";
        cin.ignore();
        cin >> address;

        cout << "Enter student programme code: ";
        cin >> programmeCode;

        cout << "Enter the student's contact number: ";
        cin >> contactNumber;

        cout << "Enter the student's faculty: ";
        cin.ignore();
        getline(cin, faculty);

        cout << "Enrollment Status: " << enrollmentStatus << endl; // sequence++;

        // idNumber = getEnrollmentYear() + Extract() + s;
        idNumber = getEnrollmentYear() + Extract() + to_string(sequence);
        cout << "This is the " << sequence << "student to be entered" << endl;
        getch();
        sequence++;

        cout << "Id Number is " << idNumber;
        student.setUserID(idNumber);
        student.setFName(firstName);
        student.setLName(lastName);
        student.setPassword(password);
        student.setAddress(address);
        student.setProgrammeCode(programmeCode);
        student.setContactNumber(contactNumber);
        student.setFaculty(faculty);
        student.setDateEnrolled(enrolldate);
        student.setEnrolmentStatus(enrollmentStatus);

        saveStudent(student);
    }

    void generateStudentsList()
    {
        string programmeCode;
        string stuFile;
        try
        {
            // Opening a file to perform read operations using file object
            ifstream *studentFile = new ifstream("student-db.txt", ios::in);
            if (studentFile->fail()) //
            {
                throw runtime_error("In file stream could not be generated ");
            }
            if (studentFile->is_open())
            {
                while (studentFile->good())
                {
                    getline(*studentFile, stuFile);
                    cout << stuFile << endl;
                }
                cout << "Press enter to continue";
                getch();
            }
            // closes the file object
            studentFile->close();
            Staff::login();
        }
        catch (runtime_error *re)
        {
            cerr << re->what();
        }
    }

    void saveCourse(Programme program, Course course)
    {
        try
        {
            ofstream *courseFile = new ofstream("course-db.txt", ios::out | ios::app);
            if (courseFile->fail())
            {
                throw runtime_error("Course file could not be created ");
            }
            *courseFile
                << program.getProgrammeCode() << "\t"
                << course.getCourseCode() << "\t"
                << course.getName() << "\t"
                << course.getDescription() << "\t"
                << course.getCredits() << "\t"
                << course.getPrerequiste() << "\t"
                << course.getCoursePrice() << endl;
            courseFile->close();
            cout << "Your Course has been succesfully entered " << endl;

            system("cls");

            Staff::login();
        }
        catch (runtime_error *re)
        {
            cerr << re->what();
        }
    }

    void createProgramme()
    {
        char again = 'N';
        do
        {
            Programme program;

            string programmeCode;
            string programmeName;
            int maximumNumberOfCourses;
            string award;
            string accreditations;
            string progCode;

            cout << "\nHello" << endl;

            cout << "Enter the programme code:";
            cin >> programmeCode;

            cout << "What is the program name: ";
            // cin.ignore();
            // getline(cin, programmeName);
            cin >> programmeName;

            cout << "What are the maximum number of course: ";
            cin >> maximumNumberOfCourses;

            cout << "What are the available Awards for this course: ";
            // cin.ignore();
            // getline(cin, award);
            cin >> award;

            cout << "What are available accreditation: ";
            cin >> accreditations;

            program.setProgrammeCode(programmeCode);
            program.setProgrammeName(programmeName);
            program.setMaxNumOfCourses(maximumNumberOfCourses);
            program.setAward(award);
            program.setAccreditation(accreditations);

            do
            {
                cout << "Do you want to enter another. Y for yes and N for no: ";
                cin >> again;

                if (toupper(again) != 'Y' && toupper(again) != 'N')
                {
                    cout << "Invalid entry, try again!" << endl;
                }
                else
                {
                    break;
                }
                // allows the function to repeat if a valid entry has not been entered
            } while (toupper(again) != 'Y' && toupper(again) != 'N');

            // Saves the different programs records to the Programme database
            saveProgram(program);

        } while (again != toupper('N'));
    }

    void modifyProgramme() 
    {
        Programme program;
        string programmeCode;
        string programmeName;
        int maximumNumberOfCourses;
        string award;
        string accreditations;
        char response = ' ';
        string code = "";

        string programmeCode2;
        string programmeName2;
        int maximumNumberOfCourses2;
        string award2;
        string accreditations2;

        string programmeCode3;
        string programmeName3;
        int maximumNumberOfCourses3;
        string award3;
        string accreditations3;

        try
        {
            ifstream *readprogrammeFile = new ifstream("programme-db.txt", ios::in);
            ofstream *tempProgrammeDatabase = new ofstream("temp-programme-db.txt", ios::out | ios::app);

            if (readprogrammeFile->fail() && tempProgrammeDatabase->fail())
            {
                throw runtime_error("Program file could not be accessed ");
            }

            cout << "Enter the programme code of the data to be modified: ";
            cin >> code;

            cout << "What is the updated program code: ";
            cin >> programmeCode2;

            cout << "What is the updated program name: ";
            cin >> programmeName2;

            cout << "What are the updated maximum number of course: ";
            cin >> maximumNumberOfCourses2;

            cout << "What are the available Awards for this course: ";
            cin >> award2;

            cout << "What are the available Accreditations: ";
            cin >> accreditations2;

            // and while file has no errors have been detected
            while (!readprogrammeFile->eof())
            {
                *readprogrammeFile >> programmeCode >> programmeName >> maximumNumberOfCourses >> award >> accreditations;

                cout << "code::" << code << endl;
                cout << "programmeCode::" << programmeCode << endl;

                // If exist in database then...
                if (programmeCode != code)
                {
                    if (programmeCode == "?")
                    {
                        break;
                    }

                    *tempProgrammeDatabase << programmeCode << "\t" << programmeName << "\t" << maximumNumberOfCourses << "\t" << award << "\t" << accreditations << endl;
                }

                programmeCode = "?";
            }

            *tempProgrammeDatabase << programmeCode2 << "\t"
                                   << programmeName2 << "\t"
                                   << maximumNumberOfCourses2 << "\t"
                                   << award2 << "\t"
                                   << accreditations2 << endl;

            tempProgrammeDatabase->close();
            readprogrammeFile->close();

            // Remove file
            if (remove("programme-db.txt") != 0)
                cerr << "Error removing file";

            // Rename file
            if (rename("temp-programme-db.txt", "programme-db.txt") != 0)
                cerr << "Error renaming file" << endl;

            // clears the input buffer
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout << "Press ENTER to continue...";
            cin.get();

            Staff::login();
        }
        catch (runtime_error *re)
        {
            cerr << re->what();
        }
    }

    void deleteProgramme(string pcode)
    {
        int maximumNumberOfCourses;
        string programmeCode;
        string programmeName;

        string award;
        string accreditations;

        try
        {

            ifstream *programmeFile = new ifstream("programme-db.txt", ios::in);
            ofstream *tempprogrammeFile = new ofstream("temp-programme-db.txt", ios::out);

            if (programmeFile->fail() || tempprogrammeFile->fail())
            {
                throw runtime_error("Error accessing database!");
            }

            while (!programmeFile->eof())
            {
                *programmeFile >> programmeCode >> programmeName >> maximumNumberOfCourses >> award >> accreditations;

                cout << pcode << endl
                     << programmeCode << endl;

                if (pcode != programmeCode)
                {
                    *tempprogrammeFile << programmeCode << "\t"
                                       << programmeName << "\t"
                                       << maximumNumberOfCourses << "\t"
                                       << award << "\t"
                                       << accreditations << endl;
                }

                programmeCode = "?";

                if (programmeCode == "?")
                {

                    break;
                }
            }

            programmeFile->close();
            tempprogrammeFile->close();

            // Remove file
            if (remove("programme-db.txt") != 0)
                cerr << "Error removing file";

            if (rename("temp-programme-db.txt", "programme-db.txt") != 0)
                cerr << "Error renaming file";

            cout << endl
                 << "The file has now been updated" << endl;

            system("cls");

            // Staff::login();
        }
        catch (runtime_error *re)
        {
            cerr << re->what();
        }
    }

    void addProgrammeCourse()
    {
        Course course;
        Programme program;
        string cCode;
        string cName;
        string cDescription;
        int cCredits;
        string cPrerequisite;
        float cPrice;
        string progCode;

        cout << "Under which programme does this course belong: ";
        cin >> progCode;

        cout << "Enter Course Code:";
        cin >> cCode;

        cout << "Enter Course Name: ";
        cin.ignore();
        cin >> cName;

        cout << "Enter Course Description:";
        cin.ignore();
        cin >> cDescription;

        cout << "Enter Course Credits: ";

        // Validate input type
        while (!(cin >> cCredits))
        {
            cout << "Invalid entry, try again!" << endl;
            cin.clear();
            // cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout << "Enter Course Credits: " << endl;
        }

        cout << "Enter the course Prerequisite:";
        cin.ignore();
        cin >> cPrerequisite;

        cin.clear();
        cout << "Enter the price of the course: $";
        cin >> cPrice;

        program.setProgrammeCode(progCode);
        course.setCourseCode(cCode);
        course.setName(cName);
        course.setDescription(cDescription);
        course.setCredits(cCredits);
        course.setPrerequisite(cPrerequisite);
        course.setCoursePrice(cPrice);

        saveCourse(program, course);
        // saveCourse(course);
    }

    void login()
    {

        int optionSelection, optionSelection2;
        string coCode, pcode, poCode;

        system("cls"); // Clears the console
        system("Color 01");
        cout << "Staff Menu Console" << endl;
        cout << "1 - Programme Administration " << endl;
        cout << "2 - Register Student" << endl;
        cout << "3 - Return to Main main " << endl;

        cout << endl
             << "You have selected: ";
        // Validate input type
        while (!(cin >> optionSelection))
        {
            cout << "Invalid entry, try again!" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout << "Selection: ";
        }

        switch (optionSelection)
        {
            system("Color 7B");
        case 1:
            // system("cls");
            cout << "1 - Create Programme" << endl;
            cout << "2 - Display Programme Details" << endl;
            cout << "3 - Modify Program" << endl;
            cout << "4 - Delete Program" << endl;
            cout << "5 - Generate Student's List based on Program" << endl;
            cout << "6 - Add Course" << endl;
            cout << "7 - Display Course Information" << endl;
            cout << "8 - Remove course " << endl;
            cout << "9 - View all students " << endl;
            cout << endl
                 << "You have selected: ";

            // Validate input type
            while (!(cin >> optionSelection2))
            {
                cout << "Invalid entry, try again!" << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                cout << "Selection: ";
            }

            cout << endl;

            switch (optionSelection2)
            {
            case 1:
                system("cls");
                cout << "Create a programme : \n"
                     << endl;
                createProgramme();
                break;
            case 2:
                cout << "Display Programme Details :"
                     << endl;
                getProgrammeDetails();
                break;
            case 3:
                cout << "Program Modification:" << endl;
                modifyProgramme();
                break;
            case 4:
                cout << "Enter the programme code of the programme to be deleted:";
                cin >> pcode;
                deleteProgramme(pcode);
                break;

            case 5:
                cout << "Generate a Student's List for a Particular Programme: "
                     << endl;
                generateStudentListForProgramme();
                break;

            case 6:
                cout << "Add Course " << endl;
                addProgrammeCourse();
                break;

            case 7:
                cout << "Display course information: " << endl;
                displayCourse();
                break;

            case 8:
                cout << "Delete a course: " << endl;
                cout << "Enter the programme code of the course to be removed:  ";
                cin >> poCode;
                cout << "Enter the course code of the course to be removed:  ";
                cin >> coCode;
                removeCourse(poCode, coCode);
                break;

            case 9:
                cout << "View All Students:" << endl;
                generateStudentsList();
                break;
            }

            break;

        case 2:
            system("cls");
            cout << "Register student : " << endl;
            registerStudent();
            break;
        case 3:
            cout << "Back to Main Menu : " << endl;
            mainMenu();
            break;
        }
    };
};

int Staff::sequence = 0;
#endif /* STAFF_H_ */