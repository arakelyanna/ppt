#pragma once
#include <iostream>
#include <optional>
#include <string>
#include "Presentation.h"
#include "Slide.h"

namespace doc{
    class Document{
    public:
        Document() = default;
        obj::Presentation open() {
            std::cout << "opened into a ppt\n";
        }
    private:
        std::string path;
        // std::optional<Shape> shape
    };
}