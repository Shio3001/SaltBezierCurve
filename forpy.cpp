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

#include "funcintegration.hpp"
#include "stdload.hpp"

class ForPyInterface
{
private:
    Integration *integration_control = new Integration;
    integration_control->Setup(200, 200);

    int x1;
    int y1;
    int x2;
    int y2;

public:
    ForPyInterface()
    {
    }
    void Setx1y1(int send_x1, int send_y1)
    {
        x1 = send_x1;
        y1 = send_y1;
    }
    void Setx2y2(int send_x2, int send_y2)
    {
        x2 = send_x2;
        y2 = send_y2;
    }
    np::ndarray GetView()
    {
        integration_control->CalculationSetup(x1, y1, x2, y2);
        int *draw = integration_control->GetView();

        py::tuple shape = py::make_tuple(200 * 200);
        py::tuple stride = py::make_tuple(sizeof(int));
        np::dtype dt = np::dtype::get_builtin<uint>();
        np::ndarray npdraw = np::from_data(&draw[0], dt, shape, stride, py::object());

        return npdraw;
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
                               py::init<>()) // VideoExecutionCenterコンストラクタへの引数型
        .def("Setx1y1", &ForPyInterface::Setx1y1)
        .def("Setx2y2", &ForPyInterface::Setx2y2)
        .def("GetView", &ForPyInterface::GetView)
        .def("GetCalculation", &ForPyInterface::GetCalculation);

    boost::python::class_<std::vector<int>>("vector<int>")
        .def(vector_indexing_suite<std::vector<int>>());
    //.def("sta", &VideoExecutionCenter::sta)
    //.def("execution", &VideoExecutionCenter::execution)
    //.def("layer_interpretation", &VideoExecutionCenter::layer_interpretation);
}
