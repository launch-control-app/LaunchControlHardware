#include "car_status.hpp"

namespace obd
{

CarStatus::CarStatus(){};

void CarStatus::add_field(const pid::Pid_t &pid, const pid::Value_t &value)
{
    fields_.emplace_back(pid, value);
}

const CarStatus::Fields_t &CarStatus::get_fields() const
{
    return fields_;
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
