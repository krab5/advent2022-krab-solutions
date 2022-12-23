#ifndef SVGPRINTER_H
#define SVGPRINTER_H

#include <ostream>
#include <string>
#include <deque>
#include <vector>
#include "point.h"

namespace svg {

using common::point;

class printer {
    public:
        struct style {
            std::string stroke_color;
            std::string stroke_width;
            std::string stroke_dash;
            std::string fill_color;
            float opacity;

            style();

            void render(std::ostream& out) const;

            static const style no_style;
            static style fill(const char* color, float opacity = -1.0);
            static style stroke(const char* color, const char* width = "", const char* dash = "", float opacity = -1.0);
        };
        struct element { 
            style the_style;
            element(const style& s = style::no_style);

            virtual point bottom_left() const = 0;
            virtual point top_right() const = 0;
            virtual void render(std::ostream& out, float scale, const std::string& indent) const = 0; 
        };
        struct rect: public element {
            point corner;
            point size;

            rect(const point& c, const point& s, const style& st = style::no_style);

            virtual point bottom_left() const;
            virtual point top_right() const;
            virtual void render(std::ostream& out, float scale, const std::string& indent) const;
        };
        struct circle: public element {
            point center;
            long radius;

            circle(const point& c, long radius, const style& st = style::no_style);

            virtual point bottom_left() const;
            virtual point top_right() const;
            virtual void render(std::ostream& out, float scale, const std::string& indent) const;
        };
        struct line: public element {
            point from;
            point to;

            line(const point& f, const point& t, const style& st = style::no_style);

            virtual point bottom_left() const;
            virtual point top_right() const;
            virtual void render(std::ostream& out, float scale, const std::string& indent) const;
        };
        struct polygon: public element {
            std::vector<point> points;

            polygon(const std::vector<point>& pts, const style& st = style::no_style);
            polygon(const style& st = style::no_style);

            void add_point(const point& p);

            virtual point bottom_left() const;
            virtual point top_right() const;
            virtual void render(std::ostream& out, float scale, const std::string& indent) const;
        };

        printer(float scale = 1.0);
        virtual ~printer();

        void set_scale(float scale);

        const point& bottom_left() const;
        const point& top_right() const;

        void add_element(element* elt);

        void render(std::ostream& out, long hmargin = 0, long vmargin = 0);


    private:
        float _scale;
        point _min, _max;
        std::deque<element*> _elements;
};


}

#endif // SVGPRINTER_H



