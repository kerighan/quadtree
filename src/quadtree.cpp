#include "quadtree.h"
#include <stdlib.h>
#include <iostream>
#include "threading.h"


Quadtree::Quadtree(float x, float y, float width, float height, size_t capacity){
    this->boundary = new Rectangle(x, y, width, height);
    this->capacity = capacity;
}


Quadtree::~Quadtree(){
    delete this->boundary;
    delete this->northwest;
    delete this->northeast;
    delete this->southwest;
    delete this->southeast;
}


Quadtree::Quadtree(const Quadtree& qt){
    float x = this->boundary->get_x();
    float y = this->boundary->get_y();
    float width = this->boundary->get_width();
    float height = this->boundary->get_height();

    this->capacity = qt.capacity;
    this->boundary = new Rectangle(x, y, width, height);
    this->divided = qt.divided;
    this->points.empty();
    for (size_t i = 0; i < qt.points.size(); i++){
        this->points.push_back(qt.points[i]);
    }

    this->northwest = new Quadtree(*qt.northwest);
    this->northeast = new Quadtree(*qt.northeast);
    this->southeast = new Quadtree(*qt.southeast);
    this->southwest = new Quadtree(*qt.southwest);
}


Quadtree& Quadtree::operator=(const Quadtree& qt){
    // Guard self assignment
    if (this == &qt)
        return *this;

    this->capacity = qt.capacity;
    this->boundary = qt.boundary;
    this->divided = qt.divided;
    this->points.empty();
    for (size_t i = 0; i < qt.points.size(); i++){
        this->points.push_back(qt.points[i]);
    }

    this->northwest = new Quadtree(*qt.northwest);
    this->northeast = new Quadtree(*qt.northeast);
    this->southeast = new Quadtree(*qt.southeast);
    this->southwest = new Quadtree(*qt.southwest);
    return *this;
}


void Quadtree::subdivide(){
    float bx = this->boundary->get_x();
    float by = this->boundary->get_y();
    float bw = this->boundary->get_width() / 2;
    float bh = this->boundary->get_height() / 2;

    this->northwest = new Quadtree(bx, by, bw, bh, this->capacity);
    this->northeast = new Quadtree(bx + bw, by, bw, bh, this->capacity);
    this->southwest = new Quadtree(bx, by + bh, bw, bh, this->capacity);
    this->southeast = new Quadtree(bx + bw, by + bh, bw, bh, this->capacity);

    this->divided = true;
}


void Quadtree::insert(py::array_t<float> data){
    py::buffer_info XBuf = data.request();
    float* X = (float *)XBuf.ptr;
    size_t size = XBuf.shape[0];

    for (size_t i = 0; i < size; i++){
        this->add(i, X[2 * i], X[2 * i + 1]);
    }
}


bool Quadtree::add(int index, float x, float y){
    if (!this->boundary->contains(x, y))
        return false;

    if (this->points.size() < this->capacity){
        Point point = Point(index, x, y);
        this->points.push_back(point);
        return true;
    }
    
    if (!this->divided)
        this->subdivide();
    
    if (this->northwest->add(index, x, y)){
        return true;
    } else if (this->northeast->add(index, x, y)){
        return true;
    } else if (this->northeast->add(index, x, y)){
        return true;
    } else if (this->southeast->add(index, x, y)){
        return true;
    } else if (this->southwest->add(index, x, y)){
        return true;
    }
    return false;
}


std::vector<size_t> Quadtree::select(float x, float y, float width, float height){
    std::vector<size_t> selection;
    Rectangle select_rect = Rectangle(x, y, width, height);
    this->select_from_rect(select_rect, selection);
    return selection;
}


void Quadtree::select_from_rect(Rectangle& select_rect, std::vector<size_t>& selection){
    if (!this->boundary->intersects(select_rect))
        return;

    // add all points intersecting
    for (auto& point : this->points){
        if (select_rect.contains(point.get_x(), point.get_y()))
            selection.push_back(point.get_index());
    }

    if (this->divided){
        this->northwest->select_from_rect(select_rect, selection);
        this->northeast->select_from_rect(select_rect, selection);
        this->southwest->select_from_rect(select_rect, selection);
        this->southeast->select_from_rect(select_rect, selection);
    }
}

std::vector<std::vector<size_t>> Quadtree::select_from(py::array_t<float> data, float radius){
    py::buffer_info XBuf = data.request();
    float* X = (float *)XBuf.ptr;
    size_t size = XBuf.shape[0];

    std::vector<std::vector<size_t>> results(size);
    // results.reserve(size);
    // for (size_t i = 0; i < size; i++){
    PARALLEL_FOR_BEGIN(size){
        std::vector<size_t> res;
        float x = X[2 * i];
        float y = X[2 * i + 1];
        results[i] = this->select(x - radius, y - radius, 2 * radius, 2 * radius);
    }PARALLEL_FOR_END();
    // }
    return results;
}