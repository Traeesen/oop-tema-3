#pragma once

#include <vector>
#include <memory>

#include "department.h"
#include "patient.h"
#include "workday.h"

class Hospital
{
    std::vector<Department> departments;
    std::vector<std::shared_ptr<Patient>> waitingQueue;
    std::vector<std::shared_ptr<Staff>> staff;

    WorkDay<int> moneyWastedPerHour;
    WorkDay<std::vector<std::string>> inactiveStaffPerHour;

    Hospital();

    void loadDoctors(const std::string& filename);
    void loadNurses(const std::string& filename);
    void loadAdmins(const std::string& filename);
    void loadPatients(const std::string& filename);

public:
    // nu poate fi copiat
    Hospital(const Hospital&) = delete;
    Hospital& operator=(const Hospital&) = delete;

    // singurul mod de a accesa
    static Hospital& getInstance();

    void addDepartment(const Department& department);
    std::vector<Department>& getDepartments();
    void addPatient(std::shared_ptr<Patient> patient);
    std::vector<std::shared_ptr<Patient>>& getWaitingQueue();

    void simulateDay();
    void printFinalReport() const;
};