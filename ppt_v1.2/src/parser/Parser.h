#pragma once
#include <memory>
#include <array>
#include <algorithm>
#include <memory>
#include <istream>
#include "Tokenizer.h"
#include "../app/cmd/CmdRegister/CmdRegister.h"
#include "../app/cmd/CmdCreator/CmdCreator.h"

namespace dec{
    
    enum class State {Start, Command, Argument, Value, Err, End}; // Args : -opt, Value: number, boolean, string, Coord
    
    
    class Parser
    {
    public:
        Parser(std::shared_ptr<doc::Ppt> ppt, std::istream& input=std::cin) 
            : tokenizer(input), cmd_register(ppt) {
            init_transition();
        }
        
        std::unique_ptr<cmd::I_Command> parse();

    private:
        void init_transition();
        void process(Token& tok);

    private:
        using TransitionTable = std::array<std::array<State, 25>, 25>;
        TransitionTable transition;

        CLI_Tokenizer tokenizer;

        cmd::CmdRegister cmd_register;
        std::unique_ptr<cmd::I_CmdCreator> cmd_creator;
        
        State currentState;

        std::string command_name = "";
        std::string key = "";
        
        std::vector<obj::Coord> coord_buffer;
    };
}