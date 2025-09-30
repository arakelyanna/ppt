#pragma once
#include <vector>
#include <string>
#include <unordered_map>
#include <variant>
namespace prs {

    using DataType = std::variant<std::monostate, 
                            std::string, 
                            std::vector<double>, 
                            double, 
                            bool,
                            int>;
    using CommandType = std::unordered_map<std::string, DataType>;

    struct Command{
    private:
        CommandType command = {
            {"command", std::monostate{}},
            {"file", std::monostate{}},
            {"at", 0},
            {"placement", std::monostate{}},
            {"font_size", std::monostate{}},
            {"font_family", std::monostate{}},
            {"font_color", std::monostate{}},
            {"text_value", std::monostate{}},
            {"picture_file", std::monostate{}},
            {"shape", std::monostate{}},
            {"length", std::monostate{}},
            {"angle", std::monostate{}},
            {"shape_width", std::monostate{}},
            {"shape_height", std::monostate{}},
            {"filled", std::monostate{}},
            {"borderline_width", 0},
            {"borderline_color", std::monostate{}},
            {"triangle_sides", std::monostate{}},
            {"circle_radius", std::monostate{}}
        };
    public:
        DataType get(const std::string& key){
            return command[key];
        }
        void set(std::string key, DataType value) {
            command[key] == value; 
        }
    };


}