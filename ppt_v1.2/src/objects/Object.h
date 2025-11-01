#pragma once
#include <iostream> 
#include <string> 
#include <vector>
#include <array>
#include <cmath>
#include <cassert>

namespace obj{
    using Coord = std::pair<double, double>;
    using Position = std::vector<Coord>;
    
    const std::array<std::string, 7> colors = {"red", "blue", "black", "yellow", "green", "purple", "white"};


    class Object{
    public:
        Object() = default;
        virtual void show() const = 0;
        virtual ~Object()= default;
    };
}