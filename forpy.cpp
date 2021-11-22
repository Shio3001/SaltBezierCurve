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
    Integration *integration_control = new Integration();

    float x1;
    float y1;
    float x2;
    float y2;

    int width_size;
    int height_size;

public:
    ForPyInterface(int send_width_size, int send_height_size)
    {
        width_size = send_width_size;
        height_size = send_height_size;

        std::cout << width_size << " " << send_height_size << std::endl;

        integration_control->Setup(width_size, height_size);
    }
    void Setx1y1(py::object send_x1, py::object send_y1)
    {
        x1 = py::extract<float>(send_x1);
        y1 = py::extract<float>(send_y1);
    }
    void Setx2y2(py::object send_x2, py::object send_y2)
    {
        x2 = py::extract<float>(send_x2);
        y2 = py::extract<float>(send_y2);
    }
    np::ndarray GetView()
    {
        integration_control->CalculationSetup(x1, y1, x2, y2);
        integration_control->CalculationView();
        int *draw = integration_control->GetView();

        py::tuple shape = py::make_tuple(width_size * height_size);
        py::tuple stride = py::make_tuple(sizeof(int));
        np::dtype dt = np::dtype::get_builtin<uint>();
        np::ndarray npdraw = np::from_data(&draw[0], dt, shape, stride, py::object());

        return npdraw;
    }
    np::ndarray GetCalculation()
    {
    }
};

BOOST_PYTHON_MODULE(forpy)
{
    Py_Initialize();
    np::initialize();
    py::class_<ForPyInterface>("ForPyInterface",
                               py::init<int, int>()) // ForPyInterfaceコンストラクタへの引数型
        .def("Setx1y1", &ForPyInterface::Setx1y1)
        .def("Setx2y2", &ForPyInterface::Setx2y2)
        .def("GetView", &ForPyInterface::GetView)
        .def("GetCalculation", &ForPyInterface::GetCalculation);

    // py::class_<std::vector<int>>("std::vector<int>")
    //     .def(vector_indexing_suite<std::vector<int>>());
    //.def("sta", &VideoExecutionCenter::sta)
    //.def("execution", &VideoExecutionCenter::execution)
    //.def("layer_interpretation", &VideoExecutionCenter::layer_interpretation);
}
