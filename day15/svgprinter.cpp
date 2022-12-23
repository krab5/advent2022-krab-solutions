#include "svgprinter.h"

#define MIN(x,y)    (x >= y ? y : x)
#define MAX(x,y)    (x >= y ? x : y)

#define SHOWIFNOTEMPTY(s, key, out)     if (!s.empty()) out << " " << key << "=\"" << s << "\"";

using namespace svg;
using common::point;
using std::string;
using std::ostream;

const printer::style printer::style::no_style = style();

printer::style::style() : stroke_color(""), stroke_width(""), stroke_dash(""), fill_color(""), opacity(-1.f) {}

void printer::style::render(ostream& out) const {
    SHOWIFNOTEMPTY(stroke_color, "stroke", out);
    SHOWIFNOTEMPTY(stroke_width, "stroke-width", out);
    SHOWIFNOTEMPTY(stroke_dash,  "stroke_dasharray", out);
    SHOWIFNOTEMPTY(fill_color, "fill", out);

    if (opacity >= 0.0 && opacity <= 1.0)
        out << " opacity=\"" << opacity << "\"";
}

printer::style printer::style::fill(const char* color, float opacity) {
    style s;
    s.stroke_color = "none";
    s.fill_color = color;
    s.opacity = opacity;
    return s;
}

printer::style printer::style::stroke(const char* color, const char* width, const char* dash, float opacity) {
    style s;
    s.fill_color = "none";
    s.stroke_color = color;
    s.stroke_width = width;
    s.stroke_dash = dash;
    s.opacity = opacity;
    return s;
}


printer::element::element(const style& s) : the_style(s) {}


printer::rect::rect(const point& c, const point& s, const style& st) :
    corner(c), size(s), element(st) {}

point printer::rect::bottom_left() const {
    return corner;
}

point printer::rect::top_right() const {
    return corner + size;
}

void printer::rect::render(ostream& out, float scale, const string& indent) const {
    out << indent << "<rect x=\"" << corner.x * scale << "\" y=\"" << corner.y * scale << "\" "
        << "width=\"" << size.x * scale << "\" height=\"" << size.y * scale << "\"";
    the_style.render(out);
    out << " />" << std::endl;
}


printer::circle::circle(const point& c, long r, const style& st) :
    center(c), radius(r), element(st) {}

point printer::circle::bottom_left() const {
    return center - point(radius, radius);
}

point printer::circle::top_right() const {
    return center + point(radius, radius);
}

void printer::circle::render(ostream& out, float scale, const string& indent) const {
    out << indent << "<circle cx=\"" << center.x * scale << "\" cy=\"" << center.y * scale 
        << "\" r=\"" << radius * scale << "\"";
    the_style.render(out);
    out << " />" << std::endl;
}


printer::line::line(const point& f, const point& t, const style& st) :
    from(f), to(t), element(st) {}

point printer::line::bottom_left() const {
    return point(
        MIN(from.x, to.x),
        MIN(from.y, to.y)
    );
}

point printer::line::top_right() const {
    return point(
        MAX(from.x, to.x),
        MAX(from.y, to.y)
    );
}

void printer::line::render(std::ostream& out, float scale, const std::string& indent) const {
    out << indent << "<line x1=\"" << from.x*scale << "\" y1=\"" << from.y*scale << "\" "
        << "x2=\"" << to.x*scale << "\" y2=\"" << to.y*scale << "\"";
    the_style.render(out);
    out << " />" << std::endl;
}


printer::polygon::polygon(const std::vector<point>& pts, const style& st) :
    points(pts), element(st) {}
printer::polygon::polygon(const style& st) :
    element(st) {}

void printer::polygon::add_point(const point& p) {
    points.push_back(p);
}

point printer::polygon::bottom_left() const {
    point min;
    bool set = false;

    for (point p : points) {
        if (!set) {
            min = p;
            set = true;
        } else {
            if (p.x < min.x) min.x = p.x;
            if (p.y < min.y) min.y = p.y;
        }
    }

    return min;
}

point printer::polygon::top_right() const {
    point max;
    bool set = false;

    for (point p : points) {
        if (!set) {
            max = p;
            set = true;
        } else {
            if (p.x > max.x) max.x = p.x;
            if (p.y > max.y) max.y = p.y;
        }
    }

    return max;
}

void printer::polygon::render(std::ostream& out, float scale, const std::string& indent) const {
    out << indent << "<polygon points=\"";
    for (size_t i = 0; i < points.size(); i++) {
        out << points[i].x * scale << "," << points[i].y * scale;
        if (i < points.size() - 1)
            out << " ";
    }
    out << "\"";
    the_style.render(out);
    out << " />" << std::endl;
}


printer::printer(float scale) : _scale(scale) {}
printer::~printer() {
    for (element* e : _elements)
        delete e;
}

void printer::set_scale(float scale) {
    _scale = scale;
}

const point& printer::bottom_left() const {
    return _min;
}

const point& printer::top_right() const {
    return _max;
}

void printer::add_element(element* elt) {
    point bl = elt->bottom_left();
    point tr = elt->top_right();

    if (_min.x > bl.x) _min.x = bl.x;
    if (_min.y > bl.y) _min.y = bl.y;
    if (_max.x < tr.x) _max.x = tr.x;
    if (_max.y < tr.y) _max.y = tr.y;

    _elements.push_back(elt);
}

void printer::render(ostream& out, long hmargin, long vmargin) {
    point min = _min - point(hmargin, vmargin);
    point size = (_max + point(hmargin, vmargin)) - min;

    out << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"yes\" ?>" << std::endl;
    out << "<svg xmlns:svg=\"http://www.w3.org/2000/svg\" version=\"1.1\" "
        << "viewBox=\"" << min.x * _scale << " " << min.y * _scale << " " 
        << size.x * _scale << " " << size.y * _scale << "\">" << std::endl;

    for (element* elt : _elements) {
        elt->render(out, _scale, "  ");
    }

    out << "</svg>" << std::endl;
}


