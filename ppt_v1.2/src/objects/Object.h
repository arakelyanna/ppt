#pragma once
#include <string> 
#include <vector>
#include <array>
#include <memory>
#include <cmath>
#include <cassert>

namespace out {
    class IVisitor;  
}

namespace obj{
    using Coord = std::pair<double, double>;
    using Geometry = std::vector<Coord>;
    
    const std::array<std::string, 8> colors = {"red", "blue", "black", "yellow", "green", "purple", "white", "pink"};


    class Object{
    public:
        Object() = default;
        
        virtual const Geometry& get_geometry() const = 0;
        virtual void accept(const out::IVisitor& visitor) = 0;

        virtual ~Object()= default;
    };
}