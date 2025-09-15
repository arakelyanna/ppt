#pragma once
#include <iostream>
#include <vector>
#include <array>
#include <optional>
#include <variant>
#include <map>
#include <string>
#include <exception>

using DataType = std::variant<std::monostate, 
                            std::string, 
                            std::vector<double>, 
                            double, 
                            bool,
                            int>;
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
    DataType get_value_of(const std::string& key){
        return command[key];
    }
    void set_value_of(std::string key, DataType value) {
        command[key] == value; 
    }
};


class Parser{
private:
    enum class States { start, new_file, open, close, show, add, newslide,
        picture, shape, text, exit, error, end };
    enum class Attributes { none, line, rectangle, square, triangle, circle, at, placement, font_size, 
        font_family, font_color, length, angle, shape_height, shape_width, filled, filling_collor, borderline_width, 
        borderline_color, triangle_sides, circle_radius, error};
    States state = States::start;
    Attributes attr = Attributes::none;
    Tokens tokens;
    Command command;
public:
    Command& parse(const Tokens& tokens){
        for (size_t i = 0; i < tokens.size(); ++i)
        {
            switch (state)
            {
                case States::start:
                if (tokens[i] == "new")
                {
                    command.set_value_of("command", "new");
                    state=States::new_file;
                }
                else if (tokens[i] == "open")
                {
                    command.set_value_of("command", "open");
                    state=States::open;
                }
                else if (tokens[i] == "add")
                {
                    command.set_value_of("command", "add");
                    state=States::add;
                }
                else if (tokens[i] == "newslide")
                {
                    command.set_value_of("command", "newslide");
                    attr=Attributes::at;
                    state=States::newslide;
                }
                else if (tokens[i] == "show")
                {
                    state=States::show;
                }
                else if (tokens[i] == "close")
                {
                    command.set_value_of("command", "close");
                    state=States::end;
                }
                else if (tokens[i] == "exit" || tokens[i] == "q")
                {
                    command.set_value_of("command", "exit");
                    state=States::end;
                }else if (tokens[i] == "info")
                {
                    command.set_value_of("command", "info");
                    state=States::end;
                }
                else{
                    std::cerr << "Incvalid command\n";
                    state = States::error;
                }                
                break;
                case States::new_file:
                if (tokens[i] != ""){
                    command.set_value_of("file", tokens[i]);
                    state=States::end;
                    
                }
                else {
                    std::cerr << "No such file or directory.\n";
                    state = States::error;
                }
                
                break;
                case States::open:
                if (tokens[i] != "") {
                    command.set_value_of("file", tokens[i]);
                    state=States::end;
                }
                else{
                    std::cerr << "No such file or directory.\n";
                    state = States::error;
                }
                break;
                case States::add:
                if (tokens[i] == "shape"){
                    state = States::shape;
                }
                else if(tokens[i] == "text"){
                    state = States::text;
                }
                else if(tokens[i] == "picture"){
                    state = States::picture;
                }
                else{
                    std::cerr<<"Invalid item type.\n";
                    state = States::error;
                }
                break;
                case States::show:
                    if (tokens[i] == "current")
                    {
                        command.set_value_of("command", "show_current");
                        state = States::end;
                    }
                    else
                    {
                        command.set_value_of("command", "show"); //needs editing
                        state = States::end;
                    }
                    break;
                case States::shape:
                    if (tokens[i] == "-line")
                    {
                        attr = Attributes::line;
                    }
                    else if (tokens[i] == "-rectangle")
                    {
                        attr = Attributes::rectangle;
                    }
                    else if (tokens[i] == "-triangle")
                    {
                        attr = Attributes::triangle;
                    }
                    else if (tokens[i] == "-circle")
                    {
                        attr = Attributes::circle;
                    }
                    else {
                        std::cerr << "Invalid shape. Available shapes are line, rectangle, square, triangle and circle\n";
                        state = States::error;
                    }
                    break;
                case States::picture:
                    command.set_value_of("picture_file", tokens[i]);
                    if (tokens[i+1] == "-width")
                        attr = Attributes::shape_width;
                    else if (tokens[i+1] == "-height")
                        attr = Attributes::shape_width;
                    else {
                        std::cerr << "Invalid option for picture. Valid options: at (optional), width, height\n";
                        state = States::error;
                    }
                    break;
                case States::text:
                    if (tokens[i] == "-value")
                    {
                        command.set_value_of("text_value", tokens[i+1]);
                    }
                    else if (tokens[i] == "-placement")
                    {
                        attr = Attributes::placement;
                    }
                    else if (tokens[i] == "-size")
                    {
                        attr = Attributes::font_size;
                    }
                    else if (tokens[i] == "-color")
                    {
                        attr = Attributes::font_color;
                    }
                    else if (tokens[i] == "-style")
                    {
                        attr = Attributes::font_family;
                    }
                    else {
                        std::cerr << "Invalid shape. Available shapes are line, rectangle, square, triangle and circle\n";
                        state = States::error;
                    }
                    break;
                case States::error:
                    throw std::exception();
                    break;
                default:
                    state = States::error;
                    attr = Attributes::none;
                    break;
            }
            ++i;
            switch (attr)
            {
            case Attributes::at:
                command.set_value_of("at", tokens[i]);
                break;
            case Attributes::line:
            case Attributes::rectangle:
            case Attributes::square:
            case Attributes::triangle:
            case Attributes::circle:
                if(tokens[i] == "-placement")
                    attr = Attributes::placement;
                else if(tokens[i] == "-length")
                    attr = Attributes::length;
                else if(tokens[i] == "-width")
                    attr = state == States::shape || state == States::picture ? 
                        Attributes::shape_width : Attributes::borderline_width;
                else if(tokens[i] == "-height")
                    attr = Attributes::shape_height;
                else if(tokens[i] == "-sides")
                    attr = Attributes::triangle_sides;
                else if(tokens[i] == "-borderline_color")
                        attr = Attributes::borderline_color;
                else if (tokens[i] == "-color")
                    attr = attr==Attributes::line ? Attributes::borderline_color :  Attributes::filling_collor; 
                else if(tokens[i] == "-angle")
                        attr = Attributes::angle;
                else if(tokens[i] == "-filled")
                        attr = Attributes::filled;
                else if(tokens[i] == "-radius")
                        attr = Attributes::circle_radius;
                else {
                    std::cerr<<"Missing or invalid attribute\n";
                    attr = Attributes::error;
                }
                break;
            case Attributes::placement:
                command.set_value_of("placement", tokens[i]);
                break;
            case Attributes::shape_height:
                command.set_value_of("", tokens[i]);
                break;
            case Attributes::shape_width:
                command.set_value_of("shape_height", tokens[i]);
                break;
            case Attributes::borderline_width:
                command.set_value_of("borderline_width", tokens[i]);
                break;
            case Attributes::borderline_color:
                command.set_value_of("borderline_color", tokens[i]);
                break;
            case Attributes::circle_radius:
                command.set_value_of("circle_radius", tokens[i]);
                break;
            case Attributes::filled:
                command.set_value_of("filled", tokens[i]);
                break;
            case Attributes::filling_collor:
                command.set_value_of("filling_collor", tokens[i]);
                break;
            case Attributes::font_color:
                command.set_value_of("font_color", tokens[i]);
                break;
            case Attributes::font_family:
                command.set_value_of("font_family", tokens[i]);
                break;
            case Attributes::font_size:
                command.set_value_of("font_size", tokens[i]);
                break;
            case Attributes::triangle_sides:
                command.set_value_of("triangle_sides", tokens[i]);
                break;
            case Attributes::length:
                command.set_value_of("length", tokens[i]);
                break;
            case Attributes::angle:
                command.set_value_of("angle", tokens[i]);
                break;
            case Attributes::error:
                throw std::exception();
            default:
                attr = Attributes::error;
                break;
            }
            
        }
        return command;
    }


};