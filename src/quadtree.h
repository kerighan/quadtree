#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include "geometry.h"
#include <stdlib.h>
#include <vector>


namespace py = pybind11;


class Quadtree {
public:
    Quadtree(){}
    Quadtree(float x, float y, float width, float height, size_t capacity);
    ~Quadtree();
    Quadtree(const Quadtree& qt);
    Quadtree& operator=(const Quadtree& qt);
    void subdivide();

    bool add(int index, float x, float y);
    void insert(py::array_t<float> data);

    std::vector<size_t> select(float x, float y, float width, float height);
    void select_from_rect(Rectangle& select_rect, std::vector<size_t>& selection);
    std::vector<std::vector<size_t>> select_from(py::array_t<float> data, float radius);
private:
    size_t capacity;
    Rectangle* boundary;
    bool divided = false;
    std::vector<Point> points;
    Quadtree* northwest = NULL;
    Quadtree* northeast = NULL;
    Quadtree* southeast = NULL;
    Quadtree* southwest = NULL;
};
