#pragma once
#include <iostream>
#include <string>

namespace obj{
    class IShape{
    public:
        virtual void draw() = 0;
        virtual void create() = 0;
    };

    class Circle : public IShape
    {
    public:
        Circle() = default;
        void draw() override {
            std::cout << "drew a Circle.'\n";
        }
        void create() override{
            std::cout << "created a Circle.'\n";
        }
    private:
        size_t radius;
        std::string color;
    };
    
    class Square : public IShape
    {
    public:
        Square() = default;
        void draw() override {
            std::cout << "drew a Square.'\n";
        }
        void create() override{
            std::cout << "created a Square.'\n";
        }
    private:
        size_t side;
        std::string color;
    };
}