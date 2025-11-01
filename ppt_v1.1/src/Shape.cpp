#include <iostream>
#include <algorithm>
#include <cmath>
#include <cassert>
#include "Shape.h"

namespace obj{

    IShape::IShape() : color("black") { 
        pos.assign({{0, 0}, {0, 0}}); 
    }

    FilledShapes::FilledShapes() : IShape(), filled(true), borderline_color("black"), borderline_width(1){}

    void FilledShapes::set_color(const std::string& color) {
        auto lookUp = std::find(colors.begin(), colors.end(), color);
        if (lookUp==colors.end()) throw std::runtime_error("ERROR: Color not supported\n");
        this->color = color;
    }

    void FilledShapes::set_line_color(const std::string& color) {
        auto lookUp = std::find(colors.begin(), colors.end(), color);
        if (lookUp==colors.end()) throw std::runtime_error("ERROR: Color not supported\n");
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

    const std::string& FilledShapes::get_line_color() const {
        return borderline_color;
    }

    bool FilledShapes::is_filled() const {
        return filled;
    }

    const double FilledShapes::get_line_width() const {
        return borderline_width;
    }

    Circle::Circle() : FilledShapes(), radius(1){
        pos={{0, 0}};
    }

    void Circle::draw() {
        std::cout << "drew a Circle.'\n";
    }

    void Circle::create(const Position& coords) {
        assert(coords.size() == 2 && (pos[0].first - pos[1].first) == (pos[0].second - pos[1].second));
        pos = coords;
        radius = (pos[0].first - pos[1].first)/2;
    }

    double Circle::get_radius() const {
        return radius;
    }

    Rectangle::Rectangle() : FilledShapes(), height(1), width(1){
        pos={{0, 0}, {1, 1}};
    }

    void Rectangle::create(const Position& coords) {
        assert(coords.size() == 2);
        pos = coords;
        width= std::abs(pos[0].first-pos[1].first);
        height= std::abs(pos[0].second-pos[1].second);
    }

    double Rectangle::get_height() const {
        return height;
    }

    double Rectangle::get_width() const {
        return height;
    }

    void Rectangle::draw() {
        std::cout << "drew a Rectangle.'\n";
    }

    Square::Square() : FilledShapes(){ }

    void Square::create(const Position& coords) {
        assert(coords.size() == 2 && (pos[0].first - pos[1].first) == (pos[0].second - pos[1].second));
        rect.create(coords);
    }

    double Square::get_side() const {
        return rect.get_width();
    }

    Triangle::Triangle() : FilledShapes() {
        pos={{0, 0}, {1, 1}, {0, 1}};
    }

    void Triangle::create(const Position& coords) {
        assert(coords.size() == 3);
        pos = coords;
        sides[0] = std::sqrt(std::pow(pos[0].first-pos[1].first, 2)+std::pow(pos[0].second-pos[1].second, 2));
        sides[1] = std::sqrt(std::pow(pos[1].first-pos[2].first, 2)+std::pow(pos[1].second-pos[2].second, 2));
        sides[2] = std::sqrt(std::pow(pos[2].first-pos[0].first, 2)+std::pow(pos[2].second-pos[0].second, 2));
    }

    const std::array<double, 3>& Triangle::get_sides() const {
        return sides;
    }

    Line::Line():IShape(), width(0){
        pos={{0, 0}, {0, 1}};
    }

    void Line::create(const Position& coords){
        assert(coords.size() == 2);
        pos = coords;
        length =  std::sqrt(std::pow(pos[0].first-pos[1].first, 2)+std::pow(pos[0].second-pos[1].second, 2));
    }

    double Line::get_length() const {
        return length;
    }

    double Line::get_width() const {
        return width;
    }

    Arrow::Arrow():Line(){
        pointing = pos[1];
    }

    const Coord& Arrow::points_to(){
        return pointing;
    }

    void Arrow::point_other_way(){
        std::swap(pos[0], pos[1]);
    }

}