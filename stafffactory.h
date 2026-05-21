#pragma once

#include <memory>
#include <string>

#include "staff.h"

class StaffFactory
{
public:
    static std::shared_ptr<Doctor> createDoctor(const std::string& name, int salary, const std::string& role, int patientsPerDay);
    static std::shared_ptr<Nurse> createNurse(const std::string& name, int salary, const std::string& role);
    static std::shared_ptr<Admin> createAdmin(const std::string& name, int salary);
};