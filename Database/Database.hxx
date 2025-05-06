#ifndef DATABASE_HXX
#define DATABASE_HXX

#include <List.hxx>
#include <Event.hxx>
#include <Filer.hxx>
#include <map>
#include <iostream>
#include <Crypter.hxx>
#include <ctime>

class Database {
protected:
    Filer file;
    std::string filename;
    std::string filename_enc;
    List<Event> data;
    Crypter crypter;
public:
    Database();
    Database(const std::string& filename);
    Database(const List<Event>& events, const std::string& filename);
    Database(const Database& db);
    ~Database();
    
    Database& operator=(const Database& db) noexcept;
    Event& operator[](unsigned int index) noexcept;
    friend std::ostream& operator<<(std::ostream& os, const Database& db);
    const Event& operator[](unsigned int index) const noexcept;
    
    void append(const Event& event) noexcept;
    void remove(unsigned int index) noexcept;
    unsigned int size() noexcept;
    
    void getEventsByMonth(List<Event>& result, unsigned short month, unsigned short year) const noexcept;
    void getEventsByResponsible(List<Event>& result, const std::string& responsible) const noexcept;
    std::map<std::string, unsigned int> getEventsCountByResponsible() const noexcept;
};

#endif // DATABASE_HXX