#include "Event.hxx"

DateTime::DateTime() noexcept : day(1), month(1), year(2000), hour(0), minute(0) {}

DateTime::DateTime(unsigned short d, unsigned short m, unsigned short y,
                   unsigned short h, unsigned short min) noexcept {
    day = (d >= 1 && d <= 31) ? d : 1;
    month = (m >= 1 && m <= 12) ? m : 1;
    year = (y >= 2000) ? y : 2000;
    hour = (h < 24) ? h : 0;
    minute = (min < 60) ? min : 0;
}

unsigned short DateTime::getDay() const noexcept { return day; }
unsigned short DateTime::getMonth() const noexcept { return month; }
unsigned short DateTime::getYear() const noexcept { return year; }
unsigned short DateTime::getHour() const noexcept { return hour; }
unsigned short DateTime::getMinute() const noexcept { return minute; }

void DateTime::setDay(unsigned short d) noexcept { day = (d >= 1 && d <= 31) ? d : day; }
void DateTime::setMonth(unsigned short m) noexcept { month = (m >= 1 && m <= 12) ? m : month; }
void DateTime::setYear(unsigned short y) noexcept { year = (y >= 2000) ? y : year; }
void DateTime::setHour(unsigned short h) noexcept { hour = (h < 24) ? h : hour; }
void DateTime::setMinute(unsigned short min) noexcept { minute = (min < 60) ? min : minute; }

std::string DateTime::toString(const DateTime& dt) noexcept {
    char buffer[20];
    snprintf(buffer, sizeof(buffer), "%02d.%02d.%04d %02d:%02d", 
             dt.day, dt.month, dt.year, dt.hour, dt.minute);
    return std::string(buffer);
}

Event::Event(const std::string& name, const DateTime& dt, const std::string& loc,
             const std::string& instCode, const std::string& deptCode,
             const std::string& respPerson, const std::string& pos) noexcept :
    eventName(name), dateTime(dt), location(loc), 
    instituteCode(instCode), departmentCode(deptCode),
    responsiblePerson(respPerson), position(pos) {}

std::string Event::getEventName() const noexcept { return eventName; }
DateTime Event::getDateTime() const noexcept { return dateTime; }
std::string Event::getLocation() const noexcept { return location; }
std::string Event::getInstituteCode() const noexcept { return instituteCode; }
std::string Event::getDepartmentCode() const noexcept { return departmentCode; }
std::string Event::getResponsiblePerson() const noexcept { return responsiblePerson; }
std::string Event::getPosition() const noexcept { return position; }

void Event::setEventName(const std::string& name) noexcept { eventName = name; }
void Event::setDateTime(const DateTime& dt) noexcept { dateTime = dt; }
void Event::setLocation(const std::string& loc) noexcept { location = loc; }
void Event::setInstituteCode(const std::string& code) noexcept { instituteCode = code; }
void Event::setDepartmentCode(const std::string& code) noexcept { departmentCode = code; }
void Event::setResponsiblePerson(const std::string& person) noexcept { responsiblePerson = person; }
void Event::setPosition(const std::string& pos) noexcept { position = pos; }

Event& Event::operator=(const Event& other) noexcept {
    if (this != &other) {
        eventName = other.eventName;
        dateTime = other.dateTime;
        location = other.location;
        instituteCode = other.instituteCode;
        departmentCode = other.departmentCode;
        responsiblePerson = other.responsiblePerson;
        position = other.position;
    }
    return *this;
}

std::ostream& operator<<(std::ostream& os, const Event& event) {
    os << "Event: " << event.eventName << "\n"
       << "When: " << DateTime::toString(event.dateTime) << "\n"
       << "Where: " << event.location << "\n"
       << "Institute: " << event.instituteCode << "\n"
       << "Department: " << event.departmentCode << "\n"
       << "Responsible: " << event.responsiblePerson << " (" << event.position << ")";
    return os;
}