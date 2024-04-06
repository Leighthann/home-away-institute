/*
  Authors:
    Leigh-Ann Cross 2100463
    Diamond Buchanan 2102369
    Winroy Jennings 2106397

Program Name: Home & Away Institute Management System
Program description:The Chairman of the H&AI has requested that a program be created to automate the
student admission and programme administration processes.
Creation date: September 26, 2022
*/

#include <cctype>    // used for std namespace
#include <ctime>     // Time method
#include <limits>    // Use for the numeric_limits<streamsize> in cin.ignore
#include <string>    // String method
#include <fstream>   // File method
#include <stdexcept> // Exception method
#include <iostream>  // Input & Output method
#include <cstdio>    // The cstdio header file contains definitions for C++ for performing input and output
#include <sstream>   // Use for the numeric_limits<streamsize> in cin.ignore
#include <conio.h>   // getch method
#include <ctime>     // Used to get time

using namespace std;

const string staffDatabase = "staff-db.txt";          // filenames and variables
const string tempStaffDatabase = "temp-staff-db.txt"; // temporary filenames and variables

const string adminDatabase = "admin-db.txt";          // filenames and variables
const string tempAdminDatabase = "temp-admin-db.txt"; // temporary filenames and variables

const string studentDatabase = "student-db.txt";          // filenames and variables
const string tempStudentDatabase = "temp-student-db.txt"; // temporary filenames and variables

const string courseDatabase = "course-db.txt";          // filenames and variables
const string tempCourseDatabase = "temp-course-db.txt"; // temporary filenames and variables

const string programmeDatabase = "programme-db.txt";          // filenames and variables
const string tempProgrammeDatabase = "temp-programme-db.txt"; // temporary filenames and variables

void firstRun();
void mainMenu();
void menuSelection();
void prompt(int);

// .H classes
#include "Date.h"
#include "User.h"
#include "Staff.h"
#include "Administration.h"
#include "Programme.h"
#include "Course.h"
#include "Student.h"

string userType = "";

int main()
{
    firstRun();
    return 0;
}

void firstRun()
{
    try
    {
        ifstream *readStaffFile = new ifstream(adminDatabase, ios::in);

        if (!readStaffFile->is_open())
        {
            ofstream *writeStaffFile = new ofstream(adminDatabase, ios::out);

            // Creates a default admin entry
            *writeStaffFile << "admin"
                            << "\t"
                            << "admin"
                            << "\t"
                            << "admin"
                            << "\t"
                            << "admin"
                            << "\t"
                            << "admin"
                            << "\t"
                            << "admin"
                            << "\t"
                            << "admin"
                            << "\t"
                            << "admin"
                            << "\t"
                            << "admin" << endl;

            writeStaffFile->close();
        }
        else
        {
            if (readStaffFile->fail())
            {
                throw runtime_error("Error accessing database!");
            }

            readStaffFile->close();
        }
    }
    catch (const runtime_error &re)
    {
        cerr << re.what() << '\n';
    }

    mainMenu();
}

void incorrectPassword(char again, int menuSelection)
{
    do
    {
        cout << "Would you like to try again?\n"
             << endl
             << endl;

        cout << "Enter (Y) to try again or (N) to return to Main Menu or (E) "
                "to exit."
             << endl;
        cout << "Selection: ";
        cin >> again;

        if (toupper(again) != 'Y' && toupper(again) != 'N' &&
            toupper(again) != 'E')
        {
            cout << "\nInvalid entry, try again!" << endl;
        }
        else if (toupper(again) == 'Y')
        {
            cout << "\n";
            prompt(menuSelection);
            break;
        }
        else if (toupper(again) == 'N')
        {
            mainMenu();
            break;
        }
        else if (toupper(again) == 'E')
        {
            exit(1); // Exits the console
        }
    } while (toupper(again) != 'Y' && toupper(again) != 'N' &&
             toupper(again) != 'E');
}

int validateUserCredential(string userID, string userPassword, int menuSelection)
{
    int result;
    char again = 'Y';

    // Validation
    do
    {
        try
        {
            ifstream *readStaffFile;

            switch (menuSelection)
            {
            case 1:
                readStaffFile = new ifstream(adminDatabase, ios::in);
                break;
            case 2:
                readStaffFile = new ifstream(staffDatabase, ios::in);
                break;
            case 3:
                readStaffFile = new ifstream(studentDatabase, ios::in);
                break;
            }

            if (readStaffFile->fail())
            {
                throw runtime_error("Error accessing database!");
            }

            if (readStaffFile->is_open())
            {
                string id, firstName, lastName, password, position;

                while (!readStaffFile->eof())
                {
                    switch (menuSelection)
                    {
                    case 1:
                    case 2:
                        *readStaffFile >> id >> firstName >> lastName >> password >> position;
                        break;
                    case 3:
                        *readStaffFile >> firstName >> lastName >> password >> id;
                        break;
                    }

                    if (id == userID)
                    {
                        if (password == userPassword)
                        {
                            if (menuSelection == 1)
                            {
                                Administration *admin = new Administration();
                                admin->login();
                                break;
                            }
                            else if (menuSelection == 2)
                            {
                                Staff *staff = new Staff();
                                staff->login();
                                break;
                            }
                            else if (menuSelection == 3)
                            {
                                Student *student = new Student();
                                student->login();
                                break;
                            }
                        }
                        else
                        {
                            cout << "Wrong password!" << endl;
                            incorrectPassword(again, menuSelection);
                        }
                    }
                    else
                    {
                        cout << "UserName does not exist in the database!" << endl;
                        incorrectPassword(again, menuSelection);
                    }

                    // Reset
                    id = "?";
                }

                // Close the file
                readStaffFile->close();
            }
            else
            {
                switch (menuSelection)
                {
                case 2:
                    cout << "No staff exist. Try to create a staff account first!" << endl;
                    break;
                case 3:
                    cout << "No student exist. Try to create a student account first!" << endl;
                    break;
                }

                // clears the input buffer
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                cout << "Press ENTER to continue...";
                cin.get();
                mainMenu();
            }
        }
        catch (const runtime_error &re)
        {
            cerr << endl
                 << re.what() << '\n';

            switch (menuSelection)
            {
            case 2:
                cout << "No staff exist. Try to create a staff account first!" << endl;
                break;
            case 3:
                cout << "No student exist. Try to create a student account first!" << endl;
                break;
            }

            // clears the input buffer
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout << "Press ENTER to continue...";
            cin.get();
            mainMenu();
        }
    } while (toupper(again) == 'Y');
}

void prompt(int menuSelection)
{
    string userName, userPassword;

    do
    {
        // Prompts user to enter username
        cout << "Enter Username: ";
        cin >> userName;

        cout << "Enter password: ";
        cin >> userPassword;
    } while (validateUserCredential(userName, userPassword, menuSelection) == 1);
}

void mainMenu()
{
    system("cls");     // Clears the console
    int menuSelection; // Used to store the user input

    cout << "Home & Away Institute Main Menu" << endl;

    cout << "Login Options:" << endl
         << endl;
    cout << "1: Administrator" << endl;

    cout << "2: Staff" << endl;

    cout << "3: Student" << endl
         << endl;

    do
    {
        cout << "Selection: "; // Prompts the user to enter an input
        cin >> menuSelection;  // Store's the user input into menuSelection

        // Checks if the input was a integer
        while (cin.fail())
        {
            cin.clear(); // Used to clear the console
            cin.ignore(numeric_limits<streamsize>::max(),
                       '\n'); // Used to remove input type error from the console

            cout << "Invalid entry, try again!" << endl
                 << endl;

            cout << "Selection: ";
            cin >> menuSelection;
        }

        system("cls"); // clear console

        switch (menuSelection)
        {
        case 1:
            userType = "Admin";
            cout << "Admin Menu" << endl;
            break;
        case 2:
            userType = "Staff";
            cout << "Staff Menu" << endl;
            break;
        case 3:
            userType = "Student";
            cout << "Student Menu" << endl;
            break;
        default:
            cout << "Invalid entry, try again!" << endl
                 << endl;
        }

        // Prompts the user to enter username and password
        prompt(menuSelection);

    } while (menuSelection < 1 || menuSelection > 3);
}
