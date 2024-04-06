//Authors: Leigh-Ann Cross, Diamond Buchanan, Winroy Jennings
#ifndef DATE_H_
#define DATE_H_

class Date
{
private:
    int day;
    int month;
    int year;

public:
    Date()
    {
        this->day = 0;
        this->month = 0;
        this->year = 0;
    }

    Date(int day, int month, int year)
    {
        this->day = day;
        this->month = month;
        this->year = year;
    }

    Date(const Date &date)
    {
        this->day = date.day;
        this->month = date.month;
        this->year = date.year;
    }

    // Mutator
    void setDay(int day)
    {
        this->day = day;
    }

    // Mutator or setters
    void setMonth(int month)
    {
        this->month = month;
    }

    void setYear(int year)
    {
        this->year = year;
    }

    int getDay()
    {
        return day;
    }

    int getMonth()
    {
        return month;
    }

    int getYear()
    {
        return year;
    }

    void display()
    {
        cout << toString() << endl;
    }

    int isValidDate(int day, int month, int year)
    {
        // Has to be older than 18 to be a staff
        time_t t = time(nullptr);
        tm *const pTInfo = localtime(&t);
        int ageLimit = (1900 + pTInfo->tm_year) - 18;

        // DATE ranges
        const int MIN_YEAR = 1957;

        // Assume by default that the date is wrong
        int isValid = 1; // ERROR ASSUME

        // Check year
        if (year > MIN_YEAR && year <= ageLimit)
        {
            // check month
            if (month >= 1 && month <= 12)
            {
                // Checks if user inputted a maximum of 31 days for Jan, Mar, May, Jul, Aug, Oct, Dec
                if ((day >= 1 && day <= 31) && (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12))
                {
                    isValid = 0;
                }
                    // Checks if user inputted a maximum of 30 days for Apr, Jun, Sep, Nov
                else if ((day >= 1 && day <= 30) && (month == 4 || month == 6 || month == 9 || month == 11))
                {
                    isValid = 0;
                }
                    // Checks if user inputted a maximum of 28 days for Feb
                else if ((day >= 1 && day <= 28) && (month == 2))
                {
                    isValid = 0;
                }

                    // Leap year for Feb, Feb normally has 28 days except for leap years where Feb has 29 days
                    // year % 4 == 0 <--   Leap years are every four (4) years        i.e. 2004, 2008, 2012, 2016, 2020, 2024, ...
                    // year % 100 != 0 <-- Every hundred (100) years Feb has 28 years i.e. 2000, 2100, 2200, 2300, 2400, 2500, ...
                else if (day == 29 && month == 2 && year % 400 == 0 || (year % 4 == 0 && year % 100 != 0))
                {
                    isValid = 0;
                }
                    // None of the above matches, thus resulting in an error
                else
                {
                    cout << "\nDay is invalid, try again!" << endl;
                }
            }
            else
            {
                cout << "\nMonth is invalid." << endl;
            }
        }
        else
        {
            cout << "\nYear is invalid." << endl;
        }

        return isValid;
    }

    string toString()
    {
        return to_string(day) + "/" + to_string(month) + "/" + to_string(year);
    }

    string getCurrentDate()
    {
        time_t t = time(NULL);
        tm *tPtr = localtime(&t);

        return to_string(tPtr->tm_mday) + "/" +
               to_string(tPtr->tm_mon + 1) + "/" +
               to_string(tPtr->tm_year + 1900);
    }
};
#endif /* DATE_H_ */
