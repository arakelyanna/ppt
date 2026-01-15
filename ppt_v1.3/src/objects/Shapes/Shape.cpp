#include <algorithm>
#include "Shape.h"

namespace obj{

    IShape::IShape() : color("black"), borderline_width(1), text("text") { 
        pos.assign({{0, 0}, {0, 0}}); 
    }

    const Geometry& IShape::get_geometry() const {
        return pos;
    }

    FilledShapes::FilledShapes() : IShape(), filled(true), borderline_color("black"){}

    void FilledShapes::set_color(const std::string& color) {
        auto lookUp = std::find(colors.begin(), colors.end(), color);
        if (lookUp==colors.end()) throw std::runtime_error("(object) ERROR: Color not supported\n");
        this->color = color;
    }

    void FilledShapes::set_line_color(const std::string& color) {
        auto lookUp = std::find(colors.begin(), colors.end(), color);
        if (lookUp==colors.end()) throw std::runtime_error("(object) ERROR: Color not supported\n");
        borderline_color = color;
    }

    void FilledShapes::set_line_width(double width){
        if (width < 0) borderline_width = 0;
        else if (width > 5) borderline_width = 5;
        else borderline_width = width;
    }

    void FilledShapes::set_filled(bool fill) {
        filled = fill;   
    }
    const std::string& FilledShapes::get_text() const {
        return text.get_text();
    }
    void FilledShapes::set_text(const std::string& value) {
        text.set_value(value);
    }
    void FilledShapes::set_text_size(const size_t value) {
        text.set_size(value);

    }

    void FilledShapes::set_text_color(const std::string& value) {
        text.set_color(value);

    }

    void FilledShapes::set_text_style(const std::string& value) {
        text.set_style(value);

    }


    size_t FilledShapes::get_text_size() const {
        return text.get_size();

    }

    const std::string& FilledShapes::get_text_color() const {
        return text.get_color();

    }

    const std::string& FilledShapes::get_text_style() const {
        return text.get_style();

    }
    const std::string& FilledShapes::get_color() const {
        return color;
    }
    const std::string& FilledShapes::get_line_color() const {
        return borderline_color;
    }

    bool FilledShapes::is_filled() const {
        return filled;
    }

    double FilledShapes::get_line_width() const {
        return borderline_width;
    }

    void LinedShapes::set_color(const std::string& color) {
        auto lookUp = std::find(colors.begin(), colors.end(), color);
        if (lookUp==colors.end()) throw std::runtime_error("(object) ERROR: Color not supported\n");
        this->color = color;
    }

    void LinedShapes::set_width(double width){
        if (width < 0) borderline_width = 0;
        else if (width > 5) borderline_width = 5;
        else borderline_width = width;
    }

    void LinedShapes::set_text(const std::string& value) {
        text.set_value(value);
    }

    const std::string& LinedShapes::get_text() const {
        return text.get_text();
    }
    void LinedShapes::set_text_size(const size_t value) {
        text.set_size(value);

    }

    void LinedShapes::set_text_color(const std::string& value) {
        text.set_color(value);

    }

    void LinedShapes::set_text_style(const std::string& value) {
        text.set_style(value);

    }


    size_t LinedShapes::get_text_size() const {
        return text.get_size();

    }

    const std::string& LinedShapes::get_text_color() const {
        return text.get_color();

    }

    const std::string& LinedShapes::get_text_style() const {
        return text.get_style();

    }

    double LinedShapes::get_length() const{
        return length;
    }

    double LinedShapes::get_width() const{
        return borderline_width;
    }

    
    const std::string& LinedShapes::get_color() const {
        return color;
    }

}
