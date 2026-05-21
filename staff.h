#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "patient.h"

class Department;

class Staff
{
    std::string name="";
    int salary;
    static int nextId;
    const int id;

    public:
        //getter-e/setter-e
        void setSalary(const int newSalary);
        int getSalary() const;
        void setName(const std::string& newName);
        const std::string& getName() const;
        int getId() const;

        //constructori
        Staff();

        Staff(const std::string& name, const int salary);

        Staff(const Staff& other);
        //destructor
        virtual ~Staff();

        friend void Swap(Staff& a, Staff& b);

        //operatori
        virtual void display(std::ostream& os) const = 0; //display virtual

        friend std::ostream& operator<<(std::ostream& os, const Staff& e);
        Staff& operator=(const Staff& other);

        //metoda virtuala
        virtual void doWork(std::vector<std::shared_ptr<Patient>>& waitingInQueue, std::vector<Department>& departments, int& moneyWastedThisHour, std::vector<std::string>& inactiveThisHour) = 0;
};

class Doctor : public Staff 
{
    int patientsPerDay;
    std::string specialisation;
    int patientsTreated=0;

    public: 
        // gettere/settere
        void setSpecialization(const std::string& spec);
        const std::string& getSpecialisation() const;

        void setPatientsPerDay(int nr);
        int getPatientsPerDay() const;


        //constuctori
        Doctor();
        Doctor(const std::string& name, int salary, const std::string& specialisation, int patientsPerDay);
        Doctor(const Doctor& other);

        //override
        void doWork(std::vector<std::shared_ptr<Patient>>& waitingInQueue, std::vector<Department>& departments, int& moneyWastedThisHour, std::vector<std::string>& inactiveThisHour) override;

        //operatori
        void display(std::ostream& os) const override;
        Doctor& operator=(const Doctor& other);
};

class Nurse : public Staff
{
    std::string role;

    public:
        // constructori
        Nurse();
        Nurse(const std::string& name, int salary, const std::string& role);
        Nurse(const Nurse& other);

        // override
        void doWork(std::vector<std::shared_ptr<Patient>>& waitingInQueue, std::vector<Department>& departments, int& moneyWastedThisHour, std::vector<std::string>& inactiveThisHour) override;

        //operatori
        void display(std::ostream& os) const override;
        Nurse& operator=(const Nurse& other);
};

class Admin : public Staff
{
    int patientsRedirected=0;

    public:
        // constructori
        Admin();
        Admin(const std::string& name, int salary);
        Admin(const Admin& other);

        // override
        void doWork(std::vector<std::shared_ptr<Patient>>& waitingInQueue, std::vector<Department>& departments, int& moneyWastedThisHour, std::vector<std::string>& inactiveThisHour) override;

        // operatori
        void display(std::ostream& os) const override;
        Admin& operator=(const Admin& other);
};
