#pragma once
#include <fstream>
#include <string>
#include "Object.h"

namespace obj{
    class Picture : public Object {
    public:
        Picture() = default;
        void create(const Position& coords, const std::string& file){
            assert(coords.size() == 2);
            pos = coords;
            pic.open(file);
            if (!pic)  throw std::runtime_error("ERROR: Picture file not found\n");
        }
    private:
        Position pos;
        std::fstream pic;
        
    };
}