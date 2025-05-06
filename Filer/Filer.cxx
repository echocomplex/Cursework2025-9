#include "Filer.hxx"

Filer::Filer(const std::string& path, bool createNew) {
    if (createNew) {
        file.open(path, std::ios::in);
        if (!file.is_open()) {
            file.open(path, std::ios::out);
            file.close();
            file.open(path, std::ios::in);
            if (!file.is_open()) throw std::runtime_error("Failed to create the file.");
        }
    }
    else {
        file.open(path, std::ios::in);
        if (!file.is_open()) throw std::runtime_error("File cannot be opened or does not exist");
    }
    this->path = path;
}

Filer::~Filer() noexcept {
    if (file.is_open()) file.close();
}

void Filer::open(const std::string& path, bool createNew) {
    if (createNew) {
        file.open(path, std::ios::in);
        if (!file.is_open()) {
            file.open(path, std::ios::out);
            file.close();
            file.open(path, std::ios::in);
            if (!file.is_open()) throw std::runtime_error("Failed to create the file.");
        }
    }
    else {
        file.open(path, std::ios::in);
        if (!file.is_open()) throw std::runtime_error("File cannot be opened or does not exist");
    }
    this->path = path;
}

void Filer::read(std::string& str) {
    if (!file.is_open()) throw std::runtime_error("File is not open");
    
    std::lock_guard<std::mutex> lock(mutex);
    
    file.close();
    file.open(path, std::ios::in);
    file.seekg(0, std::ios::beg);
    
    std::string temp;
    while (std::getline(file, temp)) {
        str += temp + '\n';
    }
}

void Filer::readToList(List<Event>& events) {
    if (!file.is_open()) throw std::runtime_error("File is not open");
    
    std::lock_guard<std::mutex> lock(mutex);
    
    file.close();
    file.open(path, std::ios::in);
    file.seekg(0, std::ios::beg);
    
    std::string line;
    Event event;
    while (std::getline(file, line)) {
        event = Event();
        stringToEvent(event, line);
        events.append(event);
    }
}

void Filer::writeBack(std::string& str) {
    if (!file.is_open()) throw std::runtime_error("File is not open");
    if (str.empty()) return;
    
    std::lock_guard<std::mutex> lock(mutex);
    
    file.close();
    file.open(path, std::ios::out | std::ios::app);
    file << str << '\n';
    file.flush();
}

void Filer::writeBackFromEvent(const Event& event) {
    if (!file.is_open()) throw std::runtime_error("File is not open");
    
    std::lock_guard<std::mutex> lock(mutex);
    
    file.close();
    file.open(path, std::ios::out | std::ios::app);
    
    file << event.getEventName() << "$$"
         << event.getDateTime().getDay() << "$$"
         << event.getDateTime().getMonth() << "$$"
         << event.getDateTime().getYear() << "$$"
         << event.getDateTime().getHour() << "$$"
         << event.getDateTime().getMinute() << "$$"
         << event.getLocation() << "$$"
         << event.getInstituteCode() << "$$"
         << event.getDepartmentCode() << "$$"
         << event.getResponsiblePerson() << "$$"
         << event.getPosition() << '\n';
    
    file.flush();
}

void Filer::rewrite(std::string& str) {
    if (!file.is_open()) throw std::runtime_error("File is not open");
    if (str.empty()) return;
    
    std::lock_guard<std::mutex> lock(mutex);
    
    file.close();
    file.open(path, std::ios::out | std::ios::trunc);
    file << str << '\n';
    file.flush();
}

void Filer::rewriteFromList(const List<Event>& events) {
    if (!file.is_open()) throw std::runtime_error("File is not open");
    if (events.length() == 0) return;
    
    std::lock_guard<std::mutex> lock(mutex);
    
    file.close();
    file.open(path, std::ios::out | std::ios::trunc);
    
    for (unsigned int i = 0; i < events.length(); ++i) {
        const Event& e = events[i];
        file << e.getEventName() << "$$"
             << e.getDateTime().getDay() << "$$"
             << e.getDateTime().getMonth() << "$$"
             << e.getDateTime().getYear() << "$$"
             << e.getDateTime().getHour() << "$$"
             << e.getDateTime().getMinute() << "$$"
             << e.getLocation() << "$$"
             << e.getInstituteCode() << "$$"
             << e.getDepartmentCode() << "$$"
             << e.getResponsiblePerson() << "$$"
             << e.getPosition() << '\n';
    }
    
    file.flush();
}

void Filer::stringToEvent(Event& event, const std::string& str) {
    if (str.empty()) return;

    std::string fields[11];
    unsigned short count = 0;
    
    for (size_t i = 0; i < str.size() && count < 11; ++i) {
        if (i + 1 < str.size() && str[i] == '$' && str[i+1] == '$') {
            ++count;
            ++i;
        } else {
            fields[count] += str[i];
        }
    }
    DateTime dt;
    try {
        dt = DateTime (
            std::stoul(fields[1]),
            std::stoul(fields[2]),   
            std::stoul(fields[3]),  
            std::stoul(fields[4]),  
            std::stoul(fields[5])
        );
    } catch (const std::exception& e) {
        dt = DateTime(1, 1, 2000, 0, 0);
    }
        event.setEventName(fields[0]);
        event.setDateTime(dt);
        event.setLocation(fields[6]);
        event.setInstituteCode(fields[7]);
        event.setDepartmentCode(fields[8]);
        event.setResponsiblePerson(fields[9]);
        event.setPosition(fields[10]);
        
    
}