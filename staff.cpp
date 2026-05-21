#include <iostream>
#include <vector>
#include "staff.h"
#include "exceptions.h"

// -- STAFF --

//getter-e/setter-e
void Staff::setSalary(const int newSalary)
{
    if(newSalary < 0) throw InvalidSalaryException();
    salary = newSalary;
}
int Staff::getSalary() const
{
    return salary;
}
void Staff::setName(const std::string& newName)
{
    name = newName;
}
const std::string& Staff::getName() const
{
    return name;
}
int Staff::getId() const {return id;}

//constructori
Staff::Staff() : id(nextId++)
{
    setSalary(0);
    setName("");
}
Staff::Staff(const std::string& name, const int salary) : id(nextId++)
{
    setSalary(salary);
    setName(name);
}
Staff::Staff(const Staff& other) : id(nextId++)
{
    setSalary(other.salary);
    setName(other.name);
}

Staff::~Staff()
{
}

int Staff::nextId=1;

//operatori
Staff& Staff::operator=(const Staff& other)
{
    if (this == &other) return *this;
    setSalary(other.getSalary());
    setName(other.getName());
    return *this;
}
std::ostream& operator<<(std::ostream& os, const Staff& e)
{
    e.display(os);
    return os;
}

// -- DOCTOR --

//getter-e/setter-e
void Doctor::setSpecialization(const std::string& spec)
{
    specialisation = spec;
}

const std::string& Doctor::getSpecialisation() const
{
    return specialisation;
}

void Doctor::setPatientsPerDay(int nr)
{
    patientsPerDay = nr;
}

int Doctor::getPatientsPerDay() const
{
    return patientsPerDay;
}

//constructori
Doctor::Doctor() : Staff(), specialisation(""), patientsPerDay(0)
{
}

Doctor::Doctor(const std::string& name, int salary, const std::string& specialisation, int patientsPerDay) : Staff(name, salary)
{
    setSpecialization(specialisation);
    setPatientsPerDay(patientsPerDay);
}

Doctor::Doctor(const Doctor& other) : Staff(other)
{
    setSpecialization(other.specialisation);
    setPatientsPerDay(other.patientsPerDay);
}

void Doctor::display(std::ostream& os) const //afisarea virtuala prin interfata non-virtuala
{
    os << "Doctor: " << getName() << ", Salary: " << getSalary() << ", Specialisation: " << specialisation;
    os << ", Patients treated today: " << patientsTreated;
}

//metoda virtuala
void Doctor::doWork(std::vector<std::shared_ptr<Patient>>& waitingInQueue, std::vector<Department>& departments, int& moneyWastedThisHour, std::vector<std::string>& inactiveThisHour)
{
    for (int i = 0; i < departments.size(); i++)
    {
        if (departments[i].getName() == specialisation)
        {
            int patientsThisHour = patientsPerDay / 8;

            // un asistent dubleaza productivitatea
            bool hasNurse = departments[i].useAvailableNurse();
            if (!hasNurse)
            {
                patientsThisHour /= 2;
            }
            if (patientsThisHour < 1) patientsThisHour = 1;

            if(departments[i].getPatients().size() == 0)
            {
                int wastedMoney = getSalary() / 20;
                
                inactiveThisHour.push_back(getName());
                moneyWastedThisHour += wastedMoney;

                std::cout << "Recommendation: " << getName() << " had no patients to treat in " << specialisation << ". Approximately " << wastedMoney << " ron was wasted this hour in salary expenses. Consider reducing staff in this department or redirecting more patients here.\n";

                break;
            }
            for (int j = 0; j < patientsThisHour && departments[i].getPatients().size() > 0; j++)
            {
                std::shared_ptr<Patient> patient = departments[i].getPatients()[0];

                departments[i].removeFirstPatient();

                if (patient->getAge() >= 60 && !hasNurse)
                {
                    inactiveThisHour.push_back(getName());
                    moneyWastedThisHour += getSalary() / 20;
                    std::cout << getName()<< " could not treat "<< patient->getName()<< " because elderly patients need nurse assistance.\n Recommendation: Hire more nurses so that elderly patients can receive assistance.";
                    break;
                }

                if (patient->getProblems().size() > 0)
                {
                    patientsTreated++;
                    std::cout << getName() << " Treated " << patient->getName() << " for " << patient->getProblems()[0] << "\n";
                    patient->removeFirstProblem();
                }

                // patient still needs treatment
                if (patient->getProblems().size() > 0)
                {
                    waitingInQueue.push_back(patient);
                }
            }

            break;
        }
    }
}

//operatori
Doctor& Doctor::operator=(const Doctor& other)
{
    if (this == &other) return *this;
    Staff::operator=(other);
    setSpecialization(other.getSpecialisation());
    setPatientsPerDay(other.getPatientsPerDay());
    return *this;
}


// -- ASISTENT --

//constructori
Nurse::Nurse() : Staff(), role("")
{
}

Nurse::Nurse(const std::string& name, int salary, const std::string& role) : Staff(name, salary), role(role)
{
}
Nurse::Nurse(const Nurse& other) : Staff(other), role(other.role)
{
}

void Nurse::display(std::ostream& os) const //afisarea virtuala prin interfata non-virtuala
{
    os << "Nurse: " << getName() << ", Salary: " << getSalary() << ", Assisting: " << role;
}


//metoda virtuala
void Nurse::doWork(std::vector<std::shared_ptr<Patient>>& waitingInQueue, std::vector<Department>& departments, int& moneyWastedThisHour, std::vector<std::string>& inactiveThisHour)
{
    for (int i = 0; i < departments.size(); i++)
    {
        if (departments[i].getName() == role)
        {
            departments[i].addAvailableNurse();
            std::cout << getName()<< " is assisting department "<< role<< "\n";
            break;
        }
    }
}

//operatori
Nurse& Nurse::operator=(const Nurse& other)
{
    if (this == &other) return *this;
    Staff::operator=(other);
    return *this;
}

// -- ADMIN --

//constructori
Admin::Admin() : Staff()
{
}

Admin::Admin(const std::string& name, int salary) : Staff(name, salary)
{
}

Admin::Admin(const Admin& other) : Staff(other)
{
}

void Admin::display(std::ostream& os) const //afisarea virtuala prin interfata non-virtuala
{
    os << "Admin: " << getName() << ", Salary: " << getSalary();
    os << ", Patients redirected today: " << patientsRedirected;
}

//metoda virtuala
void Admin::doWork(std::vector<std::shared_ptr<Patient>>& waitingInQueue, std::vector<Department>& departments, int& moneyWastedThisHour, std::vector<std::string>& inactiveThisHour)
{
    int patientsToRedirect = 1;

    if(waitingInQueue.size() == 0)
    {
        inactiveThisHour.push_back(getName());
        moneyWastedThisHour += getSalary() / 20;
    }

    for (int i = 0; i < patientsToRedirect && waitingInQueue.size() > 0; i++)
    {
        std::shared_ptr<Patient> patient = waitingInQueue[0];
        

        if (patient->getProblems().size() == 0)
            continue;

        std::string neededDepartment = patient->getProblems()[0];

        bool found = false;

        for (int j = 0; j < departments.size(); j++)
        {
            if (departments[j].getName() == neededDepartment)
            {
                departments[j].addPatient(patient);
                found = true;

                patientsRedirected++;
                std::cout << getName()<< " redirected "<< patient->getName()<< " to "<< neededDepartment<< "\n";

                break;
            }
        }

        if (!found)
        {
            std::cout << getName()<< " could not redirect "<< patient->getName()<< " because department "<< neededDepartment<< " does not exist. Patient cannot be treated.\n";

        }
        else waitingInQueue.erase(waitingInQueue.begin());
    }
}

//operatori
Admin& Admin::operator=(const Admin& other)
{
    if (this == &other) return *this;
    Staff::operator=(other);
    return *this;
}