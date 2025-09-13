#include <fstream>
#include <optional>
#include <string>


class Fetcher{
private:
    std::ifstream file;
    std::string line;
public:
    Fetcher(std::string path) {
        file.open(path);
        if (!file.is_open())
        {
            throw std::runtime_error("ERROR: Could not open file: " + path);
        }
    }
    std::optional<std::string> next_line(){
        if(std::getline(file, line)){
            return line;
        }
        else {
            return std::nullopt;
        }
    }
};
