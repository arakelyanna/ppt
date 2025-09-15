#include <iostream>
#include <fstream>
#include "Tokenizer.h"
#include "Fetcher.h"
#include "Parser.h"


int main(int argc, char* argv[]){
    std::string user_input;
    std::fstream file;

    try {
        if (!argv[1]) {
            std::cout << "No file opened.";
        }
        else {
            file.open(argv[1]);
        }

        std::cout << "\n(ppt)# ";
        Fetcher commands("commands.txt");

        while(1){
            auto user_input = commands.next_line();
            if(!user_input){
                continue;
            }
            Tokenizer tok(user_input.value());
            //Parser parser(tok.tokenize());
            
            if (user_input=="q" || user_input=="exit")
            {
                std::cout << "Quit...\n";
                break;
            }
            
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }







    return 0;
}