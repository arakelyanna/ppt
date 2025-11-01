#pragma once
#include <fstream>
#include "Presentation.h"
#include "Slide.h"

namespace doc{
    class Document{
    public:
        Document() = default;
        Document(const std::string& file_path) : file_path(file_path){
            file.open(file_path);
            if (!file)  throw std::runtime_error("ERROR: Ppt file not found\n");

        }
        Ppt& op() {
            return parseToPpt();
        }
    private:
        Ppt& parseToPpt();
        std::string file_path;
        std::ifstream file;
    };
}