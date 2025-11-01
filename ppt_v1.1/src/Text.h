#pragma once
#include <iostream>
#include <string>


namespace obj{
    class Text : public Object {
    public:
        Text() : Object(), value("text"), size(11), color("black"), style("arial") {}

        void create(const Position& coords){
            assert(coords.size() == 1);
            pos = coords;
        }
        void set_value(const std::string& val){
            assert(val.size() < 100);
            value = val;
        }
        void set_size(size_t size){
            if (size < 1) this->size = 1;
            else if (size > 32) this->size = 32;
            else this->size = size;
        }
        void set_style(const std::string& style){
            auto lookUp = std::find(styles.begin(), styles.end(), color);
            if (lookUp==styles.end()) throw std::runtime_error("ERROR: Color not supported\n");
            this->style = style;
        }
        void set_color(const std::string& color){
            auto lookUp = std::find(colors.begin(), colors.end(), color);
            if (lookUp==colors.end()) throw std::runtime_error("ERROR: Color not supported\n");
            this->color = color;
        }
        const std::string& get_color() const {
            return color;
        }

        const std::string& get_text() const {
            return value;
        }

        const std::string& get_style() const {
            return style;
        }
        size_t get_size() const {
            return size;
        }
        const Position& get_position() const {
            return pos;
        }
    private:
        const std::array<std::string, 4> styles = {"arial", "roberto", "sylfaen", "temes new roman"};
        
        Position pos;
        std::string value;
        size_t size;
        std::string style;
        std::string color;
    };
}; 