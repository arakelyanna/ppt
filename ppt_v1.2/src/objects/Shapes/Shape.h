#pragma once
#include <array>
#include "../Object.h"
#include "../Text/Text.h"

namespace obj{
    class IShape : public Object { 
    public: 
        IShape();
        virtual void create(const Position&) = 0;
        virtual void show() const override = 0;

        virtual void set_color(const std::string& color) = 0;
        virtual void set_text(const std::string& value) = 0;
        virtual const std::string& get_text() const = 0;
        virtual const std::string& get_color() const = 0;
        virtual ~IShape(){}
    protected: 
        Position pos; 
        std::string color;
        double borderline_width;
        Text text;
    };

    class FilledShapes: public IShape{
    public: 
        FilledShapes();
        virtual void create(const Position&) override = 0;
        virtual void show() const override = 0;

        virtual void set_color(const std::string& color) override;
        virtual void set_line_color(const std::string& color);
        virtual void set_line_width(double width);
        virtual void set_filled(bool fill);
        virtual void set_text(const std::string& value) override;

        virtual const std::string& get_text() const override;
        virtual const std::string& get_color() const override;
        virtual const std::string& get_line_color() const;
        virtual double get_line_width() const;
        virtual bool is_filled() const;
        virtual ~FilledShapes(){}
    protected:
        bool filled;
        std::string borderline_color;
    };
    
    class Circle : public FilledShapes
    {
    public:
        Circle();
        void create(const Position& coords) override;
        void show() const override;
        void set_radius(double);
        double get_radius() const;
    private:
        double radius;
    };
    
    class Rectangle : public FilledShapes
    {
    public:
        Rectangle();
        void create(const Position& coords) override;
        void show() const override;
        double get_height() const;
        double get_width() const;
        void set_height(double value);
        void set_width(double value);
    protected:
        double height;
        double width;
    };

    class Square : public FilledShapes{
    public:
        Square();
        void create(const Position& coords) override;
        void show() const override;
        double get_side() const;
        void set_side(double value);
    private:
        double side;
    };

    class Triangle : public FilledShapes{
    public:
        Triangle();
        void create(const Position& coords) override;
        void show() const override;
        const std::array<double, 3>& get_sides() const;
    private:
        std::array<double, 3> sides;
    };

    class LinedShapes : public IShape {
    public:
        LinedShapes() : IShape(), length(0), width(0) {}
        void create(const Position&) override = 0;
        virtual void show() const override = 0;
        
        void set_color(const std::string& color) override;
        virtual void set_text(const std::string& value) override;
        virtual void set_width(double);

        virtual const std::string& get_text() const override;
        const std::string& get_color() const override;
        virtual double get_length() const;
        virtual double get_width() const;
        virtual ~LinedShapes(){}
    protected:
        double length;
        double width;
    };

    class Line : public LinedShapes{
    public:
        Line() : LinedShapes() {}
        void show() const override;
        void create(const Position& coords) override;
        void set_width(double) override;
        double get_length() const override;
        double get_width() const override;

    };

    class Arrow : public Line{
    public:
        Arrow();
        void show() const override;
        void create(const Position& coords) override;
        const std::string& points_to() const;
        void point_other_way();
    private:
        std::string pointing;
    };
}