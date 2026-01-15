#pragma once
#include <string>
#include <iostream>
#include <unordered_map>
#include <functional>

namespace cmd {
    
    class MetaCmd {
    public:
        MetaCmd() {
            help["add slide"] = [](std::ostream& output) {
                output << "add slide -at <pos>\n";
                output << "\t-at is an OPTIONAL Argument, if not specified the slide is added at the front\n";
                output << "\t<pos> is a positive integer\n";
            };
            
            help["remove slide"] = [](std::ostream& output) {
                output << "remove slide -at <pos>\n";
                output << "\t-at is an OPTIONAL argument, if not specified the slide is removed from the front\n";
                output << "\t<pos> is a positive integer\n";
            };
            
            help["current slide"] = [](std::ostream& output) {
                output << "current slide\n";
                output << "\tprints in command line the slide you are currently working on\n";
            };
            
            help["set current slide"] = [](std::ostream& output) {
                output << "set current slide -at <pos>\n";
                output << "\tchanges the current slide you are currently working on to the slide at the specified position (id)\n";
                output << "\t-at is a REQUIRED argument, if not specified an exception is thrown\n";
            };
            
            help["add shape"] = [](std::ostream& output) {
                output << "add shape -<shape_type> -pos <Coord> ...\n";
                output << "\t-pos is a REQUIRED Argument, gets different numbers of Coord depending on the <shape_type>\n";
                output << "\t<Coord> is a pair of real numbers, showing a point in 2D dimension: e.g. (0, 0)\n";
                output << "---\n";
                output << "\tAvailable shapes:\n";
                output << "\t\tFilled Shapes: all filled shapes have these optional arguments:\n";
                output << "\t\t\tcolor: the filling color of the shape\n";
                output << "\t\t\tline_color: the borderline color of the shape\n";
                output << "\t\t\tline_width: the borderline width of the shape\n";
                output << "\t\t\ttext: the text value within the shape\n";
                output << "\t\t\t\tRectangle: requires 2 coordinates as its geometry\n";
                output << "\t\t\t\tTriangle: requires 3 coordinates as its geometry\n";
                output << "\t\t\t\tCircle: requires 2 coordinates as its geometry (the coordinates should form a square: (x, y) (y, x))\n";
                output << "\t\t\t\tSquare: requires 2 coordinates as its geometry (the coordinates should form a square: (x, y) (y, x))\n";
                output << "\t\tLined Shapes: all lined shapes have these optional arguments:\n";
                output << "\t\t\tcolor: the color of the shape\n";
                output << "\t\t\tline_width: the width of the shape\n";
                output << "\t\t\ttext: the text value within the shape\n";
                output << "\t\t\t\tLine: requires 2 coordinates as its geometry\n";
                output << "\t\t\t\tArrow: requires 2 coordinates as its geometry\n";
                output << "\tAll non-numeral values are given through strings in double quotes \"\"\n";
            };
            
            help["add text"] = [](std::ostream& output) {
                output << "add text -text \"<string value>\" -pos <Coord>\n";
                output << "\t-pos: a REQUIRED Argument, gets 1 coordinate\n";
                output << "\t<Coord> is a pair of real numbers, showing a point in 2D dimension: e.g. (0, 0)\n";
                output << "\t-text: a REQUIRED Argument, the text value\n";
                output << "\tOptional Arguments:\n";
                output << "\t\tcolor: the color of the text\n";
                output << "\t\tstyle: the style of the text (arial, roberto, sylfaen, times new roman)\n";
                output << "\t\tsize: the size of the text (1-500)\n";
            };
            
            help["add picture"] = [](std::ostream& output) {
                output << "add picture -file \"path/to/the/picture\" -pos <Coord> <Coord>\n";
                output << "\t-file: a REQUIRED Argument, path to the image file\n";
                output << "\t-pos: a REQUIRED Argument, gets 2 coordinates\n";
                output << "\t<Coord> is a pair of real numbers, showing a point in 2D dimension: e.g. (0, 0)\n";
                output << "\tOptional Arguments:\n";
                output << "\t\tline_color: the borderline color of the picture\n";
                output << "\t\tline_width: the borderline width of the picture\n";
                output << "\t\ttext: the text value on the picture\n";
                output << "\tAll non-numeral values are given through strings in double quotes \"\"\n";
            };
            
            help["remove object"] = [](std::ostream& output) {
                output << "remove object -at <Coord>\n";
                output << "\t-at: REQUIRED argument, removes the object that falls under that coordinate\n";
                output << "\t<Coord> is a pair of real numbers, showing a point in 2D dimension: e.g. (0, 0)\n";
            };
            
            help["save"] = [](std::ostream& output) {
                output << "save -file \"path/to/the/file\"\n";
                output << "\t-file: optional argument, if not specified it will search for a folder 'ztest' and save the file named 'ppt_test' there\n";
            };
            
            help["open"] = [](std::ostream& output) {
                output << "open -file \"path/to/the/file\"\n";
                output << "\t-file: optional argument, if not specified it will search for a folder 'ztest' and open the file named 'ppt_test' there\n";
            };
            
            help["draw"] = [](std::ostream& output) {
                output << "draw\n";
                output << "\tdraws and creates SVG files in the current directory with names 'slide_<slide_id>.svg'\n";
            };
            
            help["draw slide"] = [](std::ostream& output) {
                output << "draw slide -at <pos>\n";
                output << "\tdraws the specified slide as an SVG file\n";
                output << "\t-at is an OPTIONAL Argument and takes a non-negative integer, if not specified the first slide will be drawn\n";
            };
            
            help["show"] = [](std::ostream& output) {
                output << "show\n";
                output << "\tprints the whole presentation in CLI\n";
            };
            
            help["show slide"] = [](std::ostream& output) {
                output << "show slide -at <pos>\n";
                output << "\tprints the specified slide in CLI\n";
                output << "\t-at is an OPTIONAL Argument and takes a non-negative integer, if not specified the first slide will be printed\n";
            };
            
            help["undo"] = [](std::ostream& output) {
                output << "undo\n";
                output << "\treverts the last action performed\n";
            };
            
            help["redo"] = [](std::ostream& output) {
                output << "redo\n";
                output << "\treapplies the last undone action\n";
            };
            
            help["exit"] = [](std::ostream& output) {
                output << "exit\n";
                output << "\tquits the application\n";
            };
        }
        
        void showHelp(std::ostream& output, const std::string& cmd_name) const {
            auto it = help.find(cmd_name);
            if (it != help.end()) {
                it->second(output);
            } else {
                output << "No such command: " << cmd_name << "\n";
                output << "The syntax for help is:\n\thelp -cmd \"<command name>\"\n";
                listCommands(output);
            }
        }

        void listCommands(std::ostream& output) const {
            output << "Available commands:\n";
            for (const auto& [cmd, _] : help) {
                output << "\t- " << cmd << "\n";
            }
        }
        
    private:
        std::unordered_map<std::string, std::function<void(std::ostream&)>> help;
    };
    
} 