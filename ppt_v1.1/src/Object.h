#pragma once
#include <iostream> 
#include <string> 
#include <vector>
#include <cmath>
#include <cassert>

namespace obj{
    using Coord = std::pair<double, double>;
    using Position = std::vector<Coord>;
    
    class Object{
    public:
        Object() = default;
        virtual ~Object()= default;
    };
}