#pragma once
#include "../parser/Parser.h"
#include "cmd/Commands/Command.h"
#include "doc/ppt/Presentation.h"

namespace app {
    class Controller{
    public:
        Controller(std::istream& input, std::shared_ptr<doc::Ppt> ppt)
            : parser(ppt, input) {}

        Controller(const Controller&) = delete;
        Controller& operator=(const Controller&) = delete;
        Controller(Controller&&) = delete;
        Controller& operator=(Controller&&) = delete;


        void run(){
            while (true)
            {
                try{
                    std::cout << "(ppt) ";
                    command = parser.parse();
                    if(!command) {
                        continue;
                    }
                    else if (!command->execute(std::cout)) {
                        break;
                    }

                }
                catch(const std::exception& e)
                {
                    std::cerr << e.what() << '\n';
                    continue;
                }
                std::cout << '\n';
            }
        }
    private:
        std::unique_ptr<cmd::I_Command> command;
        dec::Parser parser;
        std::string path;
    };
}