#include "Interface.hxx"

void Interface::clearInputBuffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void Interface::getEvent(Event& event) {
    std::string name, location, instCode, deptCode, responsible, position;
    unsigned short day, month, year, hour, minute;

    std::cout << "\n=== Add New Event ===\n";
    
    std::cout << "Event name: ";
    std::getline(std::cin, name);
    
    std::cout << "Date (day month year): ";
    std::cin >> day >> month >> year;
    this->clearInputBuffer();
    
    std::cout << "Time (hour minute): ";
    std::cin >> hour >> minute;
    this->clearInputBuffer();
    
    std::cout << "Location: ";
    std::getline(std::cin, location);
    
    std::cout << "Institute code: ";
    std::getline(std::cin, instCode);
    
    std::cout << "Department code: ";
    std::getline(std::cin, deptCode);
    
    std::cout << "Responsible person: ";
    std::getline(std::cin, responsible);
    
    std::cout << "Position: ";
    std::getline(std::cin, position);
    
    DateTime dt(day, month, year, hour, minute);
    event = Event(name, dt, location, instCode, deptCode, responsible, position);
}

int Interface::removeEvent() {
    int number;
    while (true) {
        std::cout << "Enter event number to delete (1-" << db.size() << "): ";
        
        if (!(std::cin >> number)) {
            std::cin.clear();
            clearInputBuffer();
            std::cerr << "Error: Please enter a number\n\n";
            continue;
        }

        if (number > 0 && number <= db.size()) {
            return number - 1;
        }
        
        std::cerr << "Error: Number must be between 1 and " << db.size() << "\n\n";
    }
}

void Interface::displayEvents(const List<Event>& events) {
    if (events.length() == 0) {
        std::cout << "No events found.\n";
        return;
    }
    
    for (unsigned int i = 0; i < events.length(); ++i) {
        std::cout << i+1 << ". " << events[i] << "\n\n";
    }
}

void Interface::displayMenu() {
    std::cout << "\n=== Department Events Database ===" << std::endl;
    std::cout << "1. Display all events" << std::endl;
    std::cout << "2. Add new event" << std::endl;
    std::cout << "3. Remove event" << std::endl;
    std::cout << "4. View events by month" << std::endl;
    std::cout << "5. View events by responsible" << std::endl;
    std::cout << "6. View events statistics" << std::endl;
    std::cout << "7. Exit program" << std::endl;
    std::cout << "Enter your choice (1-7): ";
}

void Interface::run() {
    short choice = 0;
    Event newEvent;
    List<Event> events;
    unsigned short month, year;
    std::map<std::string, unsigned int> stats;
    std::string responsible;
    
    while (true) {
        displayMenu();

        while (!(std::cin >> choice) || choice < 1 || choice > 7) {
            std::cout << "Invalid input. Please enter 1-7: ";
            clearInputBuffer();
        }

        clearInputBuffer();

        switch (choice) {
            case 1:
                std::cout << "\n[All Events]\n";
                for (unsigned int i = 0; i < db.size(); ++i) {
                    events.append(db[i]);
                }
                displayEvents(events);
                events.clear();
                break;
                
            case 2:
                getEvent(newEvent);
                db.append(newEvent);
                std::cout << "Event added successfully!\n";
                break;
                
            case 3:
                if (db.size() == 0) {
                    std::cout << "No events to remove.\n";
                    break;
                }
                db.remove(removeEvent());
                std::cout << "Event removed successfully!\n";
                break;
                
            case 4:
                std::cout << "Enter month and year (e.g. 5 2023): ";
                std::cin >> month >> year;
                clearInputBuffer();
                std::cout << "\n[Events for " << month << "/" << year << "]\n";
                db.getEventsByMonth(events, month, year);
                displayEvents(events);
                events.clear();
                break;
                
            case 5:
                std::cout << "Enter responsible person name: ";
                std::getline(std::cin, responsible);
                std::cout << "\n[Events by " << responsible << "]\n";
                db.getEventsByResponsible(events, responsible);
                displayEvents(events);
                events.clear();
                break;
                
            case 6:
                std::cout << "\n[Events Statistics]\n";
                stats = db.getEventsCountByResponsible();
                for (const auto& [person, count] : stats) {
                    std::cout << person << ": " << count << " events\n";
                }
                stats.clear();
                break;
                
            case 7:
                std::cout << "\nExiting program...\n";
                return;
        }

        std::cout << "\nPress Enter to continue...";
        clearInputBuffer();
    }
}