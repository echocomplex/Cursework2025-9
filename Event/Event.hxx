#ifndef EVENT_HXX
#define EVENT_HXX

#include <string>
#include <iostream>
#include <ctime>

class DateTime {
private:
    unsigned short day, month, year;
    unsigned short hour, minute;
public:
    DateTime() noexcept;
    DateTime(unsigned short d, unsigned short m, unsigned short y, 
             unsigned short h, unsigned short min) noexcept;
    
    unsigned short getDay() const noexcept;
    unsigned short getMonth() const noexcept;
    unsigned short getYear() const noexcept;
    unsigned short getHour() const noexcept;
    unsigned short getMinute() const noexcept;
    
    void setDay(unsigned short d) noexcept;
    void setMonth(unsigned short m) noexcept;
    void setYear(unsigned short y) noexcept;
    void setHour(unsigned short h) noexcept;
    void setMinute(unsigned short min) noexcept;
    
    static std::string toString(const DateTime& dt) noexcept;
};

class Event {
private:
    std::string eventName;
    DateTime dateTime;
    std::string location;
    std::string instituteCode;
    std::string departmentCode;
    std::string responsiblePerson;
    std::string position;
public:
    Event() noexcept = default;
    Event(const std::string& name, const DateTime& dt, const std::string& loc,
          const std::string& instCode, const std::string& deptCode,
          const std::string& respPerson, const std::string& pos) noexcept;
    
    std::string getEventName() const noexcept;
    DateTime getDateTime() const noexcept;
    std::string getLocation() const noexcept;
    std::string getInstituteCode() const noexcept;
    std::string getDepartmentCode() const noexcept;
    std::string getResponsiblePerson() const noexcept;
    std::string getPosition() const noexcept;
    
    void setEventName(const std::string& name) noexcept;
    void setDateTime(const DateTime& dt) noexcept;
    void setLocation(const std::string& loc) noexcept;
    void setInstituteCode(const std::string& code) noexcept;
    void setDepartmentCode(const std::string& code) noexcept;
    void setResponsiblePerson(const std::string& person) noexcept;
    void setPosition(const std::string& pos) noexcept;
    
    Event& operator=(const Event&) noexcept;
    friend std::ostream& operator<<(std::ostream& os, const Event& event);
};

#endif // EVENT_HXX