#include "car_status.hpp"

namespace obd
{
    
CarStatus::CarStatus(const hardware::ObdUart::Pid_fields_t &pid_fields)
    : pid_fields_(pid_fields){};

const hardware::ObdUart::Pid_fields_t &CarStatus::get_fields() const 
{
    return pid_fields_;
}

// TODO: fix output formatting once bluetooth data message
//  format has been finalized
std::ostream &operator<<(std::ostream &os, const CarStatus &car_status)
{
    for (const auto &field : car_status.get_fields())
        os << field.second << ",";
    return os;
}

} // namespace obd
