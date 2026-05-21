#pragma once
#include <vector>
#include <memory>
#include <string>
#include <iostream>
#include "staff.h"

class Department
{
    std::vector<std::shared_ptr<Staff>> assignedStaff;
    std::vector<std::shared_ptr<Patient>> patients;
    std::string name="";
    int availableNurses=0;

    public:
        //monte de getteurs et setteurs
        int getEmployeeCount() const;
        const std::vector<std::shared_ptr<Staff>>& getStaff() const;
        void setName(const std::string& newName);
        const std::string& getName() const;
        void addPatient(std::shared_ptr<Patient> p);
        std::vector<std::shared_ptr<Patient>>& getPatients();
        void removeFirstPatient();
        void addAvailableNurse();
        bool useAvailableNurse();

        //constructori
        Department(const std::string& name);
        Department(const Department& other);

        //dstructor
        ~Department();

        //adaugam un angajat in departament
        void addEmployee(std::shared_ptr<Staff> e);

        friend std::ostream& operator<<(std::ostream& os, const Department& d);
        friend void Swap(Department& a, Department& b);
        Department& operator=(Department other);
};
