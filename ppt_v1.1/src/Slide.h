#pragma once
#include <iostream>
#include <string>
#include "Shape.h"
#include "Slide.h"

namespace obj{
    class Slide{
    public:
        Slide() = default;
    private:
        size_t position;
    };
}