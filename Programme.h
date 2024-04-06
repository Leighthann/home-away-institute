//Authors: Diamond Buchanan
#ifndef PROGRAMME_H_
#define PROGRAMME_H_

class Programme
{
private:
    string programmeCode;
    string programmeName;
    int maxNumOfCourses;
    string award;
    string accreditation;

public:
    Programme() //Default Constructor
    {
        programmeCode = "";
        programmeName = "";
        maxNumOfCourses = 0;
        award = "";
        accreditation = "";
    }

    Programme(string programmeCode, string programmeName, int maxNumOfCourses,string award, string accreditation) //Primary Constructor
    {
        this->programmeCode = programmeCode;
        this->programmeName = programmeName;
        this->maxNumOfCourses = maxNumOfCourses;
        this->award = award;
        this->accreditation = accreditation;
    }

    Programme(const Programme &programme) //Copy Constructor
    {
        this->programmeCode = programme.programmeCode;
        this->programmeName = programme.programmeCode;
        this->maxNumOfCourses = programme.maxNumOfCourses;
        this->award = programme.award;
        this->accreditation = programme.accreditation;
    }

//Mutators
    string getProgrammeCode()
    {
        return programmeCode;
    }

    void setProgrammeCode(string programmeCode)
    {

        this->programmeCode = programmeCode;
    }

    string getProgrammeName()
    { return programmeName; }

    void setProgrammeName(string programmeName)
    {
        this->programmeName = programmeName;
    }

    int getMaxNumOfCourses()
    {
        return maxNumOfCourses;
    }

    void setMaxNumOfCourses(int maxNumOfCourses)
    {
        this->maxNumOfCourses = maxNumOfCourses;
    }

    string getAward()
    {
        return award;
    }

    void setAward(string award)
    {
        this->award = award;
    }

    string getAccreditation()
    {
        return accreditation;
    }

    void setAccreditation(string accreditation)
    {
        this->accreditation = accreditation;
    }
};
#endif
