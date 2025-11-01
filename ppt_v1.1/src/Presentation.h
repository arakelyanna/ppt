#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "Document.h"
#include "Slide.h"

namespace doc{
    class Ppt{
    public:
        Ppt() = default;
        Document& save(){
            return parseToDoc(); 
        }
    private:
        Document& parseToDoc();
        std::vector<obj::Slide> ppt;
    };
}