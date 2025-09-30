#pragma once
#include <string>
#include "Tokenizer.h"
#include "Command.h"

namespace prs{
    class Parser
    {
    public:
        Parser(std::istream& input) : tokenizer(input) {}

        const Command& parse(const Token& token);

        const std::string& parse_command();
        const std::string& parse_string();
        const std::string& parse_option();
        double parse_number();
        bool parse_bool();

    private:
        Tokenizer tokenizer;
        Command command;
    };


}