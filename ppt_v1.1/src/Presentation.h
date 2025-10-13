#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "Document.h"
#include "Slide.h"

namespace obj{
    class Presentation{
    public:
        Presentation() = default;
        doc::Document save(){
            std::cout << "save into a document"; //actually a  parser
        }
    private:
        std::vector<Slide> ppt;
    };
}