// 16ビット モノラル
#include <bits/stdc++.h>
#include <math.h>
#include <stdio.h>

#include <boost/python.hpp>
#include <boost/python/numpy.hpp>
#include <iomanip>
//using namespace std;
namespace py = boost::python;
namespace np = boost::python::numpy;

class ForPyInterface
{
private:
    Integration *integration = new Integration();
    integration->Setup(200, 200);

public:
    ForJsInterface()
    {
    }
    void Setx1y1()
    {
    }
    void Setx2y2()
    {
    }
    np::ndarray GetView()
    {
    }
    std::vector<int> GetCalculation()
    {
    }
};

BOOST_PYTHON_MODULE(forpy)
{
    Py_Initialize();
    np::initialize();
    py::class_<ForPyInterface>("ForPyInterface",
                               py::init<int, int>()) // VideoExecutionCenterコンストラクタへの引数型
        .def("Setx1y1", &ForPyInterface::Setx1y1)
        .def("Setx1y1", &ForPyInterface::Setx2y2);

    boost::python::class_<std::vector<int>>("vector<int>")
        .def(vector_indexing_suite<std::vector<int>>());
    //.def("sta", &VideoExecutionCenter::sta)
    //.def("execution", &VideoExecutionCenter::execution)
    //.def("layer_interpretation", &VideoExecutionCenter::layer_interpretation);
}
