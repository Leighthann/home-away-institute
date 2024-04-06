//Authors:  Winroy Jennings
#ifndef ADMIN_H_
#define ADMIN_H_

class Administration : public Staff
{
private:
public:
    // Default constructor
    Administration()
    {
    }

    // Primary constructor
    Administration(string userID, string fName, string lName, string password, string position, string faculty, string address, string department, int day, int month, int year)
    {
        this->userID = userID;
        this->fName = fName;
        this->lName = lName;
        this->password = password;
        this->position = position;
        this->faculty = faculty;
        this->address = address;
        this->department = department;
        this->dateEmployed = Date(day, month, year);
    }

    // Copy constructor
    Administration(const Administration &admin)
    {
        this->userID = admin.userID;
        this->fName = admin.fName;
        this->lName = admin.lName;
        this->password = admin.password;
        this->position = admin.position;
        this->faculty = admin.faculty;
        this->address = admin.address;
        this->department = admin.department;
        this->dateEmployed = admin.dateEmployed;
    }

    int validateNewStaff(string userID, string fName, string lName)
    {
        /*
          0 means that the entry is accepted
          1 means that the entry already exist but with a different name
        */

        int result;

        try
        {
            ifstream *readStaffFile = new ifstream(staffDatabase, ios::in);

            if (!readStaffFile->is_open())
            {
                ofstream *writeStaffFile = new ofstream(staffDatabase, ios::out);
                writeStaffFile->close();
            }
            else
            {
                if (readStaffFile->fail())
                {
                    throw runtime_error("Error accessing database!");
                }

                string id, firstName, lastName, password, position, faculty, address, department, dateEmployed;

                while (!readStaffFile->eof())
                {
                    *readStaffFile >> id >> firstName >> lastName >> password >> position >> faculty >> department >> dateEmployed >> address;

                    if (id == userID)
                    {
                        if (firstName != fName && lastName != lName)
                        {
                            // ID is already taken
                            result = 1;

                            // Prompt the user that the ID is already taken
                            // They should try again!
                            cout << "ID taken, try again!" << endl;
                        }
                        else
                        {
                            // ID is available
                            result = 0;
                            break;
                        }
                    }
                        // ID entered is not in the database
                        // Then it is available
                    else
                    {
                        result = 0;
                    }

                    // Reset
                    id = "?";
                }

                // Close the file
                readStaffFile->close();
            }
        }
        catch (const runtime_error &re)
        {
            cerr << re.what() << '\n';
        }

        // The function returns the result where it was called
        return result;
    }

    void saveStaff(Staff staff)
    {
        try
        {
            ofstream *writeStaffFile = new ofstream(staffDatabase, ios::out | ios::app);

            if (writeStaffFile->fail())
            {
                throw runtime_error("Error accessing database!");
            }

            *writeStaffFile << staff.getUserID() << "\t"
                            << staff.getFName() << "\t"
                            << staff.getLName() << "\t"
                            << staff.getPassword() << "\t"
                            << staff.getPosition() << "\t"
                            << staff.getFaculty() << "\t"
                            << staff.getDepartment() << "\t"
                            << staff.getDateEmployed().toString() << "\t"
                            << staff.getAddress() << endl;

            writeStaffFile->close();
            cout << "\nInformation has been saved!" << endl;
        }
        catch (runtime_error *re)
        {
            cerr << re->what();
        }

        cout << "Press ENTER to continue...";
        cin.ignore(); // Ignore buffer entry
        cin.clear();  // Clears the input buffer
        cin.get();    // Wait until the user press a key
        Administration::login();
    }

    void createStaff()
    {
        Staff staff;

        string id, fName, lName, password, position, faculty, address, department;

        // Clear console
        system("cls");

        char spacer, spacer2;
        int day, month, year;

        cout << "Create New Staff" << endl
             << endl;

        try
        {
            do
            {
                cout << "Enter staff ID: ";
                cin >> id;

                cout << "Enter staff first name: ";
                cin >> fName;

                cout << "Enter staff last name: ";
                cin >> lName;

                // Check if ID matches in the database
            } while (validateNewStaff(userID, fName, lName) == 1);

            cout << "Enter staff password: ";
            cin >> password;

            cout << "Enter what position of staff: ";
            cin >> position;

            cout << "Enter staff faculty: ";
            cin >> faculty;
        }
        catch (int)
        {
            cout << "Name cannot contain a number, try entering text." << endl;
        }

        cout << "Enter staff address: ";
        cin >> address;

        cout << "Enter staff department: ";
        cin >> department;

        // Validation for date
        do
        {
            // Validation
            do
            {
                // Prompt the user to enter staff employee date
                cout << "Enter the date that the staff employed on; using this format {DD/MM/YYYY} i.e. 01/09/1995: ";

                // Store the user input
                cin >> day >> spacer >> month >> spacer2 >> year;

                if (spacer != '/' && spacer2 != '/')
                {
                    cout << "Invalid format, try again!" << endl
                         << endl;
                }
            } while (spacer != '/' && spacer2 != '/');

            staff.setDateEmployed(Date(day, month, year));
        } while (staff.getDateEmployed().isValidDate(day, month, year) == 1);

        staff.setUserID(id);
        staff.setFName(fName);
        staff.setLName(lName);
        staff.setPassword(password);
        staff.setPosition(position);
        staff.setFaculty(faculty);
        staff.setAddress(address);
        staff.setDepartment(department);

        // Save the information in the database.
        saveStaff(staff);
    }

    int validStaffOldPassword(string userID, string currentPassword)
    {
        /*
         0 means that the entry is accepted
         1 means that the entry already exist but with a different name
       */

        int result;
        string id, firstName, lastName, password, position, faculty, address, department, dateEmployed;

        try
        {
            ifstream *readStaffFile = new ifstream(staffDatabase, ios::in);

            if (readStaffFile->fail())
            {
                throw runtime_error("Error accessing database!");
            }

            readStaffFile->seekg(0, ios::beg);

            while (!readStaffFile->eof())
            {
                *readStaffFile >> id >> firstName >> lastName >> password >> position >> faculty >> department >> dateEmployed >> address;

                if (id == userID)
                {
                    if (password != currentPassword)
                    {
                        // ID and password does not match in the database
                        result = 1;

                        // Prompt user that the password entered does not match in database
                        cout << "Invalid password, try again!" << endl
                             << endl;
                        break;
                    }
                    else
                    {
                        // ID and password does match in the database
                        result = 0;
                        break;
                    }
                }
                    // If pointer is at the last record and the userID is still not found.
                else if (id != userID)
                {
                    if (readStaffFile->eof())
                    {
                        result = 1;

                        // Prompt user that the userID entered does not match in database
                        cout << userID << " does not exist in the database; try again!" << endl
                             << endl;
                        break;
                    }
                }
            }

            // Close the file
            readStaffFile->close();
        }
        catch (const runtime_error *re)
        {
            cerr << re->what() << endl;
        }

        // The function returns the result where it was called
        return result;
    }

    void setStaffNewPassword(string userID, string newPassword)
    {
        try
        {
            ifstream *readStaffFile = new ifstream(staffDatabase, ios::in);
            ofstream *writeTempStaffFile = new ofstream(tempStaffDatabase, ios::out | ios::app);

            if (readStaffFile->fail() && writeTempStaffFile->fail())
            {
                throw runtime_error("Error accessing database!");
            }

            string id, firstName, lastName, password, position, faculty, address, department, dateEmployed;
            string idTemp, firstNameTemp, lastNameTemp, passwordTemp, positionTemp, facultyTemp, addressTemp, departmentTemp, dateEmployedTemp;

            readStaffFile->seekg(0, ios::beg);

            while (!readStaffFile->eof())
            {
                *readStaffFile >> id >> firstName >> lastName >> password >> position >> faculty >> department >> dateEmployed >> address;

                if (userID == id)
                {
                    idTemp = id;
                    firstNameTemp = firstName;
                    lastNameTemp = lastName;
                    positionTemp = position;
                    facultyTemp = faculty;
                    departmentTemp = department;
                    dateEmployedTemp = dateEmployed;
                    addressTemp = address;
                }

                if (id != userID)
                {
                    if (id == "?")
                    {
                        break;
                    }

                    *writeTempStaffFile << id << "\t"
                                        << firstName << "\t"
                                        << lastName << "\t"
                                        << password << "\t"
                                        << position << "\t"
                                        << faculty << "\t"
                                        << department << "\t"
                                        << dateEmployed << "\t"
                                        << address << endl;
                }

                // Reset id
                id = "?";
            }

            *writeTempStaffFile << idTemp << "\t"
                                << firstNameTemp << "\t"
                                << lastNameTemp << "\t"
                                << newPassword << "\t"
                                << positionTemp << "\t"
                                << facultyTemp << "\t"
                                << departmentTemp << "\t"
                                << dateEmployedTemp << "\t"
                                << addressTemp << endl;

            readStaffFile->close();
            writeTempStaffFile->close();

            // Remove file
            if (remove("staff-db.txt") != 0)
                cerr << "Error removing file";

            // Rename file
            if (rename("temp-staff-db.txt", "staff-db.txt") != 0)
                cerr << "Error renaming file" << endl;

            cout << endl
                 << "Password was changed successfully!" << endl;

            // clears the input buffer
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout << "Press ENTER to continue...";
            cin.get();
            Administration::login();
        }
        catch (runtime_error *re)
        {
            cerr << re->what();
        }
    }

    void changeStaffPassword()
    {
        Staff staff;
        string id, currentPassword, newPassword;

        bool isStaffPasswordCorrect = false;

        // Clear console
        system("cls");

        try
        {
            ifstream *readStaffFile = new ifstream(staffDatabase, ios::in);

            if (readStaffFile->fail())
            {
                throw runtime_error("Error accessing database!");
            }

            // Move the read position to the end of the file
            readStaffFile->seekg(SEEK_END);

            if (readStaffFile->tellg() != 0)
            {
                readStaffFile->close();

                cout << "Change Staff Password" << endl
                     << endl;

                try
                {
                    do
                    {
                        cout << "Enter staff ID: ";
                        cin >> id;

                        cout << "Enter current password: ";
                        cin >> currentPassword;

                        // Check if ID matches in the database
                    } while (validStaffOldPassword(id, currentPassword) == 1);

                    cout << "Enter new password: ";
                    cin >> newPassword;
                }
                catch (int)
                {
                    cout << "Name cannot contain a number, try entering text." << endl;
                }

                // Change staff password
                setStaffNewPassword(id, newPassword);
            }
            else
            {
                readStaffFile->close(); //close file
                cout << "No data exist, try adding a staff first!" << endl;

                // clears the input buffer
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                cout << "Press ENTER to continue...";
                cin.get();

                Administration::login();
            }
        }
        catch (runtime_error &re) 
        {
            cerr << "No data exist, try adding a staff first!" << endl;

            // clears the input buffer
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout << "Press ENTER to continue...";
            cin.get();
            Administration::login(); //calls admin class
        }
    }

    // Creates an abstract method, to be use for the different menu systems.
    void login()
    {
        // Use for selection menu
        int optionSelection;

        system("cls"); // Clears the console

        cout << "Administrator Menu Console" << endl
             << endl;

        cout << "Select one of the following option." << endl;
        cout << "1 - Create Staff" << endl;
        cout << "2 - Change Staff Password" << endl;
        cout << "3 - Main Menu"
             << endl;

        do
        {
            cout << "Selection: ";
            cin >> optionSelection;

            switch (optionSelection)
            {
                case 1:
                    createStaff();
                    break;
                case 2:
                    changeStaffPassword();
                    break;
                case 3:
                    mainMenu();
                    break;
                default:
                    cout << "Invalid option, try again!" << endl;
                    break;
            }
        } while (optionSelection < 1 || optionSelection > 2);
    }
};
#endif
