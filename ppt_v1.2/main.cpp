#include "PPT.h"

int main(int argc, char* argv[]){
    try
    {
        std::string filePath = "";
        if (argc==2) filePath = argv[1];
        
        doc::Ppt ppt(filePath);
        
        Controller& ctrl = Controller::create(std::cin);
        ctrl.run(ppt, "cli");
        // dec::Parser parser;
        // dec::CLI_Tokenizer tokenizer;
        // dec::Token tok;
        // while (!tok.eof())
        // {
        //     tok = tokenizer.getToken();
        //     std::cout << tok.value << " " << (int)tok.type << '\n';
        // }
        
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
  
    return 0;
}
