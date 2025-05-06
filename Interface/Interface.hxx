#ifndef INTERFACE_HXX
#define INTERFACE_HXX

#include <iostream>
#include <Event.hxx>
#include <List.hxx>
#include <Database.hxx>
#include <map>

class Interface {
private:
    Database db;
    void displayMenu();
    void getEvent(Event& event);
    int removeEvent();
    void clearInputBuffer();
    void displayEvents(const List<Event>& events);
public:
    Interface() = default;
    Interface(const Interface&) = delete;
    Interface& operator=(const Interface&) = delete;
    ~Interface() noexcept = default;
    void run();
};

#endif // INTERFACE_HXX