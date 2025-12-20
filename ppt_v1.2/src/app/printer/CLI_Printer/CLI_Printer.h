#pragma once
#include "../Printer.h"

namespace out {
    class RectanglePrinter : public CLIPrinter{
    public:
        RectanglePrinter(std::shared_ptr<doc::Ppt> ppt, std::ostream& output = std::cout):CLIPrinter(ppt, output){} 
        void print() override;
        void printObj(std::shared_ptr<obj::Object> obj)override;

    };

    class CirclePrinter : public CLIPrinter{
    public:
        CirclePrinter(std::shared_ptr<doc::Ppt> ppt, std::ostream& output = std::cout) : CLIPrinter(ppt, output){} 
        void print() override;
        void printObj(std::shared_ptr<obj::Object> obj)override;
    };

    class SquarePrinter : public CLIPrinter{
    public:
        SquarePrinter(std::shared_ptr<doc::Ppt> ppt, std::ostream& output = std::cout):CLIPrinter(ppt, output){} 
        void print() override;
        void printObj(std::shared_ptr<obj::Object> obj)override;
    };

    class TrianglePrinter : public CLIPrinter{
    public:
        TrianglePrinter(std::shared_ptr<doc::Ppt> ppt, std::ostream& output = std::cout):CLIPrinter(ppt, output){} 
        void print() override;
        void printObj(std::shared_ptr<obj::Object> obj)override;
    };

    class LinePrinter : public CLIPrinter{
    public:
        LinePrinter(std::shared_ptr<doc::Ppt> ppt, std::ostream& output = std::cout):CLIPrinter(ppt, output){} 
        void print() override;
        void printObj(std::shared_ptr<obj::Object> obj)override;
    };

    class ArrowPrinter : public CLIPrinter{
    public:
        ArrowPrinter(std::shared_ptr<doc::Ppt> ppt, std::ostream& output = std::cout):CLIPrinter(ppt, output){} 
        void print() override;
        void printObj(std::shared_ptr<obj::Object> obj)override;
    };

    class TextPrinter : public CLIPrinter{
    public:
        TextPrinter(std::shared_ptr<doc::Ppt> ppt, std::ostream& output = std::cout):CLIPrinter(ppt, output){} 
        void print() override;
        void printObj(std::shared_ptr<obj::Object> obj)override;
    };

    class PicturePrinter : public CLIPrinter{
    public:
        PicturePrinter(std::shared_ptr<doc::Ppt> ppt, std::ostream& output = std::cout):CLIPrinter(ppt, output){} 
        void print() override;
        void printObj(std::shared_ptr<obj::Object> obj) override;
    };
}