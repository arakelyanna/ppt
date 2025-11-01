#include "Text.h"

namespace obj {
    Text::Text() : Object(), value("text"), size(11), color("black"), style("arial") {}
    
    Text::Text(const std::string& value, size_t size, const std::string& color, const std::string& style) :
        Object(), value(value), size(size), color(color), style(style) {}

    void Text::create(const Position& coords) {
        assert(coords.size() == 1);
        pos = coords;
    }

    void Text::set_value(const std::string& val) {
        assert(val.size() < 100);
        value = val;
    }

    void Text::set_size(size_t size) {
        if (size < 1) this->size = 1;
        else if (size > 32) this->size = 32;
        else this->size = size;
    }

    void Text::set_style(const std::string& value) {
        auto lookUp = std::find(styles.begin(), styles.end(), value);
        if (lookUp == styles.end()) throw std::runtime_error("ERROR: Color not supported\n");
        this->style = value;
    }

    void Text::set_color(const std::string& value) {
        auto lookUp = std::find(colors.begin(), colors.end(), value);
        if (lookUp == colors.end()) throw std::runtime_error("ERROR: Color not supported\n");
        this->color = value;
    }

    const std::string& Text::get_color() const {
        return color;
    }

    const std::string& Text::get_text() const {
        return value;
    }

    const std::string& Text::get_style() const {
        return style;
    }

    size_t Text::get_size() const {
        return size;
    }

    const Position& Text::get_position() const {
        return pos;
    }

    void Text::show() const {
        std::cout<< "Text at (" << pos[0].first << ", " << pos[0].second << ") with\n" <<
            "\ntext: " << value <<
            "\nstyle: " << size<<
            "\ncolor: " << color<<
            "\nstyle: " << style<<
            "\n---------------------\n";
    }


}