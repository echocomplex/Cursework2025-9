#include "Database.hxx"

Database::Database() {
    filename = "database.txt";
    filename_enc = "database.enc";
    crypter.decrypt(filename_enc, filename);
    file.open(filename, true);
    file.readToList(data);
}

Database::Database(const std::string& filename) {
    this->filename = filename + ".txt";
    filename_enc = filename + ".enc";
    crypter.encrypt(filename_enc, this->filename);
    file.open(filename);
    file.readToList(data);
}

Database::Database(const List<Event>& events, const std::string& filename) {
    data = events;
    this->filename = filename + ".txt";
    filename_enc = filename + ".enc";
    file.open(this->filename);
}

Database::Database(const Database& db) {
    data = db.data;
    file.open(db.filename);
    filename = db.filename;
    filename_enc = db.filename_enc;
}

Database::~Database() {
    file.rewriteFromList(data);
    crypter.encrypt(filename, filename_enc);
}

Database& Database::operator=(const Database& db) noexcept {
    if (this == &db) return *this;
    data = db.data;
    filename = db.filename;
    filename_enc = db.filename_enc;
    file.open(db.filename);
    return *this;
}

Event& Database::operator[](unsigned int index) noexcept {
    return data[index];
}

std::ostream& operator<<(std::ostream& os, const Database& db) {
    for (unsigned int i = 0; i < db.data.length(); ++i) {
        os << i + 1 << ". " << db.data[i] << "\n";
    }
    return os;
}

const Event& Database::operator[](unsigned int index) const noexcept {
    return data[index];
}

void Database::append(const Event& event) noexcept {
    data.append(event);
}

void Database::remove(unsigned int index) noexcept {
    data.remove(index);
}

unsigned int Database::size() noexcept {
    return data.length();
}

void Database::getEventsByMonth(List<Event>& result, unsigned short month, unsigned short year) const noexcept {
    for (unsigned int i = 0; i < data.length(); ++i) {
        const Event& e = data[i];
        if (e.getDateTime().getMonth() == month && e.getDateTime().getYear() == year) {
            result.append(e);
        }
    }
}

void Database::getEventsByResponsible(List<Event>& result, const std::string& responsible) const noexcept {
    for (unsigned int i = 0; i < data.length(); ++i) {
        const Event& e = data[i];
        if (e.getResponsiblePerson() == responsible) {
            result.append(e);
        }
    }
}

std::map<std::string, unsigned int> Database::getEventsCountByResponsible() const noexcept {
    std::map<std::string, unsigned int> countMap;
    
    for (unsigned int i = 0; i < data.length(); ++i) {
        const std::string& responsible = data[i].getResponsiblePerson();
        countMap[responsible]++;
    }
    
    return countMap;
}