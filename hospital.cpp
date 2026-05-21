#include "hospital.h"
#include "stafffactory.h"
#include "exceptions.h"
#include <fstream>
#include <iostream>

Hospital::Hospital() //privat
{
    loadDoctors("doctors.txt");
    loadNurses("nurses.txt");
    loadAdmins("admins.txt");
    loadEmergencyOperators("operators.txt");
    loadPatients("patients.txt");
    loadCalls("calls.txt");
    loadAppointments("appointments.txt");
}

Hospital& Hospital::getInstance()
{
    static Hospital instance;
    return instance;
}

std::vector<Department>& Hospital::getDepartments()
{
    return departments;
}

std::vector<std::shared_ptr<Patient>>& Hospital::getWaitingQueue()
{
    return waitingQueue;
}

void Hospital::addDepartment(const Department& department)
{
    departments.push_back(department);
}

void Hospital::addPatient(std::shared_ptr<Patient> patient)
{
    waitingQueue.push_back(patient);
}

void Hospital::loadDoctors(const std::string& filename)
{
    std::ifstream fin(filename);
    if(!fin.is_open()) throw FileOpenException(filename);

    std::string name, role;
    int patientsPerDay, salary;

    while(fin >> name >> role >> patientsPerDay >> salary)
    {
        std::shared_ptr<Doctor> d = StaffFactory::createDoctor(name, salary, role, patientsPerDay);

        int count = departments.size();
        bool found = false;

        for(int i = 0; i < count; i++)
        {
            if(departments[i].getName() == role)
            {
                found = true;
                departments[i].addEmployee(d);
                break;
            }
        }

        if(found == false)
        {
            Department dep(role);
            dep.addEmployee(d);
            departments.push_back(dep);
        }

        staff.push_back(d);
    }
}

void Hospital::loadNurses(const std::string& filename)
{
    std::ifstream fin(filename);
    if(!fin.is_open()) throw FileOpenException(filename);

    std::string name, role;
    int salary;

    while(fin >> name >> role >> salary)
    {
        std::shared_ptr<Nurse> d = StaffFactory::createNurse(name, salary, role);

        int count = departments.size();
        bool found = false;

        for(int i = 0; i < count; i++)
        {
            if(departments[i].getName() == role)
            {
                found = true;
                departments[i].addEmployee(d);
                break;
            }
        }

        if(found == false)
        {
            // TODO THROW ERROR
        }

        staff.push_back(d);
    }
}

void Hospital::loadAdmins(const std::string& filename)
{
    std::ifstream fin(filename);
    if(!fin.is_open()) throw FileOpenException(filename);

    std::string name;
    int salary;

    while(fin >> name >> salary)
    {
        std::shared_ptr<Admin> d = StaffFactory::createAdmin(name, salary);
        staff.push_back(d);
    }
}

void Hospital::loadPatients(const std::string& filename)
{
    std::ifstream fin(filename);
    if(!fin.is_open()) throw FileOpenException(filename);

    int hour = 0;

    while(true)
    {
        std::shared_ptr<Patient> p = readPatientFromLine(fin, false, hour);

        if(p == nullptr)
            break;

        waitingQueue.push_back(p);
    }
}

std::shared_ptr<Patient> Hospital::readPatientFromLine(std::ifstream& fin, bool hasHour, int& hour)
{
    std::string name;
    int age;

    if(hasHour)
    {
        if(!(fin >> hour >> name >> age))
            return nullptr;
    }
    else
    {
        if(!(fin >> name >> age))
            return nullptr;
    }

    std::shared_ptr<Patient> p = std::make_shared<Patient>(name, age);

    std::string problems;
    std::getline(fin, problems);

    std::string word;

    for(size_t i = 0; i < problems.size(); i++)
    {
        if(problems[i] == ' ')
        {
            if(!word.empty())
            {
                p->addProblem(word);
                word.clear();
            }
        }
        else
        {
            word += problems[i];
        }
    }

    if(!word.empty())
        p->addProblem(word);

    return p;
}

void Hospital::loadEmergencyOperators(const std::string& filename)
{
    std::ifstream fin(filename);
    if(!fin.is_open()) throw FileOpenException(filename);

    std::string name;
    int salary;

    while(fin >> name >> salary)
    {
        std::shared_ptr<EmergencyOperator> e = StaffFactory::createEmergencyOperator(name, salary);
        staff.push_back(e);
    }
}

void Hospital::loadCalls(const std::string& filename)
{
    std::ifstream fin(filename);
    if(!fin.is_open()) throw FileOpenException(filename);

    int hour = 0;

    while(true)
    {
        std::shared_ptr<Patient> p = readPatientFromLine(fin, true, hour);

        if(p == nullptr)
            break;

        p->setEmergency(true);

        if(hour >= 1 && hour <= 8)
            callsByHour[hour].push_back(p);
    }
}

void Hospital::loadAppointments(const std::string& filename)
{
    std::ifstream fin(filename);
    if(!fin.is_open()) throw FileOpenException(filename);

    int hour = 0;

    while(true)
    {
        std::shared_ptr<Patient> p = readPatientFromLine(fin, true, hour);

        if(p == nullptr)
            break;

        p->setAppointment(true);

        if(hour >= 1 && hour <= 8)
            appointmentsByHour[hour].push_back(p);
    }
}

void Hospital::processCalls(int hour)
{
    for(int i = 0; i < callsByHour[hour].size(); i++)
    {
        emergencyCallsQueue.push_back(callsByHour[hour][i]);
        std::cout << "Emergency call received for " << callsByHour[hour][i]->getName() << ".\n";
    }
}

void Hospital::processAppointments(int hour)
{
    for(int i = 0; i < appointmentsByHour[hour].size(); i++)
    {
        std::shared_ptr<Patient> patient = appointmentsByHour[hour][i];

        if(patient->getProblems().size() == 0)
            continue;

        std::string neededDepartment = patient->getProblems()[0];

        bool found = false;

        for(int j = 0; j < departments.size(); j++)
        {
            if(departments[j].getName() == neededDepartment)
            {
                departments[j].addPatient(patient);
                found = true;
                std::cout << "Appointment patient " << patient->getName() << " went directly to " << neededDepartment << ".\n";
                break;
            }
        }

        if(!found)
        {
            std::cout << "Appointment patient " << patient->getName() << " could not be sent to " << neededDepartment << " because the department does not exist.\n";
        }
    }
}

void Hospital::simulateDay()
{
    for(int hour = 1; hour <= 8; hour++)
    {
        std::cout << '\n' << "----------- HOUR " << hour << " -----------\n";

        int size = staff.size();

        std::vector<std::string> inactiveThisHour;
        int moneyWastedThisHour = 0;

        processCalls(hour);
        processAppointments(hour);

        for(int i = size - 1; i >= 0; i--) staff[i]->doWork(waitingQueue, departments, emergencyCallsQueue, moneyWastedThisHour, inactiveThisHour);

        inactiveStaffPerHour.addHourResult(inactiveThisHour);
        moneyWastedPerHour.addHourResult(moneyWastedThisHour);

        if(waitingQueue.size() == 0)
        {
            std::cout << "\nALL PATIENTS HAVE BEEN TREATED\n";

            int unusedHours = 8 - hour;

            if(unusedHours > 0)
            {
                int totalSalary = 0;

                for(int i = 0; i < staff.size(); i++)
                    totalSalary += staff[i]->getSalary();

                int wastedMoney = (totalSalary * unusedHours) / 20;

                std::cout << "Recommendation: The hospital finished " << unusedHours << " hour(s) early and wasted approximately " << wastedMoney << " ron in salaries. Consider reducing staff or accepting more patients.\n";
            }

            break;
        }
    }

    if(waitingQueue.size() > 0)
    {
        int untreatedPatients = waitingQueue.size();

        int estimatedLoss = untreatedPatients * 1000;

        std::cout << "\nRecommendation: " << untreatedPatients << " patient(s) were not treated before the hospital closed. The hospital likely needs more doctors, nurses, or administrators in overloaded departments. Alternatively, there may be departments that don't exist.";
    }
}

void Hospital::printFinalReport() const
{
    std::cout << "\n\nFINAL STAFF RESULTS:";
    std::cout << "\nADMINS:\n";

    for(int i = 0; i < staff.size(); i++)
        if(std::dynamic_pointer_cast<Admin>(staff[i]))
            std::cout << *staff[i] << "\n";

    std::cout << "\nDEPARTMENTS:\n";
    printCollection(departments);

    moneyWastedPerHour.printReport("Money wasted per hour");
    inactiveStaffPerHour.printReportCollection("Inactive staff per hour");
}