#include <vector>
#include "staff.h"
#include "department.h"
#include <iostream>


//monte de getteurs et setteurs
int Department::getEmployeeCount() const { return assignedStaff.size(); }
const std::vector<std::shared_ptr<Staff>>& Department::getStaff() const { return assignedStaff; }
void Department::setName(const std::string& newName)
{
    name = newName;
}
const std::string& Department::getName() const
{
    return name;
}

//constructori
Department::Department(const std::string& name)
{
    setName(name);
}

Department::Department(const Department& other)
{
    setName(other.getName());

    assignedStaff = other.getStaff();
}

//dstructor
Department::~Department()
{
}

//adaugam un angajat in departament
void Department::addEmployee(std::shared_ptr<Staff> e)
{

    assignedStaff.push_back(e);
}

void Department::addPatient(std::shared_ptr<Patient> p)
{
    patients.push_back(p);
}

std::vector<std::shared_ptr<Patient>>& Department::getPatients()
{
    return patients;
}

void Department::removeFirstPatient()
{
    if (!patients.empty())
    {
        patients.erase(patients.begin());
    }
}

void Department::addAvailableNurse()
{
    availableNurses++;
}

bool Department::useAvailableNurse()
{
    if (availableNurses > 0)
    {
        availableNurses--;
        return true;
    }

    return false;
}

void Swap(Department& a, Department& b)
{
    std::swap(a.name, b.name);
    std::swap(a.patients, b.patients);
    std::swap(a.assignedStaff, b.assignedStaff);
}
Department& Department::operator=(Department other)
{
    Swap(*this, other);
    return *this;
}

std::ostream& operator<<(std::ostream& os, const Department& d)
{
    int doctors = 0;
    int nurses = 0;

    for(int i = 0; i < d.getEmployeeCount(); i++)
    {
        if(std::dynamic_pointer_cast<Doctor>(d.getStaff()[i])) doctors++;
        else if(std::dynamic_pointer_cast<Nurse>(d.getStaff()[i])) nurses++;
    }

    os << d.getName() << "\n";
    os << "Doctors: " << doctors << ", Nurses: " << nurses;
    os << "---LIST OF STAFF:\n";

    for(int i = 0; i < d.getEmployeeCount(); i++)
        os << "    | " << *(d.getStaff()[i]) << "\n";

    return os;
}