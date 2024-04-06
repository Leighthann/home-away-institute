//Authors: Winroy Jennings
#ifndef USER_H_
#define USER_H_

class User
{
protected:
    string userID;
    string fName;
    string lName;
    string password;
    string position;
    string faculty;
    string address;
    string contactNumber;

public:
    User() // default
    {
        userID = "";
        fName = "";
        lName = "";
        password = "";
        position = "";
        faculty = "";
        address = "";
        contactNumber = "";
    }

    User(string userID, string fName, string lName, string password, string position, string faculty, string address, string contactNumber) //primary
    {
        this->userID = userID;
        this->fName = fName;
        this->lName = lName;
        this->password = password;
        this->position = position;
        this->faculty = faculty;
        this->address = address;
        this->contactNumber = contactNumber;
    }

    User(const User &user)//copy constructor
    {
        this->userID = user.userID;
        this->fName = user.fName;
        this->lName = user.lName;
        this->password = user.password;
        this->position = user.position;
        this->faculty = user.faculty;
        this->address = user.address;
        this->contactNumber = user.contactNumber;
    }


    string getContactNumber()
    {
        return this->contactNumber;
    }

    void setContactNumber(string contactNumber)
    {
        this->contactNumber = contactNumber;
    }

    string getUserID()
    {
        return this->userID;
    }

    void setUserID(string userID)
    {
        this->userID = userID;
    }

    string getFName()
    {
        return this->fName;
    }

    void setFName(string fName)
    {
        this->fName = fName;
    }

    string getLName()
    {
        return this->lName;
    }

    void setLName(string lName)
    {
        this->lName = lName;
    }

    string getPassword()
    {
        return this->password;
    }

    void setPassword(string password)
    {
        this->password = password;
    }

    string getPosition()
    {
        return this->position;
    }

    void setPosition(string position)
    {
        this->position = position;
    }

    string getFaculty()
    {
        return this->faculty;
    }

    void setFaculty(string faculty)
    {
        this->faculty = faculty;
    }

    string getAddress()
    {
        return this->address;
    }

    void setAddress(string address)
    {
        this->address = address;
    }

    // Abstract method
    virtual void login() = 0;
};
#endif
