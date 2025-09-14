#include <iostream>
#include "Tokenizer.h"
#include "Fetcher.h"
#include "Parser.h"


int main(int argc, char* argv[]){
    std::string user_input;
    
    if (!argv[1]) {
        std::cout << "No file opened.";
    }
    try {
        std::cout << "\n(ppt)# ";
        // std::cin >> user_input;
        Fetcher file(argv[1]);
        while(1){
            auto user_input = file.next_line();
            if(!user_input){
                continue;
            }
            Tokenizer tok(user_input.value());
            //Parser parser(tok.tokenize());
            // AAAAAAAAaystex karox e linel dzer govazdy.




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