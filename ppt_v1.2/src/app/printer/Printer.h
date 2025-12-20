#pragma once
#include "../doc/ppt/Presentation.h"

namespace out{
    class IPrinter
    {
    public:
        IPrinter() = default;
        IPrinter(std::shared_ptr<doc::Ppt> ppt) : ppt(ppt) {}
        virtual void print() = 0;
        virtual void printObj(std::shared_ptr<obj::Object> obj) = 0;
    private:
        std::shared_ptr<doc::Ppt> ppt;
    };

    class CLIPrinter : public IPrinter{
    public:
        CLIPrinter(std::shared_ptr<doc::Ppt> ppt, std::ostream& output) : IPrinter(ppt), output(output){}
        void print() override = 0;
        virtual void printObj(std::shared_ptr<obj::Object> obj) = 0;
    protected:
        std::ostream& output;
    };

    class SVGPrinter : public IPrinter{
    public:
        SVGPrinter(std::shared_ptr<doc::Ppt> ppt) : IPrinter(ppt){}
        void print() override = 0;
        virtual void printObj(std::shared_ptr<obj::Object> obj) = 0;
    };
}