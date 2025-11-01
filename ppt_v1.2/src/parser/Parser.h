#pragma once
#include <memory>
#include <array>
#include "Tokenizer.h"
#include "../app/cmd/Command.h"

namespace dec{
    
    enum class State {Start, Command, Option, Args, String, Number, Boolean, Coord, Err, Eof}; // Args = {Slide, Shape, .....}
    
    
    class Parser
    {
    public:
        Parser(std::istream& input):tokenizer(input) {
            init_transition();
        }
        Parser():tokenizer(std::cin){
            init_transition();
        }
        
        std::unique_ptr<cmd::I_Command> parse();

    private:
        void init_transition();

    private:
        CLI_Tokenizer tokenizer;
        cmd::Value val = "";
        using TransitionTable = std::array<std::array<State, 25>, 25>;
        TransitionTable transition;
    };


}