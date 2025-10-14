#pragma once
#include <string>
#include <unordered_map>
#include <variant>
#include "Tokenizer.h"

namespace cmd{
    using Data = std::variant<
            int, 
            double, 
            std::monostate, 
            std::string, 
            std::pair<double, double>,
            std::array<double, 3>,
            bool>;

    class Options
    {
    public:
        auto set(const std::string& key, const Data& value){
            auto lookUp= params.find(key);
            if (lookUp == params.end()) throw std::runtime_error("ERROR: Invalid Option -" + key + "!");
            lookUp->second = value;
        }
    private:
        
        std::unordered_map<std::string, Data> params = {
                {"position", std::monostate{}}, //array
                {"file", std::monostate{}},
                {"angle", std::monostate{}},
                {"sides", std::monostate{}}, //array
                {"height", std::monostate{}},
                {"width", std::monostate{}},
                {"length", std::monostate{}},
                {"filled", true},
                {"color", std::monostate{}},
                {"borderline width", 0},
                {"borderline color", std::monostate{}}
            };
        
    };
}