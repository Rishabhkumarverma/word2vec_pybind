#include "pybindword2vec.hpp"
#include <pybind11/pybind11.h>

PYBIND11_MODULE(word2vec, m)
{
  namespace py = pybind11;
  py::class_<CWord2Vec, std::shared_ptr<CWord2Vec>>(m, "Word2Vec")
   //py::class_<PyProfiler,nvinfer1::IProfiler>(m, "PyProfiler")
      .def(py::init<>())
        // The destroy_plugin function does not override the base class, so we must bind it explicitly.
      .def("myadd", &CWord2Vec::myadd)
      .def("doc2vector", &CWord2Vec::run);
      //.def(py::init<PyProfiler::reportLayerTime_t>());
}

