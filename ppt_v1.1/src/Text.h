#pragma once
#include <iostream>
#include <string>


namespace obj{
    class Text{
    public:
        Text(const std::string& val = "text", size_t size = 11, const std::string& style = "arial", const std::string& color = "black") :
         value(val), size(size), color(color), style(style) {}
        

        void setValue(const std::string& val){
            value = val;
        }
        void setSize(size_t size){
            this->size = size;
        }
        void setStyle(const std::string& style){
            this->style = style;
        }
        void setColor(const std::string& color){
            this->color = color;
        }
    private:
        std::string value;
        size_t size;
        std::string style;
        std::string color;
    };
};