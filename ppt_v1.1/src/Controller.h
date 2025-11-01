#pragma once
#include "Parser.h"
#include "Command.h"
#include "Presentation.h"

class Controller{
public:
    Controller(){}
    bool run(doc::Ppt& ppt){
        std::string line;
        dec::Parser parser(std::cin);
        while (true)
        {
            std::unique_ptr<cmd::ICommand> command = parser.parse();
            command->execute();
        }
        
    }
private:
};