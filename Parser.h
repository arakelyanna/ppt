#pragma once
#include <iostream>
#include <vector>
#include <array>
#include <optional>
#include <variant>
#include <map>
#include <string>

using DataType = std::variant<std::monostate, std::string, std::vector<double>, double, int, bool>;
using CommandType = std::map<std::string, DataType>;


class Command{
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
        {"picture_file_path", std::monostate{}},
        {"shape", std::monostate{}},
        {"length", std::monostate{}},
        {"angle", std::monostate{}},
        {"shape_height", std::monostate{}},
        {"shape_width", std::monostate{}},
        {"filled", std::monostate{}},
        {"borderline_width", 0},
        {"borderline_color", std::monostate{}},
        {"triangle_sides", std::monostate{}},
        {"circle_radius", std::monostate{}}
    };
public:
    DataType get_value_of(std::string key){
        return command[key];
    }
};


class Parser{
private:
    enum class States {start, open, close, new_file, add, add_shape, read, files, exit};
    States state = States::start;
    Tokens tokens;
public:
    Parser(Tokens tokens) : tokens(tokens) {}
    


};