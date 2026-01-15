#include "Controller.h"
#include <memory>

namespace app {
    class Application {
    private:
        Application(int argc, char* argv[]) : argc(argc), argv(argv) {}
    public:
        
        static Application& create(int argc, char* argv[]) {
            static Application instance(argc, argv);
            return instance;
        }
        void run(){
            try
            {
                std::string filePath = "";
                if (argc==2) filePath = argv[1];

                auto ppt = std::make_shared<doc::Ppt>(filePath);
                Controller ctrl(std::cin, ppt);

                ctrl.run();
            }
            catch(const std::exception& e)
            {
                std::cerr << e.what() << '\n';
            }
        }
    private:
        int argc; 
        char** argv;
    };
    
}