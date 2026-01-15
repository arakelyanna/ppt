#pragma once
#include <array>
#include <fstream>
#include "../Object.h"
#include "../Text/Text.h"
#include "../../app/files/Visitor.h"
// Forward declaration to avoid circular dependency
namespace files {
    class IVisitor;
}

namespace obj{

    class IShape : public Object { 
    public: 
        IShape();
        virtual void create(const Geometry&) = 0;
        virtual void accept(const files::IVisitor& visitor) = 0;
        virtual const Geometry& get_geometry() const;

        virtual void set_color(const std::string& color) = 0;
        virtual void set_text(const std::string& value) = 0;
        virtual void set_text_size(const size_t value) = 0;
        virtual void set_text_color(const std::string& value) = 0;
        virtual void set_text_style(const std::string& value) = 0;
        
        virtual const std::string& get_type() const = 0;

        virtual const std::string& get_text() const = 0;
        virtual size_t get_text_size() const = 0;
        virtual const std::string& get_text_color() const = 0;
        virtual const std::string& get_text_style() const = 0;
        virtual const std::string& get_color() const = 0;
        virtual ~IShape(){}
    protected: 
        Geometry pos; 
        std::string color;
        double borderline_width;
        Text text;
    };

    class FilledShapes: public IShape{
    public: 
        FilledShapes();
        void create(const Geometry&) override = 0;
        void accept(const files::IVisitor& visitor) override = 0;
        void set_color(const std::string& color) override;
        void set_line_color(const std::string& color);
        void set_line_width(double width);
        void set_filled(bool fill);
        void set_text(const std::string& value) override;
        void set_text_size(const size_t value) override;
        void set_text_color(const std::string& value) override;
        void set_text_style(const std::string& value) override;
    
        virtual const std::string& get_type() const override = 0;
        const std::string& get_text() const override;
        size_t get_text_size() const override;
        const std::string& get_text_color() const override;
        const std::string& get_text_style() const override;
        const std::string& get_color() const override;
        const std::string& get_line_color() const;
        double get_line_width() const;
        bool is_filled() const;
        virtual ~FilledShapes(){}
    protected:
        bool filled;
        std::string borderline_color;
    };
    
    class Circle : public FilledShapes
    {
    public:
        Circle();
        void create(const Geometry& coords) override;
        void accept(const files::IVisitor& visitor) override;
        const std::string& get_type() const override;
        void set_radius(double);
        double get_radius() const;
    private:
        double radius;
    };
    
    class Rectangle : public FilledShapes
    {
    public:
        Rectangle();
        void create(const Geometry& coords) override;
        void accept(const files::IVisitor& visitor) override;
        const std::string& get_type() const override;
        double get_height() const;
        double get_width() const;
        void set_height(double value);
        void set_width(double value);
    protected:
        double height;
        double width;
    };

    class Picture : public FilledShapes {
    public:
        Picture(const std::string& file = "./pic.png");
        
        void create(const Geometry& coords) override;
        void accept(const files::IVisitor& visitor) override;
        const std::string& get_type() const override;
        const std::string& get_path() const;
        void set_color(const std::string& color) override;
        double get_height() const;
        double get_width() const;
        void set_height(double value);
        void set_width(double value);
        
    private:
        std::fstream pic;
        std::string path;
        double height;
        double width;
    };


    class Square : public FilledShapes{
    public:
        Square();
        void create(const Geometry& coords) override;
        void accept(const files::IVisitor& visitor) override;
        const std::string& get_type() const override;
        double get_side() const;
        void set_side(double value);
    private:
        double side;
    };

    class Triangle : public FilledShapes{
    public:
        Triangle();
        void create(const Geometry& coords) override;
        void accept(const files::IVisitor& visitor) override;
        const std::string& get_type() const override;
        const std::array<double, 3>& get_sides() const;
    private:
        std::array<double, 3> sides;
    };

    class LinedShapes : public IShape {
    public:
        LinedShapes() : IShape(), length(0), width(0) {}

        void create(const Geometry&) override = 0;
        void accept(const files::IVisitor& visitor) override = 0;
        
        virtual void set_width(double) = 0;
        void set_color(const std::string& color) override;
        void set_text(const std::string& value) override;
        void set_text_size(const size_t value) override;
        void set_text_color(const std::string& value) override;
        void set_text_style(const std::string& value) override;
    
        virtual const std::string& get_type() const override = 0;
        const std::string& get_text() const override;
        size_t get_text_size() const override;
        const std::string& get_text_color() const override;
        const std::string& get_text_style() const override;
        const std::string& get_color() const override;
        virtual double get_length() const = 0;
        virtual double get_width() const = 0;
        virtual ~LinedShapes(){}
    protected:
        double length;
        double width;
    };

    class Line : public LinedShapes{
    public:
        Line() : LinedShapes() {}
        void create(const Geometry& coords) override;
        void accept(const files::IVisitor& visitor) override;
        void set_width(double) override;
        const std::string& get_type() const override;
        double get_length() const override;
        double get_width() const override;

    };

    class Arrow : public Line{
    public:
        Arrow();
        void create(const Geometry& coords) override;
        void accept(const files::IVisitor& visitor) override;
        const std::string& get_type() const override;
        const std::string& points_to() const;
        void point_other_way();
    private:
        std::string pointing;
    };
}