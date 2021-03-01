#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "geometry.h"
#include "quadtree.h"


namespace py = pybind11;


PYBIND11_MODULE(quadtree, m)  {
    py::class_<Quadtree>(m, "Quadtree")
        .def(py::init<float, float, float, float, size_t>(),
             py::arg("x") = 0,
             py::arg("y") = 0,
             py::arg("width") = 100,
             py::arg("height") = 100,
             py::arg("capacity") = 4)
        .def("add", &Quadtree::add)
        .def("insert", &Quadtree::insert)
        .def("select", &Quadtree::select)
        .def("select_from", &Quadtree::select_from);
}