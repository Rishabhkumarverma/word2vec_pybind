#include "trt_profiler.hpp"
#include <pybind11/pybind11.h>

PYBIND11_MODULE(PyProfiler, m)
{
  namespace py = pybind11;
  py::class_<CPyProfiler, std::shared_ptr<CPyProfiler>>(m, "CPyProfiler")
   //py::class_<PyProfiler,nvinfer1::IProfiler>(m, "PyProfiler")
      .def(py::init<>())
        // The destroy_plugin function does not override the base class, so we must bind it explicitly.
      .def("myadd", &CPyProfiler::myadd)
      .def("doc2vector", &CPyProfiler::run);
      //.def(py::init<PyProfiler::reportLayerTime_t>());
}

