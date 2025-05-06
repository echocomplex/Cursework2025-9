#ifndef FILER_HXX
#define FILER_HXX

#include <fstream>
#include <string>
#include <stdexcept>
#include <mutex>
#include <List.hxx>
#include <Event.hxx>

class Filer {
private:
    std::fstream file;
    std::mutex mutex;
    std::string path;
public:
    Filer() noexcept = default;
    Filer(const std::string& path, bool createNew = false);
    ~Filer() noexcept;
    
    void open(const std::string& path, bool createNew = false);
    void read(std::string& str);
    void readToList(List<Event>& events);
    void writeBack(std::string& str);
    void writeBackFromEvent(const Event& event);
    void rewrite(std::string& str);
    void rewriteFromList(const List<Event>& events);
    
    static void stringToEvent(Event& event, const std::string& str);
};

#endif // FILER_HXX