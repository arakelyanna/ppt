#pragma once
#include <istream>
#include <memory>
#include "../parser/Parser.h"
#include "cmd/Command.h"
#include "doc/Presentation.h"
#include "viewer/Viewer.h"

class Controller{
private:
    Controller(std::istream& input) : parser(input) {}

public:
    Controller(const Controller&) = delete;
    Controller& operator=(const Controller&) = delete;
    Controller(Controller&&) = delete;
    Controller& operator=(Controller&&) = delete;

    static Controller& create(std::istream& input) {
        static Controller instance(input);
        return instance;
    }


    void run(doc::Ppt& ppt,const std::string& viewer){
        while (true)
        {
            command = parser.parse();
            command->set_viewer(viewer);
            if (!command->execute()) {
                std::cout << "Exiting program...\n";
                break;
            }
        }
        
    }
private:
    std::unique_ptr<cmd::I_Command> command;
    dec::Parser parser;
};