#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>

#include "ics-servo/ics.h"

namespace py = pybind11;

namespace Adaptor {

class IOProvider {
  ::ICSServo::IOProvider provider;

public:
  IOProvider(std::string const& device, std::size_t en_pin_idx) : provider(device, en_pin_idx) {}

  void set_id(::ICSServo::ServoID id) {
    this->provider.set_id(id);
  }

  ::ICSServo::ServoID get_id() {
    return this->provider.get_id();
  }
};

}

PYBIND11_MODULE(servoarray, m) {
  m.doc() = "ICSServo: ICS serial servo driver library";
  py::class_<::ICSServo::Servo>(m, "Servo")
    .def("set_position", &::ICSServo::Servo::set_position)
    .def("set_free", &::ICSServo::Servo::set_free)
    .def("set_stretch", &::ICSServo::Servo::set_stretch)
    .def("set_speed", &::ICSServo::Servo::set_speed)
    .def("set_current_limit", &::ICSServo::Servo::set_current_limit)
    .def("set_temperature_limit", &::ICSServo::Servo::set_temperature_limit)
    .def("get_stretch", &::ICSServo::Servo::get_stretch)
    .def("get_speed", &::ICSServo::Servo::get_speed)
    .def("get_current", &::ICSServo::Servo::get_current)
    .def("get_temperature", &::ICSServo::Servo::get_temperature)
    .def("get_position", &::ICSServo::Servo::get_position);

  py::class_<Adaptor::IOProvider>(m, "IOProvider")
    .def(py::init<std::string, std::size_t>(), py::arg("device"), py::arg("en_idx"))
    .def("set_id", &Adaptor::IOProvider::set_id)
    .def("get_id", &Adaptor::IOProvider::get_id);
}
