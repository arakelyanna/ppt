#include "PPT.h"
#include <memory>

int main(int argc, char* argv[]){
    auto& app = app::Application::create(argc, argv);
    app.run();
}
