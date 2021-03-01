#ifndef GEOMETRY_H_
#define GEOMETRY_H_
#include <stdlib.h>

class Rectangle {
public:
    Rectangle(float x, float y, float width, float height) : x(x), y(y), width(width), height(height){}
    float get_x();
    float get_y();
    float get_width();
    float get_height();
    bool contains(float x, float y);
    bool intersects(Rectangle& rect);
private:
    float x;
    float y;
    float width;
    float height;
};


class Point {
public:
    Point(size_t index, float x, float y) : index(index), x(x), y(y){}
    size_t get_index();
    float get_x();
    float get_y();
private:
    size_t index;
    float x;
    float y;
};
#endif