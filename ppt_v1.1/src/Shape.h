#pragma once
#include <array>
#include "Object.h"

namespace obj{

    const std::array<std::string, 7> colors = {"red", "blue", "black", "yellow", "green", "purple", "white"};
    
    class IShape : public Object { 
    public: 
        IShape();
        virtual void create(const Position&) = 0; 

        virtual void set_color(const std::string&)=0;

        virtual void set_line_color(const std::string&){}
        virtual void set_line_width(double){}
        virtual void set_filled(bool) {}

        virtual const std::string& get_color() const { return color; } 
        virtual const Position& get_position() const { return pos; }

        virtual const std::string& get_line_color(const std::string&) const {}
        virtual double get_line_width (const std::string&) const {}
        virtual bool is_filled() const {}
        virtual void draw() = 0; 
    protected: 
        Position pos; 
        std::string color; 
    };

    class FilledShapes: public IShape{
    public: 
        FilledShapes();

        virtual void set_color(const std::string& color);
        virtual void set_line_color(const std::string& color);
        virtual void set_line_width(double width);
        virtual void set_filled(bool fill);
        virtual const std::string& get_line_color() const;
        virtual bool is_filled() const;
        virtual const double get_line_width() const;
    protected:
        bool filled;
        std::string borderline_color;
        double borderline_width;
    };
    
    class Circle : public FilledShapes
    {
    public:
        Circle();
        void draw() override;
        void create(const Position& coords) override;
        double get_radius() const;
    private:
        double radius;
    };
    
    class Rectangle : public FilledShapes
    {
    public:
        Rectangle();
        void create(const Position& coords) override;
        double get_height() const;
        double get_width() const;
        void draw() override;
    protected:
        double height;
        double width;
    };

    class Square : public FilledShapes{
    public:
        Square();
        void create(const Position& coords) override;
        double get_side() const;
    private:
        Rectangle rect;
    };

    class Triangle : public FilledShapes{
    public:
        Triangle();
        void create(const Position& coords) override;
        const std::array<double, 3>& get_sides() const;
    private:
        std::array<double, 3> sides;
    };

    class Line : public IShape{
    public:
        Line();
        void create(const Position& coords);
        double get_length() const;
        double get_width() const;
    private:
        double length;
        double width;
    };

    class Arrow : public Line{
    public:
        Arrow();
        const Coord& points_to();
        void point_other_way();
    private:
        Coord pointing;
    };
}