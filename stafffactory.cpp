#include "staffFactory.h"

std::shared_ptr<Doctor> StaffFactory::createDoctor(const std::string& name, int salary, const std::string& role, int patientsPerDay)
{
    return std::make_shared<Doctor>(name, salary, role, patientsPerDay);
}

std::shared_ptr<Nurse> StaffFactory::createNurse(const std::string& name, int salary, const std::string& role)
{
    return std::make_shared<Nurse>(name, salary, role);
}

std::shared_ptr<Admin> StaffFactory::createAdmin(const std::string& name, int salary)
{
    return std::make_shared<Admin>(name, salary);
}

std::shared_ptr<EmergencyOperator> StaffFactory::createEmergencyOperator(const std::string& name, int salary)
{
    return std::make_shared<EmergencyOperator>(name, salary);
}