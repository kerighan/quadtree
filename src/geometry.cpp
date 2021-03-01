#include "geometry.h"

size_t Point::get_index(){
    return this->index;
}

float Point::get_x(){
    return this->x;
}

float Point::get_y(){
    return this->y;
}

float Rectangle::get_x(){
    return this->x;
}

float Rectangle::get_y(){
    return this->y;
}

float Rectangle::get_width(){
    return this->width;
}

float Rectangle::get_height(){
    return this->height;
}

bool Rectangle::contains(float x, float y){
    bool cond_x = (this->x <= x) && (x < this->x + this->width);
    bool cond_y = (this->y <= y) && (y < this->y + this->height);
    return cond_x && cond_y;
}

bool Rectangle::intersects(Rectangle& rect){
    float x = this->x;
    float y = this->y;
    float width = this->width;
    float height = this->height;

    float rx = rect.get_x();
    float ry = rect.get_y();
    float rwidth = rect.get_width();
    float rheight = rect.get_height();
    
    bool cond_1 = rx >= x + width;
    bool cond_2 = rx + rwidth < x;
    bool cond_3 = ry + rheight < y;
    bool cond_4 = ry >= y + height;
    bool not_intersect = cond_1 || cond_2 || cond_3 || cond_4;
    return !not_intersect;
}
